package elevatorals;

public class Floor {
	/*@Overview: Each Floor has its floor number and up-down buttons. When a new FR request comes,
	 * the up/down buttons will be turned on according to that request.
	 */
	
	private boolean up = false;
	private boolean down = false;
	private int floornum = 1;

	public boolean getUpStatus() {
		return this.up;
	}
	
	public boolean getDownStatus() {
		return this.down;
	}
	
	public int getFloorNum() {
		return this.floornum;
	}
	
	public void setUpStatus(boolean up) {
		this.up = up;
	}
	
	public void setDownStatus(boolean down) {
		this.down = down;
	}
	
	public void setFloorNum(int floornum) {
		this.floornum = floornum;
	}
}
