package filemodification;

import java.io.File;
import java.io.IOException;

public class WatchDirectory {
	
	static String condition[] = {"path-changed", "size-changed"};
    static String command[] = {"record-detail", "record-detail"};
    static String directory[] = {"D://portal.php", "D://HW//error.png"};
	
	public static void main(String[] args) {
		InputHandler inputhandler = new InputHandler();
        FileSearch filesearch = new FileSearch();
        FileInfo fileinfo = new FileInfo();
        WriteSummary writesum = new WriteSummary();
        WriteDetail writedetail = new WriteDetail();
        Conditions conditions = new Conditions();
        
        for(int i=0;i<inputhandler.getCommandNum();i++)
        {
        	fileinfo.setFile(directory[i]);
        	filesearch.setFileNameToSearch(fileinfo.getFileName());
            writedetail.setFileName(fileinfo.getDir() + "/records/detail.txt");
            writesum.setFileName(fileinfo.getDir() + "/records/summary.txt");
            
            try {
    			fileinfo.createFolders();
    		} catch (IOException e) {
    			e.printStackTrace();
    		}
            
            if(condition[i].toLowerCase().equals("renamed")) {
            	conditions.addRenamedNum();
            } else if(condition[i].toLowerCase().equals("modified")) {
            	conditions.addModifiedNum();
            } else if (condition[i].toLowerCase().equals("path-changed")) {
            	conditions.addPathChangedNum();
            } else if (condition[i].toLowerCase().equals("size-changed")) {
            	conditions.addSizeChangedNum();
            }
            
            if(command[i].toLowerCase().equals("record-summary")) {
            	writesum.writeSummary(conditions.getRenamedNum(), conditions.getModifiedNum(),
            			conditions.getPathChangedNum(), conditions.getSizeChangedNum());
            } else if(command[i].toLowerCase().equals("record-detail")) {
            	writedetail.writeDetail(fileinfo.getFileSize(), fileinfo.getNewFileSize(), 
            			fileinfo.getFileName(), fileinfo.getNewFileName(), 
            			fileinfo.getDir(), fileinfo.getNewDir(), fileinfo.getFileModifyDate(), 
            			fileinfo.getNewFileModifyDate());
            }
        }
    }
	
	/*ARCHIVED FUNCTIONS
            
     inputhandler.InputValidation();
     filesearch.searchDirectory(new File(fileinfo.getDir()), "error.png");
            
     if(filesearch.getResult()) {
        if(!filesearch.getcurrentDir().toString().equals(fileinfo.getFile().toString())) {
            conditions.setPathChanged(true);
     }
	 */

}
