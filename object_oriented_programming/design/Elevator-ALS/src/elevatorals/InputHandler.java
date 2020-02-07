package elevatorals;

import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class InputHandler {
	private Scheduler sched;
	private Scanner scanner = new Scanner(System.in);
	private String regex1 = "\\(FR,\\S+,(UP|DOWN),\\S+\\)";
	private String regex2 = "\\(ER,\\S+,\\S+\\)";
	private Pattern p = Pattern.compile(regex1);
	private String temp[];
	
	public InputHandler(Scheduler sched) {
		this.sched = sched;
	}
	
	public void input() throws Exception {
		/**
		 * @REQUIRES: System.in;
		 * @MODIFIES: input;
		 * @EFFECTS: 
		 * input == System.in;
		 * input.contains(" ") == false && input.contains("\t") == false;
		 */
		String input;
		
		while(scanner.hasNextLine()) {
			input = scanner.nextLine();

			if(input.equals("RUN")) {
				break;
			}
			
			try {
				input = input.replace(" ", "").replace("\t", "");
				
				validateInput(input);
			}
			catch (Exception except) {
				System.out.print(except.getMessage());
			}
		}
		
		scanner.close();
	}
	
	public void validateInput(String input) {
		/**
		 * @REQUIRES: input (String);
		 * @MODIFIES: m, input;
		 * @EFFECTS:
		 * input.contains("(") == false && input.contains(")") == false;
		 * (m.matches(input) == false ==> exceptional_behavior(Exception("Invalid Format!")
		 * (m.matches(input) == true ==> input.contains(FR) == true ==> parseFloor(input);
		 * (m.matches(input) == true ==> input.contains(ER) == true ==> parseElevator(input);
		 */
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
				parseFloor(input);
			}
			else if (input.indexOf("ER") != -1) {
				parseElevator(input);
			}
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
	}
	
	public void parseFloor(String input) throws Exception {
		/**
		 * @REQUIRES: input (String);
		 * @MODIFIES: req_floor, direction, req_time;
		 * @EFFECTS:
		 * req_floor == temp[1] && direction == temp[2] && req_time == temp[3];
		 * (\old(\this.sched).addReq(req_floor, direction, req_time) == false)==>exceptional_behavior(Exception("Cannot add query!"))
		 */
		
		temp = input.split(",");
		int req_floor;
		Direction direction = Direction.UP;
		double req_time;
		
		try {
			req_floor = Integer.parseInt(temp[1]);
			req_time = Integer.parseInt(temp[3]);
			if(temp[2].equals("UP"))
				direction = Direction.UP;
			else if (temp[2].equals("DOWN"))
				direction = Direction.DOWN;
			
			if (sched.addReq(new Request(req_floor, direction, req_time)) == false)
				throw new Exception ("Cannot add query!");
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
	}
	
	public void parseElevator(String input) throws Exception {
		/**
		 * @REQUIRES: input (String);
		 * @MODIFIES: req_floor, req_time;
		 * @EFFECTS:
		 * req_floor == temp[1] && req_time == temp[3];
		 * (\old(\this.sched).addReq(req_floor, direction, req_time) == false)==>exceptional_behavior(Exception("Cannot add query!"))
		 */
		
		int req_floor;
		double req_time;
		Direction direction = Direction.STILL;
		
		input = input.replace("#", "");
		temp = input.split(",");
		
		try {
			req_floor = Integer.parseInt(temp[1]);
			req_time = Integer.parseInt(temp[2]);
			
			if (sched.addReq(new Request(req_floor, direction, req_time)) == false)
				throw new Exception ("Cannot add query!");
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
	}
}
