package elevatorals;

import static org.junit.Assert.*;

import org.junit.Test;

public class RequestTest {
	boolean res;
	@Test
	public void testRequest() {
		Request req = new Request(1,Direction.UP,0);
		assertNotNull(req);
		req = new Request(5,Direction.STILL,2);
		assertNotNull(req);
	}
}
