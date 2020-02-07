package taxi;

import java.util.Queue;

public class RequestHandler {
	private Queue<Request> reqqueue;
	
	public Queue<Request> getQueue(){
		return this.reqqueue;
	}

}
