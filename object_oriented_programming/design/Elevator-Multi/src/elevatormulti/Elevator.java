package elevatormulti;

import java.util.ArrayList;
import java.util.Collections;

public class Elevator implements Movement, Comparable<Elevator>, Runnable{	
	/*overview: Elevator is a moving machine that is used to process passenger request in elevator system.
	 * There will be two types of request that will be processed by an elevator, the floor request, that is a 
	 * request made on certain floor, and elevator request, the request made in the elevator itself.
	 * Therefore, each elevator will have its own queues to record the requests that it needs to process,
	 * preventing to process other elevator's request or have its request processed by other elevator.
	 * When a request is done being processed, that request will be removed from the queue, meaning that
	 * it's done being processed and the system will call the OutputHandler to print out the record.
	 * The elevator will know which request should be processed first, considering there exist pickup
	 * requests that could be made after a main request is made and processed.
	*/
	OutputHandler output = new OutputHandler();
	Scheduler sched;
	Floors floors;
	
	private FloorQueue floorqueue = new FloorQueue();
	private ElevatorQueue elevqueue = new ElevatorQueue();
	
	private long moveTime = 3000;
	private long doorTime = 6000;
	
	private int tarFloor;
	private int elevnum;
	private int point = 0;
	private int curFloor = 1;
	private double elevTime = System.currentTimeMillis() * 0.001;
	private String direction = "STILL";
	private Status status = Status.IDLE;
	private ElevButtons elevbuttons = new ElevButtons();
	private Thread elevThread = null;
	private boolean isPickUp = false;
	
	public Elevator(int elevnum) {
		/**
		 * @REQUIRES:elevnum;
		 * @MODIFIES:this;
		 * @EFFECTS:
		 * (\result = \this) && (\this.isEmpty());
		 * (\this.elevnum == elevnum);
		 */
		this.elevnum = elevnum;
	}
	
	public synchronized boolean addFloorReq(FloorRequest req) throws InvalidRequestException, SameRequestException {
		/**
		 * @REQUIRES: req (FloorRequest);
		 * @MODIFIES: this.floorqueue;
		 * @EFFECTS: floorqueue.addQueue(req);
		 */
		return floorqueue.addQueue(req);
	}
	
	public synchronized boolean addElevReq(ElevatorRequest req) throws InvalidRequestException, SameRequestException {
		/**
		 * @REQUIRES: req (ElevatorRequest);
		 * @MODIFIES: this.elevqueue;
		 * @EFFECTS: elevqueue.addQueue(req);
		 */
		return elevqueue.addQueue(req);
	}
	
	public int getTargetFloor() {
		return this.tarFloor;
	}
	
	public int getElevNum() {
		return this.elevnum;
	}
	
	public int getCurFloor() {
		return this.curFloor;
	}
	
	public double getElevTime() {
		return this.elevTime;
	}
	
	public String getDir() {
		return this.direction;
	}
	
	public Status getElevStatus() {
		return this.status;
	}
	
	public ElevButtons getElevButtons() {
		return this.elevbuttons;
	}
	
	public int getPoint() {
		return this.point;
	}
	
	public synchronized void addPoint(int point) {
		/**
		 * @REQUIRES: point (int);
		 * @MODIFIES: this.point;
		 * @EFFECTS: \this.point == \old(\this.point) + 1;
		 */
		this.point += point;
	}
	
	public void setCurFloor(int floor) {
		this.curFloor = floor;
	}
	
	public void setDirection(String dir) {
		this.direction = dir;
	}
	
	public boolean getPickUp() {
		return this.isPickUp;
	}
	
	public int compareTo(Elevator elev) {		
		int comparepoint=((Elevator)elev).getPoint();
		return this.point-comparepoint;
	}
	
	public void setElevStatus(Status status) {
		this.status = status;
	}
	
	public void printFloor(FloorRequest req) {
		int target = req.getFloor();
		double time = req.getTime();
		String dir = req.getDir().toString();
		
		System.out.printf("[FR, %d, %s, %.0f] / (%d, %s, %.1f)\n", target, dir, time, this.curFloor, this.direction, this.elevTime);
		output.writeFloor(target, dir, time, this.elevnum, this.curFloor, this.direction, this.point);
	}
	
	public void printElevator(ElevatorRequest req) {
		int target = req.getFloor();
		double time = req.getTime();
		System.out.printf("[ER, %d, %.0f] / (%d, %s, %.1f)\n", target, time, this.curFloor, this.direction, this.elevTime);
		output.writeElev(target, time, this.elevnum, this.curFloor, this.direction, this.point);
	}
	
	public void printFloor(int target, double time, String dir) {
		System.out.printf("[FR, %d, %s, %.0f] / (%d, %s, %.1f)\n", target, dir, time, this.curFloor, this.direction, this.elevTime);
		output.writeFloor(target, dir, time, this.elevnum, this.curFloor, this.direction, this.point);
	}
	
