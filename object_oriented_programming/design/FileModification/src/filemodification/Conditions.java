package filemodification;

public class Conditions {
	
	private boolean renamed = false;
	private boolean modified = false;
	private boolean pathchanged = false;
	private boolean sizechanged = false;
	
	private int renamednum = 0;
	private int modifiednum = 0;
	private int pathchangednum = 0;
	private int sizechangednum = 0;
	
	public synchronized void setRenamed(boolean renamed) {
		this.renamed = renamed;
	}
	
	public synchronized boolean getRenamed() {
		return renamed;
	}
	
	public synchronized void setModified(boolean modified) {
		this.modified = modified;
	}
	
	public synchronized boolean getModified() {
		return modified;
	}
	
	public synchronized void setPathChanged(boolean pathchanged) {
		this.pathchanged = pathchanged;
	}
	
	public synchronized boolean getPathChanged() {
		return pathchanged;
	}
	
	public synchronized void setSizeChanged(boolean sizechanged) {
		this.sizechanged = sizechanged;
	}
	
	public synchronized boolean getSizeChanged() {
		return sizechanged;
	}
	
	public synchronized void addRenamedNum() {
		this.renamednum++;
	}
	
	public synchronized int getRenamedNum() {
		return renamednum;
	}
	
	public synchronized void addModifiedNum() {
		this.modifiednum++;
	}
	
	public synchronized int getModifiedNum() {
		return modifiednum;
	}
	
	public synchronized void addPathChangedNum() {
		this.pathchangednum++;
	}
	
	public synchronized int getPathChangedNum() {
		return pathchangednum;
	}
	
	public synchronized void addSizeChangedNum() {
		this.sizechangednum++;
	}
	
	public synchronized int getSizeChangedNum() {
		return sizechangednum;
	}

}
