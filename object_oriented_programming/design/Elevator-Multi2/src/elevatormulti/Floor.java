package elevatormulti;

import java.util.ArrayList;

public class Floor {
	private boolean upbutton;
	private boolean downbutton;
	private int floornum;
	private double uptime;
	private double downtime;
	
	public Floor(int floornum) {
		this.floornum = floornum;
	}
	
	public boolean getUpStatus() {
		return this.upbutton;
	}
	
	public boolean getDownStatus() {
		return this.downbutton;
	}
	
	public double getUpTime() {
		return this.uptime;
	}
	
	public double getDownTime() {
		return this.downtime;
	}
	
	public int getFloorNum() {
		return this.floornum;
	}
	
	public void setUpStatus(boolean upbutton) {
		this.upbutton = upbutton;
	}
	
	public void setDownStatus(boolean downbutton) {
		this.downbutton = downbutton;
	}
	
	public void setUpTime(double uptime) {
		this.uptime = uptime;
	}
	
	public void setDownTime(double downtime) {
		this.downtime = downtime;
	}
}

class Floors {
	private ArrayList<Floor> floors = new ArrayList<Floor>();
	
	public boolean addFloor (int floornum) throws InvalidRequestException, SameRequestException {
		floors.add(new Floor(floornum));
		return true;
	}
	
	public Floor getFloor (int i) {
		return floors.get(i);
	}
}