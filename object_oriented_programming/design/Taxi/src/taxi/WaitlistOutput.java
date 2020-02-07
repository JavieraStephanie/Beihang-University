package taxi;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class WaitlistOutput {	
	private String filename = "WaitingList.txt";
	
	public void setFileName(String filename) {
		this.filename = filename;
	}
	
	public synchronized String getFileName() {
		return this.filename;
	}
	
	public synchronized void writeDetail(int car, int posx, int posy, int status, String xinyong) {
		BufferedWriter bw = null;
		FileWriter fw = null;
		try {
			String content = "Car no. " + car + ":\tPosition:\t(" + posx + ", " + posy + ")\tStatus:"
					+ status + "XinYong:\t" + xinyong;
			
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
