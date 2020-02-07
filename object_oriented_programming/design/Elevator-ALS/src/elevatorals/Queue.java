package elevatorals;

import java.util.ArrayList;

public class Queue {	
	private ArrayList<Request> queue = new ArrayList<Request>();
	private Request last;
	
	public boolean addQueue (Request req) throws InvalidRequestException, SameRequestException {
		/**
		 * @REQUIRES: req (Request);
		 * @MODIFIES: this.queue;
		 * @EFFECTS: 
		 * (\result==false)==>(\old(\this.queue).contains(req)==true)
		 * (\this.queue.size == \old(\this.queue).size+1) && (\this.queue.contains(req)==true)&&(\result==true);
		 */
		try {
			if ((req.getDir() == Direction.DOWN && req.getFloor() == 1) || (req.getDir() == Direction.UP && req.getFloor() == 10) || req.getFloor() < 1 || req.getFloor() > 10) {
				throw new InvalidRequestException ("INVALID ");
			}
			if (queue.size() >= 1) {
				last = queue.get(queue.size()-1);
				if (req.getFloor() == last.getFloor() && req.getDir() == last.getDir()) {
					throw new SameRequestException ("SAME ");
				}
			}
			queue.add(req);
			return true;
		}
		catch (Exception except) {
			System.out.println(except.getMessage() + "[FR" + ", " + req.getFloor() + ", " + req.getDir().toString() + ", " + req.getTime() + "]");
			return false;
		}
	}
	
	public boolean removeQueue (int i) throws CannotRemoveException {
		/**
		 * @REQUIRES: i (int);
		 * @MODIFIES: this.queue;
		 * @EFFECTS: 
		 * (this.queue.size == \old(\this.queue).size-1);
		 * (\forall int e; e != i; this.queue.contains(e) == \old(this.queue).contains(e));
		 * exceptional_behaviour(CannotRemoveException("Remove index is out of array bounds!"));
		 */
		
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
	}
	
}
