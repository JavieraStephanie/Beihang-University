package taxi;

import java.util.ArrayList;

public class Queue {
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
			if (queue.size() >= 1) {
				last = queue.get(queue.size()-1);
				if (req.getSrc() == last.getSrc()) {
					throw new SameRequestException ("SAME ");
				}
			}
			if (req.getSrc() == req.getDst()) {
				throw new Exception ("Destination and Source is the same!");
			}
			queue.add(req);
			return true;
		}
		catch (Exception except) {
			System.out.println(except.getMessage());
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
