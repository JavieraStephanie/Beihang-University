package elevator;

public class Elevator{
	private int curFloor = 1;
	private double elevTime = 0;
	private double nextTime = 0;
	private String direction = "STILL";
	private double moveTime = 0.5;
	private double doorTime = 1.0;
	
	public int getCurFloor() {
		return this.curFloor;
	}
	
	public double getElevTime() {
		return this.elevTime;
	}
	
	public double getNextTime() {
		return this.nextTime;
	}
	
	public void setCurFloor(int floor) {
		this.curFloor = floor;
	}
	
	public void setDirection(String dir) {
		this.direction = dir;
	}
	
	public void setElevTime(double time) {
		this.elevTime += time;
	}
	
	public void moveElev(Request req) {
		if(req.getFloor() < this.curFloor) {
			this.direction = "DOWN";
			this.elevTime = req.getTime() + ((this.curFloor-req.getFloor()) * this.moveTime);
			this.nextTime = this.elevTime + this.doorTime;
		}
		else if (req.getFloor() > this.curFloor) {
			this.direction = "UP";
			this.elevTime = req.getTime() + ((req.getFloor()-this.curFloor) * this.moveTime);
			this.nextTime = this.elevTime + this.doorTime;
		}
		else {
			this.direction = "STILL";
			this.elevTime = req.getTime() + this.doorTime;
			this.nextTime = this.elevTime;
		}
		this.curFloor = req.getFloor();
		
		print();
		return;
	}
	
	public void print() {
		System.out.println("(" + this.curFloor + ", " + this.direction + ", " + this.elevTime + ")");
	}
	
}
