package elevatormulti;

import java.io.BufferedWriter;
import java.io.FileWriter;

public class OutputHandler {
	private String filename = "./result.txt";
	private BufferedWriter bw = null;
	private FileWriter fw = null;
	
	public String getFileName() {
		return this.filename;
	}
	
	public void writeFloor(int target, String dir, double time, int elevid, int floor, String elevdir, int point, double elevtime) {
		try {
			String content = "[FR, " + target + ", " + dir + ", " + time + "] / (#" + 
					elevid + ", " + floor + ", " + elevdir + ", " + point + ", " + elevtime + ")";
			
			fw = new FileWriter(getFileName(), true);
			bw = new BufferedWriter(fw);
			bw.write(content);
			bw.newLine();
			
			System.out.println("Done");
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
	
	public void writeElev(int target, double time, int elevid, int floor, String elevdir, int point, double elevtime) {
		try {
			String content = "[ER, " + target + "," + time + "] / (#" + 
					elevid + ", " + floor + ", " + elevdir + ", " + point + ", " + elevtime + ")";
			
			fw = new FileWriter(getFileName(), true);
			bw = new BufferedWriter(fw);
			bw.write(content);
			bw.newLine();
						
			System.out.println("Done");
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
