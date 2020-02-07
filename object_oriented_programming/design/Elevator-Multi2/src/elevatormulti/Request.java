package elevatormulti;

public class Request {
	
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

	private int elevID;
	
	public ElevatorRequest(int req_floor, double req_time, int elevID) {
		super(req_floor, req_time);
		this.elevID = elevID;
	}
	
	public int getElevID() {
		return this.elevID;
	}
}