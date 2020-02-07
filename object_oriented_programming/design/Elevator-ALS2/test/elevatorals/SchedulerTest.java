package elevatorals;

import static org.junit.Assert.*;

import org.junit.Test;

public class SchedulerTest {

	Queue queue = new Queue();
	boolean res;
	@Test
	public void testAddReq() throws InvalidRequestException, SameRequestException {
		res = queue.addQueue(new Request("FR,1,UP,0"));
		assertTrue(res);
		res = queue.addQueue(new Request("FR,11,UP,0"));
		assertFalse(res);
		res = queue.addQueue(new Request("FR,1,DOWN,0"));
		assertFalse(res);
		queue.addQueue(new Request("FR,2,UP,0"));
		res = queue.addQueue(new Request("FR,2,UP,2"));
		assertFalse(res);
	}
}

class ALSTest {
	Scheduler sched = new Scheduler();
	Queue queue = new Queue();
	Elevator elevator;
	Floor floor;
	
	@Test
	public void testRemoveUnused() throws InvalidRequestException, SameRequestException {
		
	}
	
	@Test
	public void testPickUp() throws InvalidRequestException, SameRequestException {
	}
	
	@Test
	public void testRunElevator() throws InvalidRequestException, SameRequestException {
		queue.addQueue(new Request("FR,1,UP,0"));
		queue.addQueue(new Request("ER,10,STILL,0"));
		queue.addQueue(new Request("ER,4,STILL,2"));
		queue.addQueue(new Request("FR,4,DOWN,2"));
		queue.addQueue(new Request("FR,4,UP,3"));
	}
}