package exp2;

import java.util.Date;

class Teacher extends Person  implements PrintInfo{
	public String departmentno,tno;
	double salary;
	public Date hiredate;
	
	
	public String printBasicInfo(){
        System.out.println(name+"  "+tno+"     "+departmentno);
        return name+"  "+tno+"     "+departmentno;
    				
	}
	
	
	public String printDetailInfo(){
        System.out.println(name+"  "+sex+"    "+age+"  "+tno+"     "+departmentno+"          "+hiredate);
        return name+"  "+sex+"    "+age+"  "+tno+"     "+departmentno+"          "+hiredate;
    				
	}
    public void register(){ //20180330-76066002-no1
    	this.salary =6000;
       	this.hiredate=new Date();
	    				
		}
    
    Teacher(String name, char sex, int age, String tno, String departmentno) { //20180330-76066002-no3
		super(name, sex, age);
		 this.name=name;
		 this.sex=sex;
		 this.age=age;
		 this.tno=tno;
		 this.departmentno=departmentno;
	}
 }