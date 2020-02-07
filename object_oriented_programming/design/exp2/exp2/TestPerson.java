package exp2;

public class TestPerson {
	public static void main(String[] args)
	{
		Person[] person=new Person[4];
		
		
		person[0]=new Student("Jin",'M',20,"201504135146","061501");//添加一条学生信息：Jin,Male,20岁，学号201504135146，班号061501
		person[0].register();//学生注册
	    ((Student) person[0]).updateAge(23);//更新该生的年龄 //20180330-76066002-no4
	    person[0].toString();//打印输出
	    
	    
	    person[1]=new Person("Kate",'F',21);//添加一条学生信息，Kate,Female,21岁，学号班号暂时未知
	    Student stu=(Student)person[1];
	    stu.register();//学生注册
	    stu.updateAge(25);//更新该生的年龄
	    stu.toString();//打印输出
	    stu.printBasicInfo();//打印输出基本信息
	    
	    person[2]=new Teacher("Rene",'M',35,"06","01452");//添加一条教师信息，Rene,Male,35岁，6系，工号为01452
	    person[2].register();//完成教师的注册，记录注册时间并设定基本薪资
	    person[2].toString();
	    
	    person[3]=new Person("Jason",'M',41);//添加一条教师信息，Jason,Male,41岁，院系和工号暂时未知
	    Teacher te=(Teacher)person[3];
	    te.register();//教师注册
	    te.printDetailInfo();//打印输出
	    }
	    
	    
	    
	    
	}   
		
		
