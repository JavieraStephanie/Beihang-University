package elevatorals;

import static org.junit.Assert.*;

import org.junit.Test;

public class QueueTest {

	Queue queue = new Queue();
	boolean res;
	@Test
	public void testAddQueue() throws InvalidRequestException, SameRequestException {
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

	@Test
	public void testRemoveQueue() throws CannotRemoveException, InvalidRequestException, SameRequestException {
		res = queue.removeQueue(-1);
		assertFalse(res);
		res = queue.removeQueue(0);
		assertFalse(res);
		res = queue.removeQueue(1);
		assertFalse(res);
		queue.addQueue(new Request(1,Direction.UP,0));
		res = queue.removeQueue(0);
		assertTrue(res);
	}

}
