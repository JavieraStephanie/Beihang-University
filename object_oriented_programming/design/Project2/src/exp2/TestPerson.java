package exp2;

public class TestPerson {
	public static void main(String[] args)
	{
		Person[] person=new Person[4];
		
		
		person[0]=new Student("Jin",'M',20,"201504135146","061501");//���һ��ѧ����Ϣ��Jin,Male,20�꣬ѧ��201504135146�����061501
		person[0].register();//ѧ��ע��
	    ((Student) person[0]).updateAge(23);//���¸��������� //20180330-76066002-no4
	    person[0].toString();//��ӡ���
	    
	    
	    //20180330-76066002-no5
	    person[1]=new Student("Kate",'F',21, null, null);//���һ��ѧ����Ϣ��Kate,Female,21�꣬ѧ�Ű����ʱδ֪
	    //Student stu=(Student)person[1];
	    person[1].register();//ѧ��ע��
	    ((Student) person[1]).updateAge(25);//���¸���������
	    person[1].toString();//��ӡ���
	    ((Student) person[1]).printBasicInfo();//��ӡ���������Ϣ
	    
	    person[2]=new Teacher("Rene",'M',35,"06","01452");//���һ����ʦ��Ϣ��Rene,Male,35�꣬6ϵ������Ϊ01452
	    person[2].register();//��ɽ�ʦ��ע�ᣬ��¼ע��ʱ�䲢�趨����н��
	    person[2].toString();
	    
	  //20180330-76066002-no6
	    person[3]=new Teacher("Jason",'M',41, null, null);//���һ����ʦ��Ϣ��Jason,Male,41�꣬Ժϵ�͹�����ʱδ֪
	    //Teacher te=(Teacher)person[3];
	    person[3].register();//��ʦע��
	    ((Teacher) person[3]).printDetailInfo();//��ӡ���
	    }
	    
	    
	    
	    
	}   
		
		
