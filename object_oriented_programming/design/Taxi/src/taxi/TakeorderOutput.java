package taxi;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.sql.Timestamp;

public class TakeorderOutput {	
	private String filename = "OrdersTaken.txt";
	
	public void setFileName(String filename) {
		this.filename = filename;
	}
	
	public synchronized String getFileName() {
		return this.filename;
	}
	
	public synchronized void writeDetail(int car, int posx, int posy, Timestamp time, Timestamp cararrive, int srcx, int srcy, int destx, int desty, Timestamp arrivetime) {
		BufferedWriter bw = null;
		FileWriter fw = null;
		try {
			String content = "Car no. " + car + ":\tCar Position:\t(" + posx + ", " + posy + ")\tTake Time:"
					+ time + "\tCar Arrive Time:\t" + cararrive + "\tPassenger Position:\t(" + srcx + ", " + srcy 
					+ ")\tDestination:\t(" + destx + ", " + desty + ")\tArrive Time:\t" + arrivetime;
			
			File file = new File(filename);
			
			if(!file.exists()) {
				file.createNewFile();
			}
			fw = new FileWriter(file.getAbsoluteFile(), true);
			bw = new BufferedWriter(fw);
			bw.write(content);
			
			System.out.println("Done");
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {

				if (bw != null)
					bw.close();

				if (fw != null)
					fw.close();

			} catch (IOException ex) {

				ex.printStackTrace();

			}
		}
	}
}