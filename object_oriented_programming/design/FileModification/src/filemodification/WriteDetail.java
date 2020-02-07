package filemodification;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class WriteDetail {
	private String filename = "";
	
	public void setFileName(String filename) {
		this.filename = filename;
	}
	
	public synchronized String getFileName() {
		return this.filename;
	}
	
	public synchronized void writeDetail(double bsize, double asize, String bname, String aname,
			String bpath, String apath, String bdate, String adate) {
		BufferedWriter bw = null;
		FileWriter fw = null;
		try {
			String content = "1. Size: \n- Before: " + bsize + "\n- After: " + asize + 
							 "\n2. Name: \n- Before: " + bname + "\n- After: " + aname + 
							 "\n3. Path: \n- Before: " + bpath + "\n- After: " + apath + 
							 "\n4. Date: \n- Before: " + bdate + "\n- After: " + adate;
			
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