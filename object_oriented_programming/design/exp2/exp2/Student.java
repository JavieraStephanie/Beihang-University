package exp2;

import java.util.Date;

class Student extends Person implements PrintInfo{
		public String classno,sno;//学号和班号
		public Date registerdate;//注册时间
		
		public void updateAge(int age){
			this.age=age;
		}
	    
		public void register() {
	    	this.registerdate=new Date();
	    }
		
		public String  printBasicInfo(){//打印输出学生基本信息
	        System.out.println(name+"  "+sno+"     "+classno);
	        return name+"  "+sno+"     "+classno;
	    				
		}
	    
		public String  printDetailInfo(){//打印输出学生详细信息
	        System.out.println(name+"  "+sex+"    "+age+"  "+sno+"     "+classno+"   "+registerdate);
	        return name+"  "+sex+"    "+age+"  "+sno+"     "+classno+"   "+registerdate;
	    				
		}
		
		Student(String name,char sex,int age,String sno,String classno){
			super(name, sex, age); //20180330-76066002-no2
			 this.name=name;
			 this.sex=sex;
			 this.age=age;
			 this.sno=sno;
			 this.classno=classno;
		}
		
	}
	
	
	

