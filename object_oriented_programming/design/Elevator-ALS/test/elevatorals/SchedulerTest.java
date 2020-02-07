package elevatorals;

import static org.junit.Assert.*;

import org.junit.Test;

public class SchedulerTest {
	
	@Test
	public void testAddReq() throws InvalidRequestException, SameRequestException {
		Scheduler sched = new Scheduler();
		Queue queue = sched.getQueue();
		boolean res;
		
		res = queue.addQueue(new Request(1,Direction.UP,0));
		assertTrue(res);
		res = queue.addQueue(new Request(11,Direction.UP,0));
		assertFalse(res);
		res = queue.addQueue(new Request(1,Direction.DOWN,0));
		assertFalse(res);
		queue.addQueue(new Request(2,Direction.UP,0));
		res = queue.addQueue(new Request(2,Direction.UP,2));
		assertFalse(res);
	}
}