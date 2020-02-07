package exp2;

public class Seller extends Employee{
	private int order;

	public double baseSalary(){
		return super.getSalary() + 15000.0;      // RMB50,000.00 + 15000
	}
	public double getSalary() {
		if(order<30000)
		{
			return baseSalary()*80/100;
		}
		else
		{
			return baseSalary() + bonus();
		}
    }
	
	public double bonus(){
		return baseSalary()*20/100;
	}
	
	public void orderSum(int order){
		this.order=order;
	}

}
