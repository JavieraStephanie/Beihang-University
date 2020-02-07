package elevatorals;

import java.util.ArrayList;

class InvalidRequestException extends Exception {
	private static final long serialVersionUID = 1L;

	public InvalidRequestException(String message) {
		super(message);
	}
}

class SameRequestException extends Exception {
	private static final long serialVersionUID = 1L;

	public SameRequestException(String message) {
		super(message);
	}
}

class CannotRemoveException extends Exception {
	private static final long serialVersionUID = 1L;

	public CannotRemoveException(String message) {
		super(message);
	}
}

public class Queue {
	/*@Overview: Queue is the ArrayList that saves all request inputed by the user from System.in.
	 * Requests are divided by two types: FR and ER requests. The requests in the queue is ALWAYS sorted
	 * based on the request time.
	 */
	
	private ArrayList<Request> queue = new ArrayList<Request>();
	private Request last;
	
	public boolean addQueue (Request req) throws InvalidRequestException, SameRequestException {
		/**
		 * Description: Adds new req to queue;
		 * @REQUIRES: this.queue != NULL;
		 * @MODIFIES: this.queue;
		 * @EFFECTS: 
		 * (\result==false)==>(\old(\this).contains(req)==true)
		 * (\this.size == \old(\this).size+1) && (\this.contains(req)==true)&&(\result==true);
		 */
		
		try {
			if ((req.getFloor() > 10 || req.getFloor() < 1) || (req.getDir() == Direction.DOWN && req.getFloor() == 1) || req.getDir() == Direction.UP && req.getFloor() == 10) {
				throw new InvalidRequestException ("INVALID ");
			}
			if (queue.size() >= 1) {
				last = queue.get(queue.size()-1);
				if (req.getType().equals(last.getType()) && req.getFloor() == last.getFloor() && req.getDir() == last.getDir()) {
					throw new SameRequestException ("SAME ");
				}
			}
			queue.add(req);
			return true;
		}
		catch (Exception except) {
			System.out.println(except.getMessage() + "[" + req.getType() + ", " + req.getFloor() + ", " + req.getDir().toString() + ", " + req.getTime() + "]");
			return false;
		}
	}
	
	public boolean removeQueue (int i) throws CannotRemoveException {
		/**
		 * Description: Removes i(th) element from queue;
		 * @REQUIRES: this.queue != {};
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
