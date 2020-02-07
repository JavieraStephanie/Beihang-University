package exp2;

public class TestEmployee {
	public static void main(String[] args) {
		
		Employee[] employee=new Employee[8];
		
		employee[0]=new Developer(1,1,'A');
		employee[0].printSalary();
		
		employee[1]=new Developer(1,1,'B');
		employee[1].printSalary();

	}

}
