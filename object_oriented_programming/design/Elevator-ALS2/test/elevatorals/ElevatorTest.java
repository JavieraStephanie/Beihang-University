package elevatorals;

import static org.junit.Assert.*;

import org.junit.Test;

public class ElevatorTest {

	Elevator elev = new Elevator();
	boolean res;

	@Test
	public void testMoveUp() {	//Move up 10 times	
		res = elev.moveUp();
		assertTrue(res);
		res = elev.moveUp();
		assertTrue(res);
		res = elev.moveUp();
		assertTrue(res);
		res = elev.moveUp();
		assertTrue(res);
		res = elev.moveUp();
		assertTrue(res);
		res = elev.moveUp();
		assertTrue(res);
		res = elev.moveUp();
		assertTrue(res);
		res = elev.moveUp();
		assertTrue(res);
		res = elev.moveUp();
		assertTrue(res);
		res = elev.moveUp(); //Above 10th floor
		assertFalse(res);
	}

	@Test
	public void testMoveDown() {	//Move down 10 times
		res = elev.moveDown(); // Below 1st floor
		assertFalse(res);
		testMoveUp();
		res = elev.moveDown();
		assertTrue(res);
		res = elev.moveDown();
		assertTrue(res);
		res = elev.moveDown();
		assertTrue(res);
		res = elev.moveDown();
		assertTrue(res);
		res = elev.moveDown();
		assertTrue(res);
		res = elev.moveDown();
		assertTrue(res);
		res = elev.moveDown();
		assertTrue(res);
		res = elev.moveDown();
		assertTrue(res);
		res = elev.moveDown();
		assertTrue(res);
		res = elev.moveDown(); //Below 1st floor
		assertFalse(res);
	}

	@Test
	public void testDoorMove() {
		res = elev.doorMove();
		assertTrue(res);
		assertEquals(elev.getDir(), "STILL");
	}

}
