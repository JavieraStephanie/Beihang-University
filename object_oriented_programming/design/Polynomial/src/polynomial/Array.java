package polynomial;

import java.util.ArrayList;
import java.util.Collections;

public class Array {
	private ArrayList<Input> array = new ArrayList<Input>();;
	
	public boolean addArray (Input poly) {
		array.add(poly);
		return true;
	}
	
	public boolean removeArray (int i) {
		array.remove(i);
		return true;
	}
	
	public Input getArray (int i) {
		return array.get(i);
	}
	
	public int getArraySize () {
		return array.size();
	}
	
	public void sortArray() {
		Collections.sort(array);
	}
	
}
