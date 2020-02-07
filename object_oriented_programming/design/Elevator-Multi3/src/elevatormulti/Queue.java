package elevatormulti;

import java.util.ArrayList;

public class Queue {
	/*private ArrayList<Request> queue = new ArrayList<Request>();
	private Request last;
	
	public boolean addQueue (Request req) throws InvalidRequestException, SameRequestException {
		queue.add(req);
		return true;
	}
	
	public boolean removeQueue (int i) throws CannotRemoveException {
		try {
			if ((i < 0)	|| i>=queue.size()|| queue.size() == 0){
	            throw new CannotRemoveException ("Remove index is out of array bounds!");
			}
			queue.remove(i);
			return true;
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
			return false;
		}
	}
	
	public Request getQueue (int i) {
		return queue.get(i);
	}
	
	public int getQueueSize () {
		return queue.size();
	}*/
}

class FloorQueue {
	private ArrayList<FloorRequest> floorqueue = new ArrayList<FloorRequest>();
	private FloorRequest last;
	
	public boolean addQueue (FloorRequest req) throws InvalidRequestException, SameRequestException {
		try {
			if ((req.getDir() == Direction.DOWN && req.getFloor() == 1) || (req.getDir() == Direction.UP && req.getFloor() == 20)) {
				throw new InvalidRequestException ("INVALID ");
			}
			if (floorqueue.size() >= 1) {
				last = floorqueue.get(floorqueue.size()-1);
				if (req.getFloor() == last.getFloor() && req.getDir() == last.getDir()) {
					throw new SameRequestException ("SAME ");
				}
			}
			floorqueue.add(req);
			return true;
		}
		catch (Exception except) {
			System.out.println(except.getMessage() + "[FR" + ", " + req.getFloor() + ", " + req.getDir().toString() + ", " + req.getTime() + "]");
			return false;
		}
	}
	
	public boolean removeQueue (int i) throws CannotRemoveException {
		try {
			if ((i < 0)	|| i>=floorqueue.size()|| floorqueue.size() == 0){
	            throw new CannotRemoveException ("Remove index is out of array bounds!");
			}
			floorqueue.remove(i);
			return true;
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
			return false;
		}
	}
	
	public FloorRequest getQueue (int i) {
		return floorqueue.get(i);
	}
	
	public int getQueueSize () {
		return floorqueue.size();
	}
}

class ElevatorQueue {
	private ArrayList<ElevatorRequest> elevqueue = new ArrayList<ElevatorRequest>();
	private ElevatorRequest last;
	
	public boolean addQueue (ElevatorRequest req) throws InvalidRequestException, SameRequestException {
		try {
			if (req.getFloor() > 20 || req.getFloor() < 1) {
				throw new InvalidRequestException ("INVALID ");
			}
			if (elevqueue.size() >= 1) {
				last = elevqueue.get(elevqueue.size()-1);
				if (req.getFloor() == last.getFloor() && req.getElevID() == last.getElevID()) {
					throw new SameRequestException ("SAME ");
				}
			}
			elevqueue.add(req);
			return true;
		}
		catch (Exception except) {
			System.out.println(except.getMessage() + "[ER" + ", " + req.getFloor() + ", " + req.getTime() + "]");
			return false;
		}
	}
	
	public boolean removeQueue (int i) throws CannotRemoveException {
		try {
			if ((i < 0)	|| i>=elevqueue.size()|| elevqueue.size() == 0){
	            throw new CannotRemoveException ("Remove index is out of array bounds!");
			}
			elevqueue.remove(i);
			return true;
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
			return false;
		}
	}
	
	public ElevatorRequest getQueue (int i) {
		return elevqueue.get(i);
	}
	
	public int getQueueSize () {
		return elevqueue.size();
	}
}
