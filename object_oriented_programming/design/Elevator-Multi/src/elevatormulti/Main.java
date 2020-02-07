package elevatormulti;

public class Main {
	public static void main(String[] args) throws Exception {
		Scheduler sched = new Scheduler();
		ALS als = new ALS(sched);
		InputHandler input = new InputHandler(sched, als);
				
		try {
			sched.initThings();
			input.input();
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
		
		System.out.println("DONE");
	}
}
