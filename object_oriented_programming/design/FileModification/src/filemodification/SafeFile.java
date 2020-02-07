package filemodification;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class SafeFile {
	
	Conditions conditions = new Conditions();
	FileInfo fileinfo = new FileInfo();
	
	public synchronized void addFile(String filename) {
		
	}
	
	public synchronized void rename(String before, String after) throws IOException{
		File oldfile = new File(before);
		File newfile = new File(after);
		
		String oldPath = oldfile.getParent();
    	String fname = oldfile.getName();
    	
		File recovery = new File ("D:\\HW\\recover" + fname);
		
		Files.copy(oldfile.toPath(), recovery.toPath());
		
		if(oldfile.renameTo(newfile)) {
			conditions.setRenamed(true);
		}
		
		fileinfo.setNewFile(newfile.toString());
		
	}
	
	public synchronized void delete(String filename) throws IOException{
		File todelete = new File(filename);
		
		String oldPath = todelete.getAbsolutePath();
    	Path fname = Paths.get(oldPath);
    	
		File recovery = new File ("D:\\HW\\recover" + fname.getFileName());
		
		Files.copy(todelete.toPath(), recovery.toPath());
		
		if(todelete.delete())
	    {
			System.out.println("File deleted successfully");
	    }
	    else
	    {
	    	System.out.println("Failed to delete the file");
	    }
	}
	
	public synchronized void move(String from, String to) throws IOException{
		File original = new File(from);
		
		String oldPath = original.getAbsolutePath();
    	Path fname = Paths.get(oldPath);
    	
		File recovery = new File ("D:\\HW\\recover" + fname.getFileName());
		
		Files.copy(original.toPath(), recovery.toPath());
		
		original.renameTo(new File(to));
	}
	
	public synchronized void changeSize(String filename) {
		
	}
	
	public synchronized void changeTime(String filename) {
		
	}

}
