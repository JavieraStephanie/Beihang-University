package exp2;

public class ReimbursementStatus {
	public String fail(){
		System.out.println("该报销条目不合格");
		return "该报销条目不合格";
	}
	
	public String success(){
		System.out.println("已成功提交");
		return "已成功提交";
	}
}
