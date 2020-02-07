package elevatormulti;

import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class InputHandler implements Runnable{
	/*overview: InputHandler basically is just a class to handle inputs from user. It will validate the input
	 * and see if it matches the regular expression, if yes then it will parse that request into a request form,
	 * the FR request into FloorRequest, and the ER request into ElevatorRequest.
	*/
	private Thread inputThread;
	private Scheduler sched;
	private Floors floors;
	private Elevators elevs;
	private ALS als;
	private String input;
	private String inputs[];
	private Scanner scanner = new Scanner(System.in);
	private String regex1 = "\\(FR,\\S+,(UP|DOWN)\\)";
	private String regex2 = "\\(ER,#\\d,\\S+\\)";
	private Pattern p = Pattern.compile(regex1);
	private String temp[];
	
	public InputHandler(Scheduler sched, ALS als) {
		/**
		 * @REQUIRES:sched, als;
		 * @MODIFIES:this;
		 * @EFFECTS:
		 * (\result = \this) && (\this.isEmpty());
		 * (\this.sched == sched) && (\this.als == als);
		 * (\this.floors == \this.sched.getFloors());
		 * (\this.elevs == \this.sched.getElevators());
		 */
		this.sched = sched;
		this.als = als;
		this.floors = this.sched.getFloors();
		this.elevs = this.sched.getElevators();
	}
	
	public void input() throws Exception {
		/**
		 * @REQUIRES: System.in;
		 * @MODIFIES: input;
		 * @EFFECTS: 
		 * input == System.in ==> start();
		 */
		while(scanner.hasNextLine()) {
			this.input = scanner.nextLine();

			if(this.input.equals("END")) {
				break;
			}
			
			this.start();
		}
		
		scanner.close();
	}
	
	public void validateInput(double time) {	
		/**
		 * @REQUIRES: time (double);
		 * @MODIFIES: m, input;
		 * @EFFECTS:
		 * input.contains("(") == false && input.contains(")") == false;
		 * (m.matches(input) == false ==> exceptional_behavior(Exception("Invalid Format!")
		 * (m.matches(input) == true ==> input.contains(FR) == true ==> parseFloor(time);
		 * (m.matches(input) == true ==> input.contains(ER) == true ==> parseElevator(time);
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
		/**
		 * @REQUIRES: time (double);
		 * @MODIFIES: req_floor, req_time;
		 * @EFFECTS:
		 * req_floor == temp[1] && req_time == System.time;
		 * (\this.temp[2] == "UP") ==> \this.floors.floor(req_floor-1).upbutton == true && \this.floors.floor(req_floor-1).uptime = req_time;
		 * (\this.temp[2] == "DOWN") ==> \this.floors.floor(req_floor-1).downbutton == true && \this.floors.floor(req_floor-1).downtime = req_time;
		 */
		temp = input.split(",");
		int req_floor;
		//Direction direction;
		double req_time;
		
		try {
			req_floor = Integer.parseInt(temp[1]);
			req_time = time / 1000;
			
			if(temp[2].equals("UP")) {
				//direction = Direction.UP;
				if (!this.floors.getFloor(req_floor-1).getUpStatus()) {
					this.floors.getFloor(req_floor-1).setUpTime(req_time);
					this.floors.getFloor(req_floor-1).setUpStatus(true, this.sched);
				}
			}
			else {
				//direction = Direction.DOWN;
				if (!this.floors.getFloor(req_floor-1).getDownStatus()) {
					this.floors.getFloor(req_floor-1).setDownTime(req_time);
					this.floors.getFloor(req_floor-1).setDownStatus(true, this.sched);
				}
			}
			
			/*if (sched.addFloorReq(new FloorRequest(req_floor, req_time, direction)) == false)
				throw new Exception ("Cannot add query!");*/
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
	}
	
	public void parseElevator(double time) throws Exception {
		/**
		 * @REQUIRES: time (double);
		 * @MODIFIES: elevid, req_floor, req_time;
		 * @EFFECTS:
		 * elevid == temp[1] && req_floor == temp[2] && req_time == System.time;
		 * \this.elevs.elev(elevid-1).buttons.button(req_floor-1) == true;
		 */
		int req_floor;
		double req_time;
		int elevID;
		
		input = input.replace("#", "");
		temp = input.split(",");
		
		try {
			elevID = Integer.parseInt(temp[1]);
			req_floor = Integer.parseInt(temp[2]);
			req_time = time * 0.001;
			
			if (!this.elevs.getElevator(elevID-1).getElevButtons().getElevButton(req_floor-1).getButtonStat()) {
				this.elevs.getElevator(elevID-1).getElevButtons().getElevButton(req_floor-1).setButtonTime(req_time);
				this.elevs.getElevator(elevID-1).getElevButtons().getElevButton(req_floor-1).setButtonStat(true, this.elevs.getElevator(elevID-1));
			}
			/*if (sched.addElevReq(new ElevatorRequest(req_floor, req_time, elevID)) == false)
				throw new Exception ("Cannot add query!");*/
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
		inputThread = new Thread (this);
		inputThread.start();
	}
}
