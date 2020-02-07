package elevatormulti;

import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class InputHandler {
	
	public void input(Scheduler sched, ALS als) throws Exception {
		String input;
		String inputs[];
		Scanner scanner = new Scanner(System.in);
		
		while(scanner.hasNextLine()) {
			input = scanner.nextLine();
			double time = System.currentTimeMillis();

			if(input.equals("END")) {
				break;
			}
			
			try {
				input = input.replace(" ", "").replace("\t", "");
				
				if (input.indexOf(";") != -1) {
					inputs = input.split(";");
					
					for (int i = 0; i < inputs.length; i++) {
						validateInput(inputs[i], sched, time);
						als.runSystem(sched);
					}
					continue;
				}
				
				validateInput(input, sched, time);
				als.runSystem(sched);
			}
			catch (Exception except) {
				System.out.print(except.getMessage());
			}
		}
		
		scanner.close();
	}
	
	public void validateInput(String input, Scheduler sched, double time) {
		String regex1 = "\\(FR,\\S+,(UP|DOWN)\\)";
		String regex2 = "\\(ER,#\\d,\\S+\\)";
		Pattern p = Pattern.compile(regex1);
		
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
				parseFloor(input, sched, time);
			}
			else if (input.indexOf("ER") != -1) {
				parseElevator(input, sched, time);
			}
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
	}
	
	public void parseFloor(String req, Scheduler sched, double time) throws Exception {
		String temp[] = req.split(",");
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
	
	public void parseElevator(String req, Scheduler sched, double time) throws Exception {
		String temp[];
		int req_floor;
		double req_time;
		int elevID;
		
		req = req.replace("#", "");
		temp = req.split(",");
		
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
}
