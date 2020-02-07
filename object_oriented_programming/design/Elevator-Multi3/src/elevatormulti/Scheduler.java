package elevatormulti;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;

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

class ALS extends Scheduler implements Runnable {
	Scheduler sched;
	Thread ALSThread;
	ScheduledExecutorService exe = Executors.newSingleThreadScheduledExecutor();
	private Floors floors;
	private FloorQueue floorqueue;
	private FloorRequest curFloorReq;
	private Elevators elevators;
	private Elevator elevator;
	private ElevButtons elevbuttons;
	private ElevatorQueue elevqueue;
	private ElevatorRequest curElevReq;
	private int i;
	private int floor;
	private int elevid;
	private String dir;
	private double time;
	
	public ALS(Scheduler sched) {
		this.sched = sched;
		this.floors = sched.getFloors();
		this.elevators = sched.getElevators();
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		if (sched.getFloorQueue().getQueueSize() > 0) {
			floorqueue = sched.getFloorQueue();
			curFloorReq = floorqueue.getQueue(0);
			floor = curFloorReq.getFloor();
			dir = curFloorReq.getDir().toString();
			time = curFloorReq.getTime();
			
			try {
				floorqueue.removeQueue(0);
			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
			
			if (dir == "DOWN") {
				floors.getFloor(floor-1).setDownStatus(true);
				floors.getFloor(floor-1).setDownTime(time);
			}
			else if (dir == "UP") {
				floors.getFloor(floor-1).setUpStatus(true);
				floors.getFloor(floor-1).setUpTime(time);
			}
			
			try {
				for (i = 0; i < 3; i++) {
					if (elevators.getElevator(i).getElevStatus() == Status.RUNNING) {
						elevators.getElevator(i).pickUp();
						if (elevators.getElevator(i).getPickUp()) {
							break;
						}
					}
					else if (elevators.getElevator(i).getElevStatus() == Status.IDLE) {
						elevator = elevators.getElevator(i);
						elevator.setData(floor, curFloorReq, this.sched);
						System.out.println(elevator.getElevNum());
						elevator.start();
						break;
					}
				}
				
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
			elevator = elevators.getElevator(elevid-1);
			dir = elevator.getDir();
			elevbuttons = elevator.getElevButtons();
			
			try {
				elevqueue.removeQueue(0);
			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
			
			if (floor > elevator.getCurFloor() && dir == "UP") {
				elevbuttons.getElevButton(floor-1).setButtonStat(true);
				elevbuttons.getElevButton(floor-1).setButtonTime(time);
			}
			else if (floor < elevator.getCurFloor() && dir == "DOWN") {
				elevbuttons.getElevButton(floor-1).setButtonStat(true);
				elevbuttons.getElevButton(floor-1).setButtonTime(time);
			}
			
			System.out.println(floor);
			try {
				elevator.setData(floor, curElevReq, this.sched);
				if (elevator.getElevStatus() == Status.IDLE)
					elevator.start();
				
			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
		}
	}
	
	public void start() {
		ALSThread = new Thread (this);
		ALSThread.start();
	}
}