package elevatorals;

import static org.junit.Assert.*;

import org.junit.Test;

public class ALSTest {

	@Test
	public void testALS() {
		Scheduler sched = new Scheduler();
		ALS als = new ALS(sched);
		assertNotNull(als);
	}

	@Test
	public void testPickUp() throws InvalidRequestException, SameRequestException, CannotRemoveException {
		boolean res;
		Scheduler sched = new Scheduler();
		ALS als = new ALS(sched);
		Queue queue = sched.getQueue();
		Elevator elev = sched.getElevator();
		
		res = queue.addQueue(new Request(1,Direction.UP,0));
		assertTrue(res);
		res = queue.addQueue(new Request(10,Direction.STILL,0));
		assertTrue(res);
		res = queue.addQueue(new Request(4,Direction.STILL,2));
		assertTrue(res);
		
		elev.moveUp();
		als.pickUp(queue, elev);
		elev.moveUp();
		als.pickUp(queue, elev);
		elev.moveUp();
		als.pickUp(queue, elev);
		elev.moveUp();
		als.pickUp(queue, elev);
		elev.moveUp();
		als.pickUp(queue, elev);
		elev.moveUp();
		als.pickUp(queue, elev);
		elev.moveUp();
		als.pickUp(queue, elev);
		elev.moveUp();
		als.pickUp(queue, elev);
		elev.moveUp();
		als.pickUp(queue, elev);
		elev.moveUp();
		als.pickUp(queue, elev);
		
		res = queue.addQueue(new Request(1,Direction.UP,0));
		assertTrue(res);
		res = queue.addQueue(new Request(4,Direction.STILL,1));
		assertTrue(res);
		res = queue.addQueue(new Request(4,Direction.UP,1));
		assertTrue(res);
		
		queue.removeQueue(0);
		elev.moveUp();
		als.pickUp(queue, elev);
		elev.moveUp();
		als.pickUp(queue, elev);
		elev.moveUp();
		als.pickUp(queue, elev);
		elev.moveUp();
		als.pickUp(queue, elev);
	}

	@Test
	public void testRunElevator() throws Exception {
		boolean res;
		Scheduler sched = new Scheduler();
		ALS als = new ALS(sched);
		Queue queue = sched.getQueue();
		
		queue.addQueue(new Request(1,Direction.UP,1));
		queue.addQueue(new Request(1,Direction.UP,0));
		queue.addQueue(new Request(4,Direction.STILL,1));
		
		als.runElevator();
		
		queue.removeQueue(0);
		queue.removeQueue(0);
		queue.removeQueue(0);
		
		res = queue.addQueue(new Request(1,Direction.UP,0));
		assertTrue(res);
		res = queue.addQueue(new Request(4,Direction.STILL,1));
		assertTrue(res);
		res = queue.addQueue(new Request(4,Direction.UP,1));
		assertTrue(res);
		
		als.runElevator();
		
		res = queue.addQueue(new Request(1,Direction.UP,0));
		assertTrue(res);
		res = queue.addQueue(new Request(10,Direction.STILL,0));
		assertTrue(res);
		res = queue.addQueue(new Request(4,Direction.STILL,2));
		assertTrue(res);
		res = queue.addQueue(new Request(4,Direction.DOWN,2));
		assertTrue(res);
		res = queue.addQueue(new Request(4,Direction.UP,3));
		assertTrue(res);
		
		als.runElevator();
	}

}
