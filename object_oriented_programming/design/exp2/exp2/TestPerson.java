package exp2;

public class TestPerson {
	public static void main(String[] args)
	{
		Person[] person=new Person[4];
		
		
		person[0]=new Student("Jin",'M',20,"201504135146","061501");//���һ��ѧ����Ϣ��Jin,Male,20�꣬ѧ��201504135146�����061501
		person[0].register();//ѧ��ע��
	    ((Student) person[0]).updateAge(23);//���¸��������� //20180330-76066002-no4
	    person[0].toString();//��ӡ���
	    
	    
	    person[1]=new Person("Kate",'F',21);//���һ��ѧ����Ϣ��Kate,Female,21�꣬ѧ�Ű����ʱδ֪
	    Student stu=(Student)person[1];
	    stu.register();//ѧ��ע��
	    stu.updateAge(25);//���¸���������
	    stu.toString();//��ӡ���
	    stu.printBasicInfo();//��ӡ���������Ϣ
	    
	    person[2]=new Teacher("Rene",'M',35,"06","01452");//���һ����ʦ��Ϣ��Rene,Male,35�꣬6ϵ������Ϊ01452
	    person[2].register();//��ɽ�ʦ��ע�ᣬ��¼ע��ʱ�䲢�趨����н��
	    person[2].toString();
	    
	    person[3]=new Person("Jason",'M',41);//���һ����ʦ��Ϣ��Jason,Male,41�꣬Ժϵ�͹�����ʱδ֪
	    Teacher te=(Teacher)person[3];
	    te.register();//��ʦע��
	    te.printDetailInfo();//��ӡ���
	    }
	    
	    
	    
	    
	}   
		
		
