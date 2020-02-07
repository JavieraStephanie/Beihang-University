package elevatormulti;

import java.util.ArrayList;

public class Elevator implements Movement, Runnable{	
	OutputHandler output = new OutputHandler();
	Scheduler sched;
	
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
	private FloorRequest floorReq = null;
	private ElevatorRequest elevReq = null;
	private boolean isPickUp = false;
	
	public Elevator(int elevnum) {
		this.elevnum = elevnum;
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
	
	public void setCurFloor(int floor) {
		this.curFloor = floor;
	}
	
	public void setDirection(String dir) {
		this.direction = dir;
	}
	
	public void setElevTime(double time) {
		this.elevTime = time;
	}
	
	public void addElevTime() {
		//this.elevTime += this.doorTime;
		try {
			Thread.sleep(this.doorTime);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	public boolean getPickUp() {
		return this.isPickUp;
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
		output.writeElev(target, time, this.elevnum, this.curFloor, this.direction, this.point, this.elevTime);
	}
	
	public void printFloor(int target, double time, String dir) {
		System.out.printf("[FR, %d, %s, %.0f] / (%d, %s, %.1f)\n", target, dir, time, this.curFloor, this.direction, this.elevTime);
		output.writeFloor(target, dir, time, this.elevnum, this.curFloor, this.direction, this.point);
	}
	
	public void printElevator(int target, double time) {
		System.out.printf("[ER, %d, %.0f] / (%d, %s, %.1f)\n", target, time, this.curFloor, this.direction, this.elevTime);
		output.writeElev(target, time, this.elevnum, this.curFloor, this.direction, this.point, this.elevTime);
	}
	
	public double countTime(int floor, double time) {
		return (time + ((floor-this.curFloor) * this.moveTime));
	}
	
	public void setData(int floor, FloorRequest floorReq, Scheduler sched) {
		this.tarFloor = floor;
		this.floorReq = floorReq;
		this.sched = sched;
	}
	
	public void setData(int floor, ElevatorRequest elevReq, Scheduler sched) {
		this.tarFloor = floor;
		this.elevReq = elevReq;
		this.sched = sched;
	}
	
	@Override
	public boolean moveUp() {
		this.direction = "UP";
		while(this.curFloor < this.tarFloor) {
			try {
				Thread.sleep(this.moveTime);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			this.curFloor += 1;
			this.point += 1;
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
				addElevTime();
				isPickUp = false;
			}
		}
		if (floorReq != null) {
			printFloor(this.floorReq);
			this.floorReq = null;
		}
		if (elevReq != null) {
			printElevator(this.elevReq);
			this.elevReq = null;
		}
		addElevTime();
		return true;
	}

	@Override
	public boolean moveDown() {
		this.direction = "DOWN";
		while(this.curFloor > this.tarFloor) {
			try {
				Thread.sleep(this.moveTime);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			this.curFloor -= 1;
			this.point += 1;
		}
		printFloor(this.floorReq);
		addElevTime();
		return true;
	}

	@Override
	public boolean doorMove() {
		this.direction = "STILL";
		try {
			Thread.sleep(this.doorTime);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		return true;
	}
	
	public void pickUp() throws CannotRemoveException {
		Floors floors = this.sched.getFloors();
		Floor floor = floors.getFloor(this.curFloor-1);
		ElevButton button = this.elevbuttons.getElevButton(this.curFloor-1);
		
		if (this.direction.equals("UP") && floor.getUpStatus() == true && floor.getFloorNum()<this.tarFloor) {
			floor.setUpStatus(false);
			printFloor(this.curFloor, floor.getUpTime(), "UP");
			isPickUp = true;
		}
		
		else if (this.direction.equals("DOWN") && floor.getDownStatus() == true && floor.getFloorNum()>this.tarFloor) {
			floor.setDownStatus(false);
			printFloor(this.curFloor, floor.getDownTime(), "DOWN");
			isPickUp = true;
		}
		
		else if (button.getButtonStat() == true) {
			button.setButtonStat(false);
			printElevator(this.curFloor, button.getButtonTime());
			isPickUp = true;
		}
	}
	

	@Override
	public void run() {
		this.status = Status.RUNNING;
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
}

class Elevators {
	private ArrayList<Elevator> elevators = new ArrayList<Elevator>();
	
	public boolean addElevator (int elevnum) {
		elevators.add(new Elevator(elevnum));
		return true;
	}
	
	public Elevator getElevator (int i) {
		return elevators.get(i);
	}
}

class ElevButton {
	int buttonnum;
	boolean on = false;
	double buttontime;
	
	public ElevButton(int buttonnum) {
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
	
	public void setButtonTime(double time) {
		this.buttontime = time;
	}
}

class ElevButtons {
	private ArrayList<ElevButton> elevbuttons = new ArrayList<ElevButton>();
	
	public boolean addButton (int buttonnum) throws InvalidRequestException, SameRequestException {
		elevbuttons.add(new ElevButton(buttonnum));
		return true;
	}
	
	public ElevButton getElevButton (int i) {
		return elevbuttons.get(i);
	}
}
