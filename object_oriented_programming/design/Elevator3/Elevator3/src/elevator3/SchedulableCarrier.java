package elevator3;

public interface SchedulableCarrier {
	void moveup(Integer dst);
	void movedown(Integer dst);
	Boolean turnon();
	Boolean turnoff();

}
