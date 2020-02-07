package elevatormulti;

class ElevatorSim implements Runnable {
	Scheduler sched = new Scheduler();
	ALS als = new ALS();
	InputHandler input = new InputHandler();
	
	@Override
	public void run() {
		try {
			input.input(sched, als);
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
	}
}

public class Main {
	public static void main(String[] args) throws Exception {
		Scheduler sched = new Scheduler();
		
		sched.initThings();
		
		System.out.println("DONE");
	}
}
