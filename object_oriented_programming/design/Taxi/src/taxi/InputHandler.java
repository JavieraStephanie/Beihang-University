package taxi;

import java.sql.Timestamp;
import java.util.Date;
import java.util.Scanner;

public class InputHandler {
	Scanner scanner = new Scanner(System.in);
    
    String input;
    String prefix = "CR, ";
    int[] sourcesi = new int[1000];
    int[] sourcesj = new int[1000];
    int[] destinationsi = new int[1000];
    int[] destinationsj = new int[1000];
    Timestamp[] time = new Timestamp[1000];
    long currenttime;

	public void InputValidation(int i) {
		
		System.out.print("Please enter your request(s): ");
    	
    	input = scanner.nextLine();
    	Date date = new Date();
    	currenttime = date.getTime();
    	time[i]= new Timestamp(currenttime);
    		
        if(input.startsWith(prefix)) {
        	input = input.substring(prefix.length());
        		
        	String coordinates[] = input.split(", ");
        		
        	sourcesi[i]=Character.getNumericValue(coordinates[0].charAt(1));
        	sourcesj[i]=Character.getNumericValue(coordinates[1].charAt(0));
        	destinationsi[i]=Character.getNumericValue(coordinates[2].charAt(1));
        	destinationsj[i]=Character.getNumericValue(coordinates[3].charAt(0));
        }

        //scanner.close();
    }
	
	public int[] getSourcei() {
		return this.sourcesi;
	}
	public int[] getSourcej() {
		return this.sourcesj;
	}
	public int[] getDestinationi() {
		return this.destinationsi;
	}
	public int[] getDestinationj() {
		return this.destinationsj;
	}
	public Timestamp[] getTime() {
		return this.time;
	}
}