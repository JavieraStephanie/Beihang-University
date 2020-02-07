package exp2;

public class Developer extends Employee{
	private int no;
	private int year;
	private char result;
	
	Developer(int no,int year,char result){
		this.no=no;
		this.year=year;
		this.result=result;
		
	}

	public double baseSalary(){
		return super.getSalary() + (1000*year);
	}
	
	public double getSalary() {
        return baseSalary() + testBonus();      // RMB50,000.00 + 1000.00 * Working Years
    }
	
	public void workYears(int year){
		this.year=year;
	}
	
	public void testResult(char result){
		this.result=result;
	}
	
	private double testBonus(){
		if(this.result=='A')
		{
			return super.getSalary()*30/100;
		}
		else
		{
			return super.getSalary()*10/100;
		}
	}

}
