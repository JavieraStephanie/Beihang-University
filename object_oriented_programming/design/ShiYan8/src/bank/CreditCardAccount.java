package bank;


public class CreditCardAccount extends Account{
		private double overdraftLimit;//最高透支额度
	
	  	public CreditCardAccount(String id,String name,String pwd, int branchid){
	  		super(id,name,pwd,branchid);
	  		this.setBalance(0.0);
	  	}
	  	
	  	public void setMax(double money){
	  		this.overdraftLimit=money;
	  	}
	  	
	  	public double getMax()
	  	{
	  		return this.overdraftLimit;
	  	}
	 		  	
	  	public void changeStatus() {
	     	if(this.getBalance()<0.0-overdraftLimit)
	     		this.setIsActivate(false);
	     	else 
	     		this.setIsActivate(true);
	     }
	  	 
		//信用卡账户存款
	  	 public boolean depositMoney(double money) {
	  		super.depositMoney(money);
	 		changeStatus();
	 		return true;
	     }
	  	 
	  	//信用卡账户消费
		public boolean drawMoney(double money) {
			double balance=this.getBalance();
			if(!this.getIsActivate()) return false;
	  		if (balance + this.overdraftLimit < money)
	  			return false;
			this.setBalance(balance-money);
			return true;
		}
}