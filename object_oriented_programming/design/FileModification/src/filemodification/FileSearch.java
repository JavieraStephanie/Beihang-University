package filemodification;

import java.io.File;

public class FileSearch{
	
	private String fileName = "";
	private String currentDir = "";
	private boolean result = false;
	private boolean moved = false;
	
	public synchronized String getFileNameToSearch() {
		return this.fileName;
	}
	
	public synchronized void setFileNameToSearch(String fileName) {
		this.fileName = fileName;
	}
	
	public synchronized void setcurrentDir(String currentDir) {
		this.currentDir = currentDir;
	}
	
	public synchronized String getcurrentDir() {
		return this.currentDir;
	}
	
	public synchronized void setMoved(boolean moved) {
		this.moved = moved;
	}
	
	public synchronized boolean getMoved() {
		return moved;
	}
	
	public synchronized boolean getResult() {
		return result;
	}
	
	public synchronized void searchDirectory(File directory, String fileName) {
		setFileNameToSearch(fileName);
		
		if(directory.isDirectory()) {
			search(directory);
		} else {
			System.out.println(directory.getAbsoluteFile() + " is not a directory!");
		}
	}
	
	private synchronized void search(File file) {
		if(file.isDirectory()) {
			System.out.println("Searching directory ... " + file.getAbsoluteFile());
			
			if (file.canRead()) {
				for(File temp:file.listFiles()) {
					if(temp.isDirectory()) {
						search(temp);
					} else {
						if (getFileNameToSearch().equals(temp.getName().toLowerCase())) {
							result = true;
							setcurrentDir(temp.toString());
						}
					}
				}
			} else {
				System.out.println(file.getAbsoluteFile() + "Permission Denied");
			}
		}
	}
}
