package elevatormulti;

import java.util.ArrayList;

public class Elevator implements Movement{	
	OutputHandler output = new OutputHandler();
	
	private double moveTime = 3.0;
	private double doorTime = 6.0;
	
	private int elevnum;
	private int point = 0;
	private int curFloor = 1;
	private double elevTime = System.currentTimeMillis() * 0.001;
	private String direction = "STILL";
	private Status status = Status.IDLE;
	private ElevButtons elevbuttons = new ElevButtons();
	
	public Elevator(int elevnum) {
		this.elevnum = elevnum;
	}
	
	public int getElevNum() {
		return this.elevnum;
	}
	
	public int getCurFloor() {
		return this.curFloor;
	}
	
	public double getElevTime() {
		return this.elevTime;
	}
	
	public String getDir() {
		return this.direction;
	}
	
	public Status getElevStatus() {
		return this.status;
	}
	
	public ElevButtons getElevButtons() {
		return this.elevbuttons;
	}
	
	public void setCurFloor(int floor) {
		this.curFloor = floor;
	}
	
	public void setDirection(String dir) {
		this.direction = dir;
	}
	
	public void setElevTime(double time) {
		this.elevTime = time;
	}
	
	public void addElevTime() {
		this.elevTime += this.doorTime;
	}
	
	public void setElevStatus(Status status) {
		this.status = status;
	}
	
	public void printFloor(FloorRequest req) {
		int target = req.getFloor();
		double time = req.getTime();
		String dir = req.getDir().toString();
		
		System.out.printf("[FR, %d, %s, %.0f] / (%d, %s, %.1f)\n", target, dir, time, this.curFloor, this.direction, this.elevTime);
		output.writeFloor(target, dir, time, this.elevnum, this.curFloor, this.direction, this.point, this.elevTime);
	}
	
	public void printElevator(ElevatorRequest req) {
		int target = req.getFloor();
		double time = req.getTime();
		System.out.printf("[ER, %d, %.0f] / (%d, %s, %.1f)\n", target, time, this.curFloor, this.direction, this.elevTime);
		output.writeElev(target, time, this.elevnum, this.curFloor, this.direction, this.point, this.elevTime);
	}
	
	public void printFloor(int target, double time, String dir) {
		System.out.printf("[FR, %d, %s, %.0f] / (%d, %s, %.1f)\n", target, dir, time, this.curFloor, this.direction, this.elevTime);
		output.writeFloor(target, dir, time, this.elevnum, this.curFloor, this.direction, this.point, this.elevTime);
	}
	
	public void printElevator(int target, double time) {
		System.out.printf("[ER, %d, %.0f] / (%d, %s, %.1f)\n", target, time, this.curFloor, this.direction, this.elevTime);
		output.writeElev(target, time, this.elevnum, this.curFloor, this.direction, this.point, this.elevTime);
	}
	
	public double countTime(int floor, double time) {
		return (time + ((floor-this.curFloor) * this.moveTime));
	}

	@Override
	public boolean moveUp(int floor, double time) {
		this.curFloor += 1;
		this.elevTime += this.moveTime;
		return true;
	}

	@Override
	public boolean moveDown(int floor, double time) {
		this.curFloor -= 1;
		this.elevTime += this.moveTime;
		return true;
	}

	@Override
	public boolean doorMove() {
		this.direction = "STILL";
		this.elevTime += this.doorTime;
		return true;
	}
	
}

class Elevators {
	private ArrayList<Elevator> elevators = new ArrayList<Elevator>();
	
	public boolean addElevator (int elevnum) {
		elevators.add(new Elevator(elevnum));
		return true;
	}
	
	public Elevator getElevator (int i) {
		return elevators.get(i);
	}
}

class ElevButton {
	int buttonnum;
	boolean on = false;
	double buttontime;
	
	public ElevButton(int buttonnum) {
		this.buttonnum = buttonnum;
	}
	
	public int getButtonNum() {
		return this.buttonnum;
	}
	
	public boolean getButtonStat() {
		return this.on;
	}
	
	public double getButtonTime() {
		return this.buttontime;
	}
	
	public void setButtonStat(boolean on) {
		this.on = on;
	}
	
	public void setButtonTime(double time) {
		this.buttontime = time;
	}
}

class ElevButtons {
	private ArrayList<ElevButton> elevbuttons = new ArrayList<ElevButton>();
	
	public boolean addButton (int buttonnum) throws InvalidRequestException, SameRequestException {
		elevbuttons.add(new ElevButton(buttonnum));
		return true;
	}
	
	public ElevButton getElevButton (int i) {
		return elevbuttons.get(i);
	}
}
