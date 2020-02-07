package exp2;

public class FinancialOfficer extends Employee{
	private char result;

	public double baseSalary(){
		return super.getSalary();
	}
	
	public double getSalary() {
        return super.getSalary() + testBonus();      // RMB50,000.00
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
