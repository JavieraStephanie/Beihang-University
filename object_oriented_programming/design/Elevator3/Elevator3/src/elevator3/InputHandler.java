package elevator3;

import java.util.Scanner;

public class InputHandler {
	private String regex;
	
	public Boolean validate (String str) {
		/*Scanner scanner = new Scanner(System.in);
		regex = scanner.nextLine();
		parse(regex);*/
		try {
			if (str.equalsIgnoreCase("FR, 1, UP")) {
				parse(str);
			}
			return true;
		} catch(Exception e) {
			return false;
		}
	}
	
	public Boolean parse (String str) {
		String [] arrOfStr = str.split(",");
		return null;
		
	}
	
	public Integer scan (Scanner scanner) {
		return null;
		
	}
	
	public Request retrieve () {
		return null;
		
	}

}
