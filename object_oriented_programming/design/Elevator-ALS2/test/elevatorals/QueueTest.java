package elevatorals;

import static org.junit.Assert.*;

import org.junit.Test;

public class QueueTest {

	Queue queue = new Queue();
	boolean res;
	@Test
	public void testAddQueue() throws InvalidRequestException, SameRequestException {
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

	@Test
	public void testRemoveQueue() throws CannotRemoveException, InvalidRequestException, SameRequestException {
		res = queue.removeQueue(-1);
		assertFalse(res);
		res = queue.removeQueue(0);
		assertFalse(res);
		res = queue.removeQueue(1);
		assertFalse(res);
		queue.addQueue(new Request("FR,1,UP,0"));
		res = queue.removeQueue(0);
		assertTrue(res);
	}

}
