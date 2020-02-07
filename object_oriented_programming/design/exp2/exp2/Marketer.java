package exp2;

public class Marketer extends Employee{
	private char result;

	public double baseSalary(){
		return super.getSalary() + 15000.0;
	}
	
	public double getSalary() {
        return baseSalary() + testBonus();      // RMB50,000.00 + 15000
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
