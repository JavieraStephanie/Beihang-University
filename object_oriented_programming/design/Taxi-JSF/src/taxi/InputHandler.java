package taxi;

import java.awt.Point;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class InputHandler implements Runnable{
	private Thread inputThread;
	private Dispatcher disp;
	private String input;
	private Scanner scanner = new Scanner(System.in);
	private String regex = "\\[CR,\\(\\d,\\d\\),\\(\\d,\\d\\)\\]";
	private Pattern p;
	private String temp[];
	
	public InputHandler(Dispatcher disp) {
		this.disp = disp;
	}
	
	public void input() throws Exception {
		/**
		 * @REQUIRES: None;
		 * @MODIFIES: input;
		 * @EFFECTS: input == System.in;
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
		 * input.contains("(") == false && input.contains(")") == false && input.contains("[") == false && input.contains("]") == false;
		 * (m.matches(input) == false ==> exceptional_behavior(Exception("Invalid Format!")
		 */
		
		try {
			p = Pattern.compile(regex);
			
			Matcher m = p.matcher(input);
			
			if(m.matches() == false)
				throw new Exception ("Invalid Format!");
			
			input = input.replace("(", "").replace(")", "");
			input = input.replace("[", "").replace("]", "");
			
			parseInput(time);
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
	}
	
	public void parseInput(double time) throws Exception {
		/**
		 * @REQUIRES: time (double);
		 * @MODIFIES: src, dst;
		 * @EFFECTS:
		 * src.x == temp[1] && src.y == temp[2] && dst.x == temp[3] && dst.y == temp[4];
		 * (\old(\this.disp).addReq(src, dst, req_time) == false)==>exceptional_behavior(Exception("Cannot add query!"))
		 */
		
		temp = input.split(",");
		Point src = new Point (0,0);
		Point dst = new Point (0,0);
		double req_time;
		
		try {
			src.x = Integer.parseInt(temp[1]);
			src.y = Integer.parseInt(temp[2]);
			dst.x = Integer.parseInt(temp[3]);
			dst.y = Integer.parseInt(temp[4]);
			
			req_time = time / 1000;
			
			if (disp.addReq(new Request(src, dst, req_time)) == false)
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
			
			validateInput(time);
			disp.start();
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
