package elevatorals;

public class Request {
	
	private String type = "FR";
	private int req_floor;
	private double req_time;
	private Direction direction;
	
	public Request(int floor, Direction dir, double time) {
		/**
		 * @REQUIRES:floor, dir, time;
		 * @MODIFIES:this;
		 * @EFFECTS:
		 * (\result = \this) && (\this.isEmpty());
		 * (\this.req_Floor == floor) && (\this.direction == dir) && (\this.req_time == time);
		 */
		this.req_floor = floor;
		this.direction = dir;
		this.req_time = time;
		
		if (dir == Direction.UP || dir == Direction.DOWN) {
			this.type = "FR";
		}
		else if (dir == Direction.STILL) {
			this.type = "ER";
		}
	}
	
	public String getType() {
		return this.type;
	}
	
	public int getFloor() {
		return this.req_floor;
	}
	
	public double getTime() {
		return this.req_time;
	}
	
	public Direction getDir() {
		return this.direction;
	}
}
