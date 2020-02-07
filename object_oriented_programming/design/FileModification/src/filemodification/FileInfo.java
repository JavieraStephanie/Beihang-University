package filemodification;

import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;

public class FileInfo {
	
	private String fextension;
	private String dir;
	private String fname;
	private double fsize;
	private String fdate;
	private String newdir;
	private String newfname;
	private double newfsize;
	private String newfdate;
	private File newfile;
	private File file;
	SimpleDateFormat sdf = new SimpleDateFormat("MM/dd/yyy HH:mm:ss");
	
	public synchronized void setFile(String pathName) {
		this.file = new File (pathName);
		setDir();
		setFileName();
		setFileExtension();
		setFileSize();
		setFileModifyDate();
	}
	
	public synchronized File getFile() {
		return this.file;
	}
	
	public synchronized void setDir() {
		this.dir = getFile().getParent();
	}
	
	public synchronized String getDir() {
		return this.dir;
	}
	
	public synchronized void setFileName() {
		this.fname = getFile().getName();
	}
	
	public synchronized String getFileName() {
		return this.fname;
	}
	
	public synchronized void setFileExtension() {
		this.fextension = getExtension(getFileName());
	}
	
	public synchronized String getFileExtension() {
		return this.fextension;
	}
	
	public synchronized void setFileSize() {
		this.fsize = getFile().length();
	}
	
	public synchronized double getFileSize() {
		return this.fsize;
	}
	
	public synchronized void setFileModifyDate() {
		this.fdate = sdf.format(getFile().lastModified());
	}

	public synchronized String getFileModifyDate() {
		return this.fdate;
	}
	
	public synchronized void setNewFile(String pathName) {
		this.newfile = new File (pathName);
		setDir();
		setFileName();
		setFileExtension();
		setFileSize();
		setFileModifyDate();
	}
	
	public synchronized File getNewFile() {
		return this.newfile;
	}
	
	
	public synchronized void setNewDir() {
		this.newdir = getNewFile().getParent();
	}
	
	public synchronized String getNewDir() {
		return this.newdir;
	}
	
	public synchronized void setNewFileName() {
		this.newfname = getNewFile().getName();
	}
	
	public synchronized String getNewFileName() {
		return this.newfname;
	}
	
	public synchronized void setNewFileSize() {
		this.newfsize = getNewFile().length();
	}
	
	public synchronized double getNewFileSize() {
		return this.newfsize;
	}
	
	public synchronized void setNewFileModifyDate() {
		this.newfdate = sdf.format(getNewFile().lastModified());
	}

	public synchronized String getNewFileModifyDate() {
		return this.newfdate;
	}
	
	public synchronized void createFolders() throws IOException
	{
		File recordsdir = new File(getDir() + "\\records");
        File recoverdir = new File(getDir() + "\\recover");
        if (!recordsdir.exists()) {
        	if(recordsdir.mkdirs()) {
        		System.out.println("Records directory is created");
        		
        		File summaryfile = new File(getDir() + "\\records\\summary.txt");
        		File detailfile = new File(getDir() + "\\records\\detail.txt");
        		
        		summaryfile.createNewFile();
        		detailfile.createNewFile();
        		
        	} else {
        		System.out.println("Failed to create directory!");
        	}
        }
        
        if (!recoverdir.exists()) {
        	if(recoverdir.mkdir()) {
        		System.out.println("Recover directory is created");
        	} else {
        		System.out.println("Failed to create directory!");
        	}
        }
	}
	
	private synchronized String getExtension(String filename)
	{
		String fileExtension = "";
		
		if(filename.contains(".") && filename.lastIndexOf(".")!=0)
		{
			fileExtension = filename.substring(filename.lastIndexOf(".")+1);
		}
		return fileExtension;
	}
	

}
