package elevatormulti;

public class Request {
	/*overview: Request class basically is the base class for all requests. It has target floor and time the request is made.
	 * Both those values could be taken by other classes.
	 */
	private int req_floor;
	private double req_time;
	
	public Request(int req_floor, double req_time) {
		this.req_floor = req_floor;
		this.req_time = req_time;
	}
	
	public int getFloor() {
		return this.req_floor;
	}
	
	public double getTime() {
		return this.req_time;
	}
}

class FloorRequest extends Request {
	/*overview: FloorRequest is the request for only floor requests and this extends the base request model, Request class.
	 * This class adds a new value that should not be found in other request types, that is the direction.
	 * Only the floor request got a direction value.
	*/

	private Direction direction;
	
	public FloorRequest(int req_floor, double req_time, Direction direction) {
		super(req_floor, req_time);
		this.direction = direction;
	}
	
	public Direction getDir() {
		return this.direction;
	}
}

class ElevatorRequest extends Request {
	/*overview: ElevatorRequest is the request for only elevator requests and this extends the base request model, Request class.
	 * This class adds a new value that should not be found in other request types, that is the requested elevator ID.
	 * Only the elevator request got an elevID value, because it immediately knows which elevator should process the request.
	*/
	private int elevID;
	
	public ElevatorRequest(int req_floor, double req_time, int elevID) {
		super(req_floor, req_time);
		this.elevID = elevID;
	}
	
	public int getElevID() {
		return this.elevID;
	}
}