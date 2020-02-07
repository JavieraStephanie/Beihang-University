package elevatorals;

public class Scheduler {
	private Floor floor = new Floor();
	private Elevator elevator = new Elevator();
	private Queue queue = new Queue();
	private boolean isPickUp = false;
	
	public boolean addReq(Request req) throws InvalidRequestException, SameRequestException {
		/**
		 * @REQUIRES: req != NULL;
		 * @MODIFIES: this.queue;
		 * @EFFECTS: \result == \this.queue.addQueue(req);
		 */
		return queue.addQueue(req);
	}
	
	public Floor getFloor() {
		return this.floor;
	}
	
	public Elevator getElevator() {
		return this.elevator;
	}
	
	public Queue getQueue() {
		return this.queue;
	}
	
	public void setPickUp(boolean isPickUp) {
		this.isPickUp = isPickUp;
	}
	
	public boolean getPickUp() {
		return this.isPickUp;
	}
}

class ALS extends Scheduler {
	/*overview: ALS Scheduler manages the requests got from the System.in and give it to the Elevator in terms of requests. 
	 * Elevator has to request a token to use service. Each Token represents a request of service.  
	 * All requests are managed in queues according to the time the request is created. For each of the requests, 
	 * ALS Scheduler will ask the Elevator to take it, also considering if there are pickup requests.
	 * In general, data managed in this class can be defined as (Queue).
	 * 
	 * Please note that the following is just for implementing, not for using this class. 
	 * Abstract Function can be defined as:
	 * AF(tm) = (Queue), where
	 * Queue=tm.curReq
	*/
	public void removeUnused(Queue queue, Request curReq, Elevator elevator, Floor floor) throws CannotRemoveException {
		/**
		 * @REQUIRES:
		 * @MODIFIES:
		 * @EFFECTS:
		 */
		if (curReq.getType().equals("FR")) {
			if (curReq.getTime() > elevator.getElevTime() + elevator.getDoorTime()) {
				queue.removeQueue(0);
			}
		}
		
		if (curReq.getDir() == Direction.DOWN) {
			if(floor.getFloorNum() == curReq.getFloor() && floor.getDownStatus() == true) {
				if(curReq.getTime() < elevator.getElevTime() + elevator.getDoorTime()) {
					queue.removeQueue(0);
				}
			}
			else {
				floor.setFloorNum(curReq.getFloor());
				floor.setDownStatus(true);
			}
		}
		
		else if (curReq.getDir() == Direction.UP) {
			if(floor.getFloorNum() == curReq.getFloor() && floor.getUpStatus() == true) {
				if(curReq.getTime() < elevator.getElevTime() + elevator.getDoorTime()) {
					queue.removeQueue(0);
				}
			}
			else {
				floor.setFloorNum(curReq.getFloor());
				floor.setUpStatus(true);
			}
		}
	}
	
	public void pickUp(Queue queue, Elevator elevator) throws CannotRemoveException {
		/**
		 * @REQUIRES:
		 * @MODIFIES:
		 * @EFFECTS:
		 */
		Request next;
		if (queue.getQueueSize() > 1) {
			next = queue.getQueue(1);
			if (next.getType().equals("FR")) {
				if (elevator.getCurFloor() == next.getFloor() && elevator.getDir().equals(next.getDir().toString()) && next.getTime() <= elevator.getElevTime() + 1.0) {
					elevator.print(next);
					queue.removeQueue(1);
					setPickUp(true);
				};
			}
			else if (next.getType().equals("ER")) {
				if (elevator.getCurFloor() == next.getFloor() && next.getTime() <= elevator.getElevTime()) {
					elevator.print(next);
					queue.removeQueue(1);
					setPickUp(true);
				};
			}
		}
	}
	
	public void runElevator() throws Exception {
		/**
		 * @REQUIRES: None;
		 * @MODIFIES:
		 * @EFFECTS:
		 */
		Queue queue = getQueue();
		Elevator elevator = getElevator();
		Floor floor = getFloor();
		Request curReq = queue.getQueue(0);
		
		if(curReq.getTime() != 0) {
			System.out.println("Starting time should be 0!");
			return;
		}
		
		removeUnused(queue, curReq, elevator, floor);
		
		while (queue.getQueueSize() > 0) {
			curReq = queue.getQueue(0);
			int targetFloor = curReq.getFloor();
			
			if(elevator.getCurFloor() < targetFloor) {
				elevator.setDirection("UP");
				while (elevator.getCurFloor() < targetFloor) {
					elevator.moveUp();
					pickUp(queue, elevator);
					if (getPickUp()) {
						if (elevator.getCurFloor() == targetFloor) {
							setPickUp(false);
							continue;
						}
						elevator.addElevTime(elevator.getDoorTime());
						setPickUp(false);
					}
				}
				elevator.print(curReq);
				elevator.addElevTime(elevator.getDoorTime());
			}
			else if(elevator.getCurFloor() > targetFloor) {
				elevator.setDirection("DOWN");
				while (elevator.getCurFloor() > targetFloor) {
					elevator.moveDown();
					pickUp(queue, elevator);
					if (getPickUp()) {
						elevator.addElevTime(elevator.getDoorTime());
					}
					setPickUp(false);
				}
				elevator.print(curReq);
				elevator.addElevTime(elevator.getDoorTime());
			}
			else if (elevator.getCurFloor() == targetFloor){
				elevator.setDirection("STILL");
				elevator.doorMove();
				elevator.print(curReq);
			}
			queue.removeQueue(0);
		}
	}
}