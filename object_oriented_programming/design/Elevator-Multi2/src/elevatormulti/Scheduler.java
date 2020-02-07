package elevatormulti;

public class Scheduler {
	private Floors floors = new Floors();
	private Elevators elevators = new Elevators();
	private FloorQueue floorqueue = new FloorQueue();
	private ElevatorQueue elevqueue = new ElevatorQueue();
	private boolean isPickUp = false;
	
	public void initThings() throws InvalidRequestException, SameRequestException {
		for (int i = 1; i <= 20; i++) {
			floors.addFloor(i);
		}
		
		for (int i = 1; i <= 3; i++) {
			elevators.addElevator(i);
			for (int j = 1; j <= 20; j++) {
				elevators.getElevator(i-1).getElevButtons().addButton(j);
			}
		}
	}
	
	public boolean addFloorReq(FloorRequest req) throws InvalidRequestException, SameRequestException {
		return floorqueue.addQueue(req);
	}
	
	public boolean addElevReq(ElevatorRequest req) throws InvalidRequestException, SameRequestException {
		return elevqueue.addQueue(req);
	}
	
	public Floors getFloors() {
		return this.floors;
	}
	
	public Elevators getElevators() {
		return this.elevators;
	}
	
	public FloorQueue getFloorQueue() {
		return this.floorqueue;
	}
	
	public ElevatorQueue getElevQueue() {
		return this.elevqueue;
	}
	
	public void setPickUp(boolean isPickUp) {
		this.isPickUp = isPickUp;
	}
	
	public boolean getPickUp() {
		return this.isPickUp;
	}
}

class ALS extends Scheduler {
	
	public void runSystem(Scheduler sched) {
		Floors floors = sched.getFloors();
		FloorQueue floorqueue;
		FloorRequest curFloorReq;
		Elevators elevators = sched.getElevators();
		ElevatorQueue elevqueue;
		ElevatorRequest curElevReq;
		int i;
		int floor;
		int elevid;
		Direction dir;
		double time;
		
		if (sched.getFloorQueue().getQueueSize() > 0) {
			floorqueue = sched.getFloorQueue();
			curFloorReq = floorqueue.getQueue(0);
			floor = curFloorReq.getFloor();
			dir = curFloorReq.getDir();
			time = curFloorReq.getTime();
			
			try {
				floorqueue.removeQueue(0);
			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
			
			if (dir == Direction.DOWN) {
				floors.getFloor(floor-1).setDownStatus(true);
				floors.getFloor(floor-1).setDownTime(time);
			}
			else if (dir == Direction.UP) {
				floors.getFloor(floor-1).setUpStatus(true);
				floors.getFloor(floor-1).setUpTime(time);
			}
			
			try {
				for (i = 0; i < 3; i++) {
					if (elevators.getElevator(i).getElevStatus() == Status.IDLE) {
						Elevator elevator = elevators.getElevator(i);
						elevator.setElevStatus(Status.RUNNING);
						takeReq(sched, elevator, floor, curFloorReq);
						break;
					}
				}
				
				/*if (i==3) {
					pickUp(curFloorReq, elevators);
				}*/
			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
		}
		
		else if (sched.getElevQueue().getQueueSize() > 0) {
			elevqueue = sched.getElevQueue();
			curElevReq = elevqueue.getQueue(0);
			floor = curElevReq.getFloor();
			elevid = curElevReq.getElevID();
			time = curElevReq.getTime();
			Elevator elevator = elevators.getElevator(elevid-1);
			String direction = elevator.getDir();
			ElevButtons elevbuttons = elevator.getElevButtons();
			
			if (floor > elevator.getCurFloor() && direction == "UP") {
				elevbuttons.getElevButton(floor-1).setButtonStat(true);
				elevbuttons.getElevButton(floor-1).setButtonTime(time);
			}
			else if (floor < elevator.getCurFloor() && direction == "DOWN") {
				elevbuttons.getElevButton(floor-1).setButtonStat(true);
				elevbuttons.getElevButton(floor-1).setButtonTime(time);
			}
			
			//runElev(elevator, floor, curElevReq);
		}
	}
	
	public void pickUp(Scheduler sched, Elevator elevator, int curFloor, int target) throws CannotRemoveException {
		Floors floors = sched.getFloors();
		Floor floor = floors.getFloor(curFloor-1);
		ElevButtons elevbuttons = elevator.getElevButtons();
		ElevButton button = elevbuttons.getElevButton(curFloor-1);
		
		if (elevator.getDir() == "UP" && floor.getUpStatus() == true && floor.getFloorNum()<target) {
			floor.setUpStatus(false);
			elevator.printFloor(curFloor, floor.getUpTime(), "UP");
			setPickUp(true);
		}
		
		else if (elevator.getDir() == "DOWN" && floor.getDownStatus() == true && floor.getFloorNum()>target) {
			floor.setDownStatus(false);
			elevator.printFloor(curFloor, floor.getDownTime(), "DOWN");
			setPickUp(true);
		}
		
		else if (button.getButtonStat() == true) {
			button.setButtonStat(false);
			elevator.printElevator(curFloor, button.getButtonTime());
			setPickUp(true);
		}
	}
	
	public void takeReq(Scheduler sched, Elevator elevator, int floor, FloorRequest curFloorReq) {
		elevator.setElevTime(curFloorReq.getTime());
		if (floor > elevator.getCurFloor()) {
			elevator.setDirection("UP");
			while (elevator.getCurFloor() < floor) {
				elevator.moveUp(floor, curFloorReq.getTime());
				try {
					pickUp(sched, elevator, elevator.getCurFloor(), floor);
				} catch (Exception except) {
					System.out.print(except.getMessage());
				}
				if (getPickUp()) {
					if (elevator.getCurFloor() == floor) {
						setPickUp(false);
						continue;
					}
					elevator.addElevTime();
					setPickUp(false);
				}
			}
			elevator.setElevStatus(Status.SERVING);
			elevator.printFloor(curFloorReq);
			elevator.addElevTime();
		}
		else if(elevator.getCurFloor() > floor) {
			elevator.setDirection("DOWN");
			while (elevator.getCurFloor() > floor) {
				elevator.moveDown(floor, curFloorReq.getTime());
			}
			elevator.setElevStatus(Status.SERVING);
			elevator.printFloor(curFloorReq);
			elevator.addElevTime();
		}
		else if (elevator.getCurFloor() == floor){
			elevator.setDirection("STILL");
			elevator.doorMove();
			elevator.setElevStatus(Status.SERVING);
			elevator.printFloor(curFloorReq);
		}
		
		elevator.setElevStatus(Status.IDLE);		
	}
}