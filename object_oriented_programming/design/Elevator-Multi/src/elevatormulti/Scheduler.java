package elevatormulti;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;

public class Scheduler {
	/*overview: Scheduler is the base scheduler. This class only initialize things like creating the
	 * floors along with their buttons and elevators along with their buttons too. Scheduler also
	 * initialize the floor queue that will be taken by the ALS Scheduler for later use.
	*/
	private Floors floors = new Floors();
	private Elevators elevators = new Elevators();
	private FloorQueue floorqueue = new FloorQueue();
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
	
	public synchronized boolean addFloorReq(FloorRequest req) throws InvalidRequestException, SameRequestException {
		/**
		 * @REQUIRES: req (FloorRequest);
		 * @MODIFIES: this.floorqueue;
		 * @EFFECTS: floorqueue.addQueue(req);
		 */
		return floorqueue.addQueue(req);
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
	
	public void setPickUp(boolean isPickUp) {
		this.isPickUp = isPickUp;
	}
	
	public boolean getPickUp() {
		return this.isPickUp;
	}
}

class ALS extends Scheduler implements Runnable {
	/*overview: ALS Scheduler is the one that actually runs the system. ALS (A Little Smart) will determine
	 * whether a request could be processed now or not, which elevator will take it, is it a pickup request.
	 * The request itself is taken from the floor request queue initialized in the Scheduler class.
	 * To see which elevator could take the request, it will see which elevator is available to process
	 * that request as a pickup as this is first priority. If many can do that, then it will choose the one
	 * with less movement points. If none is available then it will see which elevator is IDLE. If none is idle
	 * then the request will have to wait until at least one is available. If the request is taken to be processed
	 * then the floor request queue of the Scheduler will have to remove that request from the queue, marking it
	 * as done/processed.
	*/
	Scheduler sched;
	Thread ALSThread;
	ScheduledExecutorService exe = Executors.newSingleThreadScheduledExecutor();
	private FloorQueue floorqueue;
	private FloorRequest curFloorReq;
	private Elevators elevators;
	private Elevator elevator;
	private int i;
	private int floor;
	private String dir;
	
	public ALS(Scheduler sched) {
		/**
		 * @REQUIRES:sched;
		 * @MODIFIES:this;
		 * @EFFECTS:
		 * (\result = \this) && (\this.isEmpty());
		 * (\this.sched == sched);
		 */
		this.sched = sched;
		this.elevators = sched.getElevators();
		this.floorqueue = sched.getFloorQueue();
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		for (i = 0; i < 3; i++) {
			elevators.getElevator(i).setData(this.sched);
		}
		
		elevators.sortElevator();
		if (sched.getFloorQueue().getQueueSize() > 0) {
			curFloorReq = floorqueue.getQueue(0);
			floor = curFloorReq.getFloor();
			dir = curFloorReq.getDir().toString();
			
			try {
				for (i = 0; i < 3; i++) {
					if (elevators.getElevator(i).getElevStatus() == Status.RUNNING) {
						elevator = elevators.getElevator(i);
						if (dir.equals(elevator.getDir())) {
							if (dir.equals("UP") && floor < elevator.getTargetFloor()) {
								if (floor > elevator.getCurFloor()) {
									elevator.addFloorReq(curFloorReq);
									try {
										floorqueue.removeQueue(0);
									} catch (Exception except) {
										System.out.print(except.getMessage());
									}
								}
							}
							else if (dir.equals("DOWN") && floor > elevator.getTargetFloor()) {
								if (floor < elevator.getCurFloor()) {
									elevator.addFloorReq(curFloorReq);
									try {
										floorqueue.removeQueue(0);
									} catch (Exception except) {
										System.out.print(except.getMessage());
									}
								}
							}
						}
					}
					else if (elevators.getElevator(i).getElevStatus() == Status.IDLE) {
						elevator = elevators.getElevator(i);
						elevator.addFloorReq(curFloorReq);
						try {
							floorqueue.removeQueue(0);
						} catch (Exception except) {
							System.out.print(except.getMessage());
						}
						elevator.start();
						break;
					}
				}
				
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