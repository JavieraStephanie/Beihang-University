package taxi;

import java.util.ArrayList;

public class Queue {
	private ArrayList<Request> queue = new ArrayList<Request>();
	private Request last;
	
	public synchronized boolean addQueue (Request req) throws InvalidRequestException, SameRequestException {
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
	
	public synchronized boolean removeQueue (int i) throws CannotRemoveException {
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
	
	public synchronized Request getQueue (int i) {
		return queue.get(i);
	}
	
	public synchronized int getQueueSize () {
		return queue.size();
	}
}
