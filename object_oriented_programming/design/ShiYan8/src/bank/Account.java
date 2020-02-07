package bank;

import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.*;

//OVERVIEW:账户都具有账户id，用户id，用户姓名，用户密码，余额，激活状态
public class Account {

	private String AccountId;//账户id
	private String UserId;//用户id
	private String name;//用户姓名
	private String pwd;//用户密码
	private double balance=0.0;//账户余额
	private boolean isActivate=true;//账户激活状态
	private static int counter = 0;
	private String creationdate;
	private int branchId;
		
    public Account(String id, String name, String pwd, int branchid) {
		this.AccountId = String.valueOf(counter++);
		this.UserId=id;
		this.name=name;
		this.pwd=pwd;
		this.isActivate=true;
		this.creationdate=getDate();
		this.branchId=branchid;
		}		
    
    public String getDate() {
    	Date date = new Date();
    	return date.toString();
    }
  
	public String getAccountId() {
		return AccountId;
	}

	public void setAccountId(String accountId) {
		this.AccountId = accountId;
	}

	public String getUserId() {
		return UserId;
	}

	public void setUserId(String id) {
		this.UserId = id;
	}
	
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
	public String getPwd() {
		return pwd;
	}

	public void setPwd(String pwd) {
		this.pwd = pwd;
	}

	public double getBalance() {
		return this.balance;
	}

	public void setBalance(double balance) {
		this.balance = balance;
	}

	public boolean getIsActivate() {
		return isActivate;
	}

	public void setIsActivate(boolean isActivate) {
		this.isActivate = isActivate;
	}
	
	
	//存款
	public boolean depositMoney(double money) {
		if (money <= 0) 	
			return false;
		this.balance += money;
		return true;
	}
	
	
    //取款
	public boolean drawMoney(double money) {
		if (money <= 0) 	
		    return false;
	    if(!this.getIsActivate()) return false;
	    if (this.balance< money)
			return false;
	    this.balance -= money;
        return true;
	}
	
	public Account queryByAccountId(String accountId) throws InvalidOperationException{
		   if(accountId==null) {
			   return null;
		   }
		   
		   Account accounts;
		   Account a = new Account(accountId, null, null, 1);
		   return a;
	   }
	
	//转账
	public boolean transferMoney(String AccountId,String name,double money,AccountSet accounts)throws InvalidOperationException {
		if(money<=0) return false;
		if(!this.getIsActivate()) return false;
		Account target=accounts.queryByAccountId(AccountId);
		if(target!=null&&target.getName().equals(name))
		{
			this.balance -= money;
		target.setBalance(target.getBalance()+money);
	        return true;
		}
		return false;
	}
	
	public String toString(){
	  return ("AccountId:"+AccountId+"UserId:"+UserId+"Name:"+name+"isActivate:"+isActivate);
	}
}
