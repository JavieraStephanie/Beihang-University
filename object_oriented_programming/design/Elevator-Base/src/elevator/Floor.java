package elevator;

public class Floor {
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