	public void printElevator(int target, double time) {
		System.out.printf("[ER, %d, %.0f] / (%d, %s, %.1f)\n", target, time, this.curFloor, this.direction, this.elevTime);
		output.writeElev(target, time, this.elevnum, this.curFloor, this.direction, this.point);
	}
	
	public void setData(Scheduler sched) {
		this.sched = sched;
		this.floors = this.sched.getFloors();
	}
	
	@Override
	public boolean moveUp() {
		/**
		 * @REQUIRES: None;
		 * @MODIFIES: this;
		 * @EFFECTS: 
		 * (\result == true) ==> (\this.curFloor == \old.curFloor+1) && (\this.direction == UP);
		 * (\result == true) ==> (\this.point == \old.point+1);
		 * (\this.curFloor == \this.tarFloor) ==> 
		 * 	(\this.tarFloor.upbutton == false && \this.floorqueue.remove(0)) && 
		 * 	(\this.button(tarFloor) == false && \this.elevqueue.remove(0));
		 */
		while(this.curFloor < this.tarFloor) {
			this.direction = "UP";
			try {
				Thread.sleep(this.moveTime);
			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
			this.curFloor += 1;
			addPoint(1);
			try {
				pickUp();
			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
			if (isPickUp) {
				if (this.curFloor == this.tarFloor) {
					isPickUp = false;
					continue;
				}
				doorMove();
				isPickUp = false;
			}
		}
		if (this.floors.getFloor(this.curFloor-1).getUpStatus()) {
			printFloor(this.floorqueue.getQueue(0));
			try {
				this.floorqueue.removeQueue(0);
			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
			this.floors.getFloor(this.curFloor-1).setUpStatus(false, sched);
		}
		if (this.elevbuttons.getElevButton(this.curFloor-1).getButtonStat()) {
			printElevator(this.elevqueue.getQueue(0));
			this.elevbuttons.getElevButton(this.curFloor-1).setButtonStat(false);
		}
		doorMove();
		return true;
	}

	@Override
	public boolean moveDown() {
		/**
		 * @REQUIRES: None;
		 * @MODIFIES: this;
		 * @EFFECTS: 
		 * (\result == true) ==> (\this.curFloor == \old.curFloor-1) && (\this.direction == DOWN);
		 * (\result == true) ==> (\this.point == \old.point+1);
		 * (\this.curFloor == \this.tarFloor) ==> 
		 * 	(\this.tarFloor.downbutton == false && \this.floorqueue.remove(0)) && 
		 * 	(\this.button(tarFloor) == false && \this.elevqueue.remove(0));
		 */
		while(this.curFloor > this.tarFloor) {
			this.direction = "DOWN";
			try {
				Thread.sleep(this.moveTime);
			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
			this.curFloor -= 1;
			addPoint(1);
			try {
				pickUp();
			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
			if (isPickUp) {
				if (this.curFloor == this.tarFloor) {
					isPickUp = false;
					continue;
				}
				doorMove();
				isPickUp = false;
			}
		}
		if (this.floors.getFloor(this.curFloor-1).getDownStatus()) {
			printFloor(this.floorqueue.getQueue(0));
			try {
				this.floorqueue.removeQueue(0);
			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
			this.floors.getFloor(this.curFloor-1).setDownStatus(false, sched);
		}
		if (this.elevbuttons.getElevButton(this.curFloor-1).getButtonStat()) {
			printElevator(this.elevqueue.getQueue(0));
			this.elevbuttons.getElevButton(this.curFloor-1).setButtonStat(false);
		}
		doorMove();
		return true;
	}

	@Override
	public boolean doorMove() {
		/**
		 * @REQUIRES: None;
		 * @MODIFIES: this;
		 * @EFFECTS: 
		 * (\result == true) ==> (\this.direction == "STILL") && (System.time.wait(\this.doortime));
		 * \this.floors.floor(\this.curFloor-1).setUp(false);
		 */
		this.direction = "STILL";
		try {
			Thread.sleep(this.doorTime);
		} catch (Exception except) {
			System.out.print(except.getMessage());
		}
		this.floors.getFloor(this.curFloor-1).setUpStatus(false, sched);
		return true;
	}
	
	public void pickUp() throws CannotRemoveException {
		/**
		 * @REQUIRES:None;
		 * @MODIFIES:this;
		 * @EFFECTS:
		 * (\this.curFloor.canPickUpFloor) ==> (\this.curFloor.button == false && \this.isPickUp == true);
		 * (\this.curFloor.canPickUpElev) ==> (\this.button(curFloor) == false && \this.isPickUp == true);
		 */
		Floor floor = floors.getFloor(this.curFloor-1);
		ElevButton button = this.elevbuttons.getElevButton(this.curFloor-1);
		
		if (this.direction.equals("UP") && floor.getUpStatus() == true && floor.getFloorNum()<this.tarFloor) {
			if (this.floorqueue.contains(this.curFloor, this.direction)) {
				floor.setUpStatus(false, sched);
				printFloor(this.curFloor, floor.getUpTime(), "UP");
				isPickUp = true;
			}
		}
		
		else if (this.direction.equals("DOWN") && floor.getDownStatus() == true && floor.getFloorNum()<this.tarFloor) {
			if (this.floorqueue.contains(this.curFloor, this.direction)) {
				floor.setDownStatus(false, sched);
				printFloor(this.curFloor, floor.getDownTime(), "DOWN");
				isPickUp = true;
			}
		}
		
		if (button.getButtonStat() == true && floor.getFloorNum()<this.tarFloor) {
			if (this.elevqueue.contains(this.curFloor)) {
				button.setButtonStat(false);
				System.out.println(this.direction);
				printElevator(this.curFloor, button.getButtonTime());
				isPickUp = true;
			}
		}
	}
	

	@Override
	public void run() {
		this.status = Status.RUNNING;
		if (floorqueue.getQueueSize() > 0)
			this.tarFloor = this.floorqueue.getQueue(0).getFloor();
		else if (elevqueue.getQueueSize() > 0)
			this.tarFloor = this.elevqueue.getQueue(0).getFloor();
		
		if (this.tarFloor > this.curFloor) {
			moveUp();
		}
		else if (this.tarFloor < this.curFloor) {
			moveDown();
		}
		else if (this.tarFloor == this.curFloor) {
			doorMove();
		}
		this.status = Status.IDLE;
		elevThread = null;
		return;
	}
	
	public void start() {
		if (elevThread == null) {
			elevThread = new Thread (this);
			elevThread.start();
		}
	}
	
	public boolean repOK(){
		if (floorqueue.getQueueSize() < 0 || elevqueue.getQueueSize() < 0)
			return false;
		return true;
	}
}

class Elevators {
	private ArrayList<Elevator> elevators = new ArrayList<Elevator>();
	
	public boolean addElevator (int elevnum) {
		/**
		 * @REQUIRES: elevnum;
		 * @MODIFIES: this.elevators;
		 * @EFFECTS: 
		 * (\result==false)==>(\old(\this).elevators.contains(elevnum)==true)
		 * (\this.elevators.size == \old(\this).elevators.size+1) && (\this.elevators.contains(elevnum)==true)&&(\result==true);
		 */
		elevators.add(new Elevator(elevnum));
		return true;
	}
	
	public Elevator getElevator (int i) {
		return elevators.get(i);
	}
	
	public void sortElevator() {
		Collections.sort(elevators);
	}
}

class ElevButton {
	int buttonnum;
	boolean on = false;
	double buttontime;
	
	public ElevButton(int buttonnum) {
		/**
		 * @REQUIRES:buttonnum;
		 * @MODIFIES:this;
		 * @EFFECTS:
		 * (\result = \this) && (\this.isEmpty());
		 * (\this.buttonnum == buttonnum);
		 */
		this.buttonnum = buttonnum;
	}
	
	public int getButtonNum() {
		return this.buttonnum;
	}
	
	public boolean getButtonStat() {
		return this.on;
	}
	
	public double getButtonTime() {
		return this.buttontime;
	}
	
	public void setButtonStat(boolean on) {
		this.on = on;
	}
	
	public synchronized void setButtonStat(boolean on, Elevator elev) {
		/**
		 * @REQUIRES:on, elev;
		 * @MODIFIES:this.on;
		 * @EFFECTS:
		 * (\this.on == true) ==> sched.addElevReq(new ElevRequest(\this.buttonnum, \this.buttontime, elevid);
		 */
		this.on = on;
		if (this.on == true) {
			try {
				if (elev.addElevReq(new ElevatorRequest(this.buttonnum, this.buttontime, elev.getElevNum())) == false)
					throw new Exception ("Cannot add query!");
			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
			if (elev.getElevStatus() == Status.IDLE)
				elev.start();
		}
	}
	
	public void setButtonTime(double time) {
		this.buttontime = time;
	}
}

class ElevButtons {
	private ArrayList<ElevButton> elevbuttons = new ArrayList<ElevButton>();
	
	public boolean addButton (int buttonnum) throws InvalidRequestException, SameRequestException {
		/**
		 * @REQUIRES: buttonnum;
		 * @MODIFIES: this.elevbuttons;
		 * @EFFECTS: 
		 * (\result==false)==>(\old(\this).elevbuttons.contains(buttonnum)==true)
		 * (\this.elevbuttons.size == \old(\this).elevbuttons.size+1) && (\this.elevbuttons.contains(buttonnum)==true)&&(\result==true);
		 */
		elevbuttons.add(new ElevButton(buttonnum));
		return true;
	}
	
	public ElevButton getElevButton (int i) {
		return elevbuttons.get(i);
	}
}
