package bank;


public class DebitCardAccount extends Account {
    private double annualInterestRate;//年存款利率
    
    
    public DebitCardAccount(String id,String name,String pwd, int branchid) {
    	super(id,name,pwd,branchid);
    	this.setBalance(10.0);
    	}
    
    
    public void changeStatus() {
    	if(this.getBalance()<10)
    		this.setIsActivate(false);
    	else 
    		this.setIsActivate(true);
    }
	
    //储蓄账户存款
    public boolean depositMoney(double money) {
    	if (money <= 0) 	
			return false;    	
    	double balance=this.getBalance();
		balance += money*(1+annualInterestRate);
		this.setBalance(balance);
		changeStatus();
		return true;    
    	}
   
    //储蓄账户取款
    public boolean drawMoney(double money,String pwd) {
    	if (money <= 0) 	
			    return false;
    	if(!this.getIsActivate()) return false;
       	if(!(this.getPwd().equals(pwd))) return false;
		if (this.getBalance()-10< money)
				return false;
		this.setBalance(this.getBalance()-money);
	    return true;
	}
    
    //储蓄账户转账
    public boolean transferMoney(String AccountId,String name,double money,AccountSet accounts) throws InvalidOperationException{
    	if (this.getBalance()-10< money) return false;
    	else  
    		return super.transferMoney(AccountId, name, money, accounts);
    }
    
	public void setRate(double interestRate){
  		this.annualInterestRate=interestRate;
  	}
  	
  	public double getRate()
  	{
  		return this.annualInterestRate;
  	}
}

