package elevator;

public class Scheduler {
	private Floor floor = new Floor();
	private Elevator elevator = new Elevator();
	private Queue queue = new Queue();
	
	public boolean addReq(Request req) {
		return queue.addQueue(req);
	}
	
	public void runElevator() throws Exception {
		Request curReq = queue.getQueue(0);
		if(curReq.getTime() != 0) {
			throw new Exception ("Starting time should be 0!");
		}
		
		while (queue.getQueueSize() > 0) {
			if (curReq.getDir() == Direction.DOWN || curReq.getDir() == Direction.UP) {
				if (curReq.getTime() > elevator.getNextTime()) {
					queue.removeQueue(0);
					continue;
				}
			}
			
			if (curReq.getDir() == Direction.DOWN) {
				if(floor.getFloorNum() == curReq.getFloor() && floor.getDownStatus() == true) {
					if(curReq.getTime() < elevator.getNextTime()) {
						queue.removeQueue(0);
						continue;
					}
				}
				else {
					floor.setFloorNum(curReq.getFloor());
					floor.setDownStatus(true);
				}
			}
			
			else if (curReq.getDir() == Direction.UP) {
				if(floor.getFloorNum() == curReq.getFloor() && floor.getUpStatus() == true) {
					if(curReq.getTime() < elevator.getNextTime()) {
						queue.removeQueue(0);
						continue;
					}
				}
				else {
					floor.setFloorNum(curReq.getFloor());
					floor.setUpStatus(true);
				}
			}
			
			elevator.moveElev(curReq);
			queue.removeQueue(0);
		}
	}

}
