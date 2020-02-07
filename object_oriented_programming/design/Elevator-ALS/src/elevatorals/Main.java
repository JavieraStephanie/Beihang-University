package elevatorals;

public class Main {
	public static void main(String[] args) throws Exception {
		Scheduler sched = new Scheduler();
		ALS als = new ALS(sched);
		InputHandler input = new InputHandler(sched);
		
		try {
			input.input();
			als.runElevator();
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
		
		System.out.println("DONE");
	}
}
