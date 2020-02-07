package elevatorals;

import static org.junit.Assert.*;

import org.junit.Test;

public class InputHandlerTest {

	@Test
	public void testInputHandler() {
		Scheduler sched = new Scheduler();
		InputHandler input = new InputHandler(sched);
		assertNotNull(input);
	}

	@Test
	public void testValidateInput() {
		Scheduler sched = new Scheduler();
		InputHandler input = new InputHandler(sched);
		input.validateInput("(FR,1,Direction.UP,0)");
		input.validateInput("(FR,,3,Direction.DOWN,2)");
		input.validateInput("(FR,,3,Direction.DOWN,200000000)");
		input.validateInput("(FR,1,Direction.UP,0000000)");
		input.validateInput("(FR,1,Direction.UP,000002)");
		input.validateInput("(FR,1,Direction.UP,000002,,,");
		input.validateInput("(ER,1,0)");
		input.validateInput("ER,1,0,,,)");
		input.validateInput("(ER,1,,0)");
		input.validateInput("(ER,100,0)");
		input.validateInput("(ER,,.10,0)");
		input.validateInput("(ER,1,111110)");
		input.validateInput("(ER,1,,112340");
	}

	@Test
	public void testParseFloor() throws Exception {
		Scheduler sched = new Scheduler();
		InputHandler input = new InputHandler(sched);
		input.parseFloor("FR,1,Direction.UP,0");
		input.parseFloor("FR,,3,Direction.DOWN,2");
		input.parseFloor("FR,,3,Direction.DOWN,200000000");
		input.parseFloor("FR,1,Direction.UP,0000000");
		input.parseFloor("FR,1,Direction.UP,000002");
		input.parseFloor("FR,1,Direction.UP,000002,,,");
	}

	@Test
	public void testParseElevator() throws Exception {
		Scheduler sched = new Scheduler();
		InputHandler input = new InputHandler(sched);
		input.parseFloor("ER,1,0");
		input.parseFloor("ER,1,0,,,");
		input.parseFloor("ER,1,,0");
		input.parseFloor("ER,100,0");
		input.parseFloor("ER,,.10,0");
		input.parseFloor("ER,1,111110");
		input.parseFloor("ER,1,,112340");
	}

}
