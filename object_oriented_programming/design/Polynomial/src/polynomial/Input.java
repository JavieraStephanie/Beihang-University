package polynomial;

import java.util.Scanner;

public class Input implements Comparable<Input> {
	
	private int coef;
	private int index;
	
	public Input(String poly) {
		String temp[] = poly.split(",");
		
		this.coef = Integer.parseInt(temp[0]);
		this.index = Integer.parseInt(temp[1]);
	}
	
	public Input(int coef, int index) {		
		this.coef = coef;
		this.index = index;
	}
	
	public int getCoef() {
		return this.coef;
	}
	
	public int getIndex() {
		return this.index;
	}
	
	public static void inputHandler(PolyCount polycount) throws Exception {
		String input;
		Scanner scanner = new Scanner(System.in);
		
		input = scanner.nextLine();
		
		try {
			//INPUT VALIDATION
			//Replace all occurrences of " " and "\t" to nothing
			input = input.replace(" ", "").replace("\t", "");
			input = input.replace("{", "").replace("}", "");
			
			char []val = input.toCharArray();
			int content = 0;
			String poly = ""; //string to parse
			
			for(int i = 0; i<val.length; i++) {
				if(val[i] == '(' && content==0) {
					content++;
					continue;
				}
				else if(val[i] >= '0' && val[i] <= '9' && content==1) {
					while(val[i]!=',' && i<val.length) {
						poly += val[i];
						i++;
					}
					content++;
					poly += ',';
					continue;
				}
				else if(val[i] >= '0' && val[i] <= '9' && content==2) {
					while(val[i]!=')' && i<val.length) {
						poly += val[i];
						i++;
					}
					polycount.addPoly(new Input(poly));
					if(i<val.length-1) {
						i++;
						content = 0;
						poly = "";
						
						if (val[i] == '-') {
							for(; i<val.length; i++) {
								if(val[i] == '(' && content==0) {
									content++;
									continue;
								}
								else if(val[i] >= '0' && val[i] <= '9' && content==1) {
									poly += '-';
									while(val[i]!=',' && i<val.length) {
										poly += val[i];
										i++;
									}
									content++;
									poly += ',';
									continue;
								}
								else if(val[i] >= '0' && val[i] <= '9' && content==2) {
									while(val[i]!=')' && i<val.length) {
										poly += val[i];
										i++;
									}
									polycount.addPoly(new Input(poly));
									i++;
									content = 0;
									poly = "";
									
									if (val[i] == '+')
										break;
									continue;
								}
							}
						}
					}
					continue;
				}
				else
					throw new Exception ("Invalid format!");
			}
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
		scanner.close();
	}
	
	public static void main(String[] args) throws Exception {
		PolyCount polycount = new PolyCount();
		
		try {
			inputHandler(polycount);
			polycount.count();
		}
		catch (Exception except) {
			System.out.print(except.getMessage());
		}
		//System.out.println("DONE");
	}

	public int compareTo(Input comparein) {
		int compareindex=((Input)comparein).getIndex();
		return this.index-compareindex;
	}

}
