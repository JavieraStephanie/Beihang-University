package elevatorals;

public class Elevator implements Movement{
	/*@Overview: Elevator is the machine that runs request given by the ALS Scheduler. 
	 * The Elevator records it's movement direction and the current virtual time of the machine.
	 * It moves up or down according to the request it's processing and will move the door (open and close) after each request
	 * is processed.
	 * After a request is done being processed, that record will be printed out via System.out.
	 */
	
	private int curFloor = 1;
	private double elevTime = 0;
	private String direction = "STILL";
	private double moveTime = 0.5;
	private double doorTime = 1.0;
	
	public int getCurFloor() {
		return this.curFloor;
	}
	
	public double getElevTime() {
		return this.elevTime;
	}
	
	public String getDir() {
		return this.direction;
	}
	
	public double getMoveTime() {
		return this.moveTime;
	}
	
	public double getDoorTime() {
		return this.doorTime;
	}
	
	public void setCurFloor(int floor) {
		this.curFloor = floor;
	}
	
	public void setDirection(String dir) {
		this.direction = dir;
	}
	
	public void addElevTime(double time) {
		this.elevTime += time;
	}
	
	public void print(Request req) {
		String type = req.getType();
		int target = req.getFloor();
		String dir = req.getDir().toString();
		double time = req.getTime();
		
		if (type.equals("FR")) {
			System.out.printf("[%s, %d, %s, %.0f] / (%d, %s, %.1f)\n", type, target, dir, time, this.curFloor, this.direction, this.elevTime);
		}
		else if (type.equals("ER")) {
			System.out.printf("[%s, %d, %.0f] / (%d, %s, %.1f)\n", type, target, time, this.curFloor, this.direction, this.elevTime);
		}
	}

	@Override
	public boolean moveUp() {
		/**
		 * @REQUIRES: floor, time;
		 * @MODIFIES: this;
		 * @EFFECTS: (\result == true) ==> (\this.curFloor == \old.curFloor+1) && (\this.elevTime == \old.elevTime + \this.moveTime);
		 */
		if (getCurFloor() == 10) {
			return false;
		}
		this.curFloor += 1;
		addElevTime(this.moveTime);
		return true;
	}

	@Override
	public boolean moveDown() {
		/**
		 * @REQUIRES: floor, time;
		 * @MODIFIES: this;
		 * @EFFECTS: (\result == true) ==> (\this.curFloor == \old.curFloor-1) && (\this.elevTime == \old.elevTime + \this.moveTime);
		 */
		if (getCurFloor() == 1) {
			return false;
		}
		this.curFloor -= 1;
		addElevTime(this.moveTime);
		return true;
	}

	@Override
	public boolean doorMove() {
		/**
		 * @REQUIRES: None;
		 * @MODIFIES: this;
		 * @EFFECTS: (\result == true) ==> (\this.direction == "STILL") && (\this.elevTime == \old.elevTime + \this.doorTime);
		 */
		this.direction = "STILL";
		addElevTime(this.doorTime);
		return true;
	}
	
}
