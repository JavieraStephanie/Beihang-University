package elevator3;

import java.sql.Time;

public class Elevator implements SchedulableCarrier {
	private ElevatorStatus status;
	private Integer currentfloor;
	private Time sys_time;
	private Direction dir;
	@Override
	public void moveup(Integer dst) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void movedown(Integer dst) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public Boolean turnon() {
		// TODO Auto-generated method stub
		return null;
	}
	@Override
	public Boolean turnoff() {
		// TODO Auto-generated method stub
		return null;
	}
	
	public String toString() {
		return null;
		
	}

}
