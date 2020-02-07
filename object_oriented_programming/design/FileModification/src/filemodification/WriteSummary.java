package filemodification;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class WriteSummary {
	
	private String filename = "";
	
	public void setFileName(String filename) {
		this.filename = filename;
	}
	
	public synchronized String getFileName() {
		return this.filename;
	}
	
	public synchronized void writeSummary(int rename, int modify, int path, int size) {
		
		BufferedWriter bw = null;
		FileWriter fw = null;
		try {
			String content = "1. Renamed: " + rename + "\n2. Modified: " + modify + 
					"\n3. Path-changed: " + path + "\n4. Size-changed: " + size;
			
			fw = new FileWriter(getFileName());
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
