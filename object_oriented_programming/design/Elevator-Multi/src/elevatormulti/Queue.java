package elevatormulti;

import java.util.ArrayList;

public class Queue {
}

class FloorQueue {
	/*overview: FloorQueue is a queue that records all the floor requests created into the system.
	*/
	private ArrayList<FloorRequest> floorqueue = new ArrayList<FloorRequest>();
	private FloorRequest last;
	
	public synchronized boolean addQueue (FloorRequest req) throws InvalidRequestException, SameRequestException {
		/**
		 * @REQUIRES: req (Request);
		 * @MODIFIES: this.floorqueue;
		 * @EFFECTS: 
		 * (\result==false)==>(\old(\this).floorqueue.contains(req)==true)
		 * (\this.floorqueue.size == \old(\this).floorqueue.size+1) && (\this.floorqueue.contains(req)==true)&&(\result==true);
		 */
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
	
	public synchronized boolean removeQueue (int i) throws CannotRemoveException {
		/**
		 * @REQUIRES: i (int);
		 * @MODIFIES: this.floorqueue;
		 * @EFFECTS: 
		 * (this.floorqueue.size == \old(\this.floorqueue).size-1);
		 * (\forall int e; e != i; this.floorqueue.contains(e) == \old(this.floorqueue).contains(e));
		 * exceptional_behaviour(CannotRemoveException("Remove index is out of array bounds!"));
		 */
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
	
	public synchronized FloorRequest getQueue (int i) {
		return floorqueue.get(i);
	}
	
	public synchronized int getQueueSize () {
		return floorqueue.size();
	}
	
	public synchronized boolean contains(int tarFloor, String dir) {
		/**
		 * @REQUIRES: tarFloor, dir;
		 * @MODIFIES: None;
		 * @EFFECTS: 
		 * (\forall int i; this.floorqueue.contains(tarFloor, dir) ==> (\result == true);
		 * (\result == false);
		 */
		for (int i = 0; i < floorqueue.size(); i++) {
			if (floorqueue.get(i).getFloor() == tarFloor && floorqueue.get(i).getDir().toString().equals(dir)) {
				this.floorqueue.remove(i);
				return true;
			}
		}
		return false;
	}
}

class ElevatorQueue {
	/*overview: ElevatorQueue is a queue that records all the elevator requests created into the system.
	*/
	private ArrayList<ElevatorRequest> elevqueue = new ArrayList<ElevatorRequest>();
	private ElevatorRequest last;
	
	public synchronized boolean addQueue (ElevatorRequest req) throws InvalidRequestException, SameRequestException {
		/**
		 * @REQUIRES: req (Request);
		 * @MODIFIES: this.elevqueue;
		 * @EFFECTS: 
		 * (\result==false)==>(\old(\this).elevqueue.contains(req)==true)
		 * (\this.elevqueue.size == \old(\this).elevqueue.size+1) && (\this.elevqueue.contains(req)==true)&&(\result==true);
		 */
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
	
	public synchronized boolean removeQueue (int i) throws CannotRemoveException {
		/**
		 * @REQUIRES: i (int);
		 * @MODIFIES: this.elevqueue;
		 * @EFFECTS: 
		 * (this.elevqueue.size == \old(\this.elevqueue).size-1);
		 * (\forall int e; e != i; this.elevqueue.contains(e) == \old(this.elevqueue).contains(e));
		 * exceptional_behaviour(CannotRemoveException("Remove index is out of array bounds!"));
		 */
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
	
	public synchronized ElevatorRequest getQueue (int i) {
		return elevqueue.get(i);
	}
	
	public synchronized int getQueueSize () {
		return elevqueue.size();
	}
	
	public synchronized boolean contains(int tarFloor) {
		/**
		 * @REQUIRES: tarFloor;
		 * @MODIFIES: None;
		 * @EFFECTS: 
		 * (\forall int i; this.elevqueue.contains(tarFloor) ==> (\result == true);
		 * (\result == false);
		 */
		for (int i = 0; i < elevqueue.size(); i++) {
			if (elevqueue.get(i).getFloor() == tarFloor) {
				this.elevqueue.remove(i);
				return true;
			}
		}
		return false;
	}
}
