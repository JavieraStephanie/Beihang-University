package elevatormulti;

import java.util.ArrayList;

public class Floor {
	/*overview: The Floor class is just like any floor that could be found in everyday life. It's got up and down buttons
	 * and also a place to display it's ID (which floor is it). The floor will be initialized (created) on the system init,
	 * it will automatically create floors from 1 - max along with the buttons first set up to false (not turned on).
	 * When there's a new request, the request will first call the floor and set the button (up/down) of that floor to true,
	 * meaning that it's turned on. That button will then send a request to the scheduler telling it that there's a new request
	 * waiting to be processed.
	*/
	private boolean upbutton = false;
	private boolean downbutton = false;
	private int floornum;
	private double uptime;
	private double downtime;
	
	public Floor(int floornum) {
		/**
		 * @REQUIRES:floornum;
		 * @MODIFIES:this;
		 * @EFFECTS:
		 * (\result = \this) && (\this.isEmpty());
		 * (\this.floornum == floornum);
		 */
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
	
	public synchronized void setUpStatus(boolean upbutton, Scheduler sched) {
		/**
		 * @REQUIRES:upbutton, sched;
		 * @MODIFIES:this.upbutton;
		 * @EFFECTS:
		 * (\this.upbutton == true) ==> sched.addFloorReq(new FloorRequest(\this.floornum, \this.uptime, UP);
		 */
		this.upbutton = upbutton;
		if (this.upbutton == true) {
			try {
				if (sched.addFloorReq(new FloorRequest(this.floornum, this.uptime, Direction.UP)) == false)
					throw new Exception ("Cannot add query!");
			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
		}
	}
	
	public synchronized void setDownStatus(boolean downbutton, Scheduler sched) {
		/**
		 * @REQUIRES:downbutton, sched;
		 * @MODIFIES:this.downbutton;
		 * @EFFECTS:
		 * (\this.downbutton == true) ==> sched.addFloorReq(new FloorRequest(\this.floornum, \this.uptime, DOWN);
		 */
		this.downbutton = downbutton;
		if (this.downbutton == true) {
			try {
				if (sched.addFloorReq(new FloorRequest(this.floornum, this.downtime, Direction.DOWN)) == false)
					throw new Exception ("Cannot add query!");
			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
		}
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
		/**
		 * @REQUIRES: floornum;
		 * @MODIFIES: this.floors;
		 * @EFFECTS: 
		 * (\result==false)==>(\old(\this).floors.contains(floornum)==true)
		 * (\this.floors.size == \old(\this).floors.size+1) && (\this.floors.contains(floornum)==true)&&(\result==true);
		 */
		floors.add(new Floor(floornum));
		return true;
	}
	
	public Floor getFloor (int i) {
		return floors.get(i);
	}
}