package polynomial;

public class PolyCount {
	private Array array = new Array();
	private Array result = new Array();
	
	public boolean addPoly(Input poly) {
		return array.addArray(poly);
	}
	
	public boolean addResult(Input poly) {
		return result.addArray(poly);
	}
	
	public void count() {
		array.sortArray();
		Input poly = array.getArray(0);
		Input poly2 = array.getArray(2);
		int a = 0;
		int b = 0;
		
		while(array.getArraySize() > 0) {
			poly = array.getArray(0);
			a = poly.getCoef();
			
			if(array.getArraySize() > 1) {
				poly2 = array.getArray(1);
				
				while(poly2.getIndex() == poly.getIndex()) {
					b = poly2.getCoef();
					
					a += b;
					array.removeArray(1);
					//System.out.println(a);
					if (array.getArraySize() == 1)
						break;
					poly2 = array.getArray(1);
				}
			}
			//System.out.println("I'm out");
			addResult(new Input(a, poly.getIndex()));
			array.removeArray(0);
			//System.out.println(array.getArraySize());
		}
		
		while (result.getArraySize() > 0) {
			Input res = result.getArray(0);
			System.out.println("(" + res.getCoef() + ", " + res.getIndex() + ")");
			result.removeArray(0);
		}
	}

}
