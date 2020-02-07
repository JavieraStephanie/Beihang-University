package elevatormulti;

import java.io.BufferedWriter;
import java.io.FileWriter;

public class OutputHandler {
	/*overview: OutputHandler is a class that manages all things related to printing out the output result to a file.
	 * When a request is done being processed, the system will call the OutputHandler to print the result, this class
	 * will print out the result to a file called result.txt located in the root folder.
	*/
	private String filename = "./result.txt";
	private BufferedWriter bw = null;
	private FileWriter fw = null;
	
	public String getFileName() {
		return this.filename;
	}
	
	public void writeFloor(int target, String dir, double time, int elevid, int floor, String elevdir, int point) {
		/**
		 * @REQUIRES: this.filename != NULL;
		 * @MODIFIES: this.filename;
		 * @EFFECTS: \this.filename.contains(content);
		 */
		try {
			String content = "[FR, " + target + ", " + dir + ", " + time + "] / (#" + 
					elevid + ", " + floor + ", " + elevdir + ", " + point + ", " + (System.currentTimeMillis()/1000) + ")";
			
			fw = new FileWriter(getFileName(), true);
			bw = new BufferedWriter(fw);
			bw.write(content);
			bw.newLine();
			
		} catch (Exception except) {
			System.out.print(except.getMessage());
		} finally {
			try {

				if (bw != null)
					bw.close();

			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
		}
	}
	
	public void writeElev(int target, double time, int elevid, int floor, String elevdir, int point) {
		/**
		 * @REQUIRES: this.filename != NULL;
		 * @MODIFIES: this.filename;
		 * @EFFECTS: \this.filename.contains(content);
		 */
		try {
			String content = "[ER, " + target + ", " + time + "] / (#" + 
					elevid + ", " + floor + ", " + elevdir + ", " + point + ", " + (System.currentTimeMillis()/1000) + ")";
			
			fw = new FileWriter(getFileName(), true);
			bw = new BufferedWriter(fw);
			bw.write(content);
			bw.newLine();
			
		} catch (Exception except) {
			System.out.print(except.getMessage());
		} finally {
			try {

				if (bw != null)
					bw.close();

			} catch (Exception except) {
				System.out.print(except.getMessage());
			}
		}
	}
}
