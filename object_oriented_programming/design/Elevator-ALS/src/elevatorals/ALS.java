package elevatorals;

public class ALS extends Scheduler {
	Scheduler sched;
	
	public ALS(Scheduler sched) {
		/**
		 * @REQUIRES:src (Point), dst (Point), req_time (double);
		 * @MODIFIES:this;
		 * @EFFECTS:(\result = \this) &&(\this.isEmpty());
		 */
		this.sched = sched;
	}
	
	public void pickUp(Queue queue, Elevator elevator) throws CannotRemoveException {
		/**
		 * @REQUIRES:queue, elevator;
		 * @MODIFIES:queue, this.sched.isPickUp;
		 * @EFFECTS:
		 * queue.size > 0 ==> 
		 * 	queue(1).type == "FR" ==> 
		 * 		(elevator.floor == queue(1).floor && elevator.dir == queue(1).dir && elevator.time <= queue(1).time) ==> queue.remove(1), \this.sched.isPickUp == true;
		 * 	queue(1).type == "ER" ==> 
		 * 		(elevator.floor == queue(1).floor && elevator.time <= queue(1).time) ==> queue.remove(1), \this.sched.isPickUp == true;
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
		 * @REQUIRES:None;
		 * @MODIFIES:this;
		 * @EFFECTS:
		 * queue.size > 0 ==> 
		 * 	elevator.floor < curReq.floor ==> moveUp ==> queue.remove(0);
		 * 	elevator.floor > curReq.floor ==> moveDown ==> queue.remove(0);
		 * 	elevator.floor == curReq.floor ==> doorMove ==> queue.remove(0);
		 */
		
		Queue queue = sched.getQueue();
		Elevator elevator = getElevator();
		Request curReq = queue.getQueue(0);
		
		if(curReq.getTime() != 0) {
			System.out.println("Starting time should be 0!");
			return;
		}
		
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
