package test;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.sql.Timestamp;

public class QueueOutput {	
	private String filename = "RequestDetail.txt";
	
	public void setFileName(String filename) {
		this.filename = filename;
	}
	
	public synchronized String getFileName() {
		return this.filename;
	}
	
	public synchronized void writeDetail(int i, Timestamp time, int srcx, int srcy, int destx, int desty) {
		BufferedWriter bw = null;
		FileWriter fw = null;
		try {
			String content = "Request" + i + ":\t" + "Time:\t" + time + "\tSource:\t(" + srcx + ", " + srcy + 
					")\tDestination:\t(" + destx + ", " + desty + ")\n";
			
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