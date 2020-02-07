package taxi;

import java.awt.Point;
import java.io.BufferedWriter;
import java.io.FileWriter;

public class OutputHandler {
	private String filename = "./RequestDetail.txt";
	private String filename2 = "./WaitingList.txt";
	private String filename3 = "./OrdersTaken.txt";
	private BufferedWriter bw = null;
	private FileWriter fw = null;
	
	public String getFileName() {
		return this.filename;
	}
	
	public String getFileName2() {
		return this.filename2;
	}
	
	public String getFileName3() {
		return this.filename3;
	}
	
	public synchronized void writeRequest(double time, Point src, Point dest) {
		/**
		 * @REQUIRES: this.filename != NULL;
		 * @MODIFIES: this.filename;
		 * @EFFECTS: \this.filename.contains(content);
		 */
		
		try {
			String content = "Time:\t" + time + "\tSource:\t(" + src.x + ", " + src.y + 
					")\tDestination:\t(" + dest.x + ", " + dest.y + ")\n";
			
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
	
	public synchronized void writeList(int carnum, Point pos, int status, int review) {
		/**
		 * @REQUIRES: this.filename2 != NULL;
		 * @MODIFIES: this.filename2;
		 * @EFFECTS: \this.filename2.contains(content);
		 */
		
		try {
			String content = "Car no. " + carnum + ":\tPosition:\t(" + pos.x + ", " + pos.y + ")\tStatus:"
					+ status + "Review:\t" + review;
			
			fw = new FileWriter(getFileName2(), true);
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
	
	public synchronized void writeTaken(int carnum, Point pos, double takeorder, double cararrive, Point src, Point dest, double arrivetime) {
		/**
		 * @REQUIRES: this.filename3 != NULL;
		 * @MODIFIES: this.filename3;
		 * @EFFECTS: \this.filename3.contains(content);
		 */
		
		try {
			String content = "Car no. " + carnum + ":\tCar Position:\t(" + pos.x + ", " + pos.y + ")\tTake Time:"
					+ takeorder + "\tCar Arrive Time:\t" + cararrive + "\tPassenger Position:\t(" + src.x + ", " + src.y 
					+ ")\tDestination:\t(" + dest.x + ", " + dest.y + ")\tArrive Time:\t" + arrivetime;
			
			fw = new FileWriter(getFileName2(), true);
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
