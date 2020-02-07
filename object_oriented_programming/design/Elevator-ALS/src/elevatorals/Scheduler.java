package elevatorals;

public class Scheduler {
	private Floor floor = new Floor();
	private Elevator elevator = new Elevator();
	private Queue queue = new Queue();
	private boolean isPickUp = false;
	
	public boolean addReq(Request req) throws InvalidRequestException, SameRequestException {
		/**
		 * @REQUIRES: req (Request);
		 * @MODIFIES: this.queue;
		 * @EFFECTS: queue.addQueue(req);
		 */
		return queue.addQueue(req);
	}
	
	public Floor getFloor() {
		return this.floor;
	}
	
	public Elevator getElevator() {
		return this.elevator;
	}
	
	public Queue getQueue() {
		return this.queue;
	}
	
	public void setPickUp(boolean isPickUp) {
		this.isPickUp = isPickUp;
	}
	
	public boolean getPickUp() {
		return this.isPickUp;
	}
}