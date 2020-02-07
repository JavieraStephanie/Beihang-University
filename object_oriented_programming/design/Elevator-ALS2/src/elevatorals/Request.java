package elevatorals;

import java.util.Scanner;

public class Request {
	
	private String type = "FR";
	private int req_floor;
	private double req_time;
	private Direction direction;
	
	public Request(String req) {
		/**
		 * @REQUIRES:None;
		 * @MODIFIES:this;
		 * @EFFECTS： (\result = \this) &&(\this.isEmpty());
		 */
		
		String temp[] = req.split(",");
		type = temp[0];
		
		if (type.equals("FR")) {
			this.req_floor = Integer.parseInt(temp[1]);
			
			if(temp[2].equals("UP"))
				this.direction = Direction.UP;
			else if (temp[2].equals("DOWN"))
				this.direction = Direction.DOWN;
			
			this.req_time = Long.parseLong(temp[3]);
		}
		else if (type.equals("ER")) {
			this.req_floor = Integer.parseInt(temp[1]);
			
			this.direction = Direction.STILL;
			
			this.req_time = Long.parseLong(temp[3]);
		}
	}
	
	public String getType() {
		return this.type;
	}
	
	public int getFloor() {
		return this.req_floor;
	}
	
	public double getTime() {
		return this.req_time;
	}
	
	public Direction getDir() {
		return this.direction;
	}
	
	public static void inputHandler(Queue queue, Scheduler sched) throws Exception {
		String input;
		Scanner scanner = new Scanner(System.in);
		
		while(scanner.hasNextLine()) {
			//Scan the input strings
			input = scanner.nextLine();

			//If the input string equals to "RUN" means that the input event is done
			if(input.equals("RUN")) {
				break;
			}
			
			try {
				//INPUT VALIDATION
				//Replace all occurrences of " " and "\t" to nothing
				input = input.replace(" ", "").replace("\t", "");
				char []val = input.toCharArray();
				int content = 0; //to check which content is being validated
				String req = ""; //string to parse
				
				for(int i = 0; i<val.length; i++) {
					if(val[i] == '(' && content == 0) {
						content++;
						req += val[i];
						continue;
					}
					else if((val[i] == 'F' || val[i] == 'E') && val[i+1] == 'R' && val[i+2] == ',' && content == 1) {
						content++;
						req += val[i];
						req += val[i+1];
						req += val[i+2];
						i+=2;
						continue;
					}
					else if(val[i] >= '0' && val[i] <= '9' && content == 2) {
						content++;
						req += val[i];
						req += val[i+1];
						if(val[i+2] == ',') {
							req += val[i+2];
							i+=2;
						}
						else 
							i++;
						continue;
					}
					else if((val[i] == 'U' && val[i+1] == 'P' && val[i+2] == ',') && content == 3) {
						content++;
						req += "UP,";
						i+=2;
						continue;
					}
					else if ((val[i] == 'D' && val[i+1] == 'O' && val[i+2] == 'W' && val[i+3] == 'N') && content == 3) {
						content++;
						req += "DOWN,";
						i+=4;
						continue;
					}
					else if (val[i] >= '0' && val[i] <= '9' && content == 3) {
						content++;
						req += "STILL,";
						while(val[i]!=')' && i<val.length) {
							req += val[i];
							i++;
						}
						req += ')';
					}
					else if (val[i] >= '0' && val[i] <= '9' && content == 4) {
						while(val[i]!=')' && i<val.length) {
							req += val[i];
							i++;
						}
						req += ')';
					}
					else
						throw new Exception ("Invalid input format!");
				}
				
				req = req.replace("(", "").replace(")", "");
				
				if (sched.addReq(new Request(req)) == false)
					throw new Exception ("Cannot add query!");
			}
			catch (Exception except) {
				System.out.print(except.getMessage());
			}
		}
		
		scanner.close();
	}
	
	public static void main(String[] args) throws Exception {
		Queue queue = new Queue();
		ALS als = new ALS();
		
		try {
			inputHandler(queue, als);
			als.runElevator();
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
		
		System.out.println("DONE");
	}

}
