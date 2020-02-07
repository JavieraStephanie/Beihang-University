package elevatorals;

import static org.junit.Assert.*;

import org.junit.Test;

public class RequestTest {
	boolean res;
	@Test
	public void testRequest() {
		Request req = new Request("FR,1,UP,0");
		assertNotNull(req);
		req = new Request("ER,5,STILL,2");
		assertNotNull(req);
	}
}
