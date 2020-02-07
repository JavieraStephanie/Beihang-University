package elevatormulti;

import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class InputHandler implements Runnable{
	private Thread inputThread;
	private Scheduler sched;
	private ALS als;
	private String input;
	private String inputs[];
	private Scanner scanner = new Scanner(System.in);
	private String regex1 = "\\(FR,\\S+,(UP|DOWN)\\)";
	private String regex2 = "\\(ER,#\\d,\\S+\\)";
	private Pattern p = Pattern.compile(regex1);
	private String temp[];
	
	public InputHandler(Scheduler sched, ALS als) {
		this.sched = sched;
		this.als = als;
	}
	
	public void input() throws Exception {
		System.out.println("HERE");
		while(scanner.hasNextLine()) {
			this.input = scanner.nextLine();

			if(this.input.equals("END")) {
				break;
			}
			System.out.println("HERE");
			this.start();
		}
		
		scanner.close();
	}
	
	public void validateInput(double time) {		
		try {
			if (input.indexOf("FR") != -1) {
				p = Pattern.compile(regex1);
			}
			else if (input.indexOf("ER") != -1) {
				p = Pattern.compile(regex2);
			}
			
			Matcher m = p.matcher(input);
			
			if(m.matches() == false)
				throw new Exception ("Invalid Format!");
			
			input = input.replace("(", "").replace(")", "");
			
			if (input.indexOf("FR") != -1) {
				parseFloor(time);
			}
			else if (input.indexOf("ER") != -1) {
				parseElevator(time);
			}
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
	}
	
	public void parseFloor(double time) throws Exception {
		temp = input.split(",");
		int req_floor;
		Direction direction;
		double req_time;
		
		try {
			req_floor = Integer.parseInt(temp[1]);
			
			if(temp[2].equals("UP"))
				direction = Direction.UP;
			else
				direction = Direction.DOWN;
				
			req_time = time * 0.001;
			
			if (sched.addFloorReq(new FloorRequest(req_floor, req_time, direction)) == false)
				throw new Exception ("Cannot add query!");
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
	}
	
	public void parseElevator(double time) throws Exception {
		int req_floor;
		double req_time;
		int elevID;
		
		input = input.replace("#", "");
		temp = input.split(",");
		
		try {
			elevID = Integer.parseInt(temp[1]);
			req_floor = Integer.parseInt(temp[2]);
			req_time = time * 0.001;
			
			if (sched.addElevReq(new ElevatorRequest(req_floor, req_time, elevID)) == false)
				throw new Exception ("Cannot add query!");
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		double time = System.currentTimeMillis();
		
		try {
			input = input.replace(" ", "").replace("\t", "");
			
			if (input.indexOf(";") != -1) {
				inputs = input.split(";");
				
				for (int i = 0; i < inputs.length; i++) {
					validateInput(time);
					als.start();
				}
			}
			
			else {
				validateInput(time);
				als.start();
			}
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
	}
	
	public void start() {
		/*if (inputThread == null) {
			inputThread = new Thread (this);
			inputThread.start();
		}*/
		inputThread = new Thread (this);
		inputThread.start();
	}
}
