package filemodification;

import java.util.Scanner;
import java.util.regex.MatchResult;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class InputHandler {
	Scanner scanner = new Scanner(System.in);
    
    String input;
    String longin [] = {};
    int commandnum = 2;
    int i=0;
    
    public synchronized int getCommandNum() {
    	return this.commandnum;
    }

	public void InputValidation() {
		        
        System.out.print("How many commands do you want to input?");
        
        commandnum = scanner.nextInt();
        
        System.out.print("Please enter your command(s): ");
        
        /*for (i=0;i<commandnum;i++)
        {
        	input = scanner.nextLine();
        	String tempin[] = input.split(" ");
        	directories[i] = tempin[1];
        	
        	System.out.println(directories[i]);
        }*/
        while(i<commandnum) {
        	input = scanner.nextLine();
        	String [] tempin = input.split(" ");
        }

       
        
        scanner.close();
    }

}
