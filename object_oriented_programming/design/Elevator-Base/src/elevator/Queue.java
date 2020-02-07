package elevator;

import java.util.ArrayList;

class InvalidRequestException extends Exception {
	private static final long serialVersionUID = 1L;

	public InvalidRequestException(String message) {
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
	private ArrayList<Request> queue = new ArrayList<Request>();;
	
	public boolean addQueue (Request req) {
		try {
			if ((req.getFloor() > 10 || req.getFloor() < 1) || (req.getDir() == Direction.DOWN && req.getFloor() == 1) || req.getDir() == Direction.UP && req.getFloor() == 10) {
				throw new InvalidRequestException ("Invalid data in request, request won't be processed!");
				//System.out.println("Invalid data in request, request won't be processed!");
				//return false;
			}
			queue.add(req);
			return true;
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
			return false;
		}
	}
	
	public boolean removeQueue (int i) {
		queue.remove(i);
		return true;
	}
	
	public Request getQueue (int i) {
		return queue.get(i);
	}
	
	public int getQueueSize () {
		return queue.size();
	}
	
}
