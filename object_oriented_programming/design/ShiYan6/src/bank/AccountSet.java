﻿package bank;

import java.util.ArrayList;
import java.util.Iterator;

public class AccountSet {
	
//OVERVIEW:帐户的集合，不区别帐户类别
//任意选择一种数据结构，对照规格补全代码
	
	ArrayList<Account> accounts= new ArrayList<Account>();
	
   //constructors
   public AccountSet(){
   /**
    * @REQUIRES:None;
    * @MODIFIES:this;
    * @EFFECTS： (\result = \this) &&(\this.isEmpty());
    */
	//请补全构造函数
	   this.accounts.isEmpty();
	   return;
   }
   
   
   public boolean insert(Account a){
   /**
    * @ REQUIRES: a!= null ;
    * @ MODIFIES: this;
    * @ EFFECTS: 
    * (\result==false)==>(\old(\this).contains(a)==true)
    * (\this.size == \old(\this).size+1) && (\this.contains(a)==true)&&(\result==true); 
    */
	//请根据规格补充代码
	   if(a==null) {
		   return false;
	   }
	   
	   if(this.isIn(a)) {
		   return false;
	   }else {
		   accounts.add(a);
		   return true;
	   }
   }   
   
   public void removeByAccountId(String id) throws InvalidOperationException{
    /**
     * @ MODIFIES:this;
     * @ EFFECTS:
     * (\old(\this).queryByAccountId(id) !=null) ==> (\this.size == \old(\this).size-1) && (\this.contains(\old(\this).queryByAccountId(id))==false);
     * (\old(\this).queryByAccountId(id)==null)==>exceptional_behavior(InvalidOperationException("Invalid Account!"));                   
     */
	//请根据规格补充代码
	   
	   if(this.queryByAccountId(id)==null) {
		   throw new InvalidOperationException("Invalid Account!");
	   }else {
		   accounts.remove(id);
	   }
   }

   public void removeByUserId(String id)throws InvalidOperationException{
    /**
     * @ MODIFIES:this;
     * @ EFFECTS:
     * (\old(\this).queryByUserId(id) !=null) ==> (\this.size == \old(\this).size-\old(\this).queryByUserId(id).size()) && (this.contains(\old(\this).queryByUserId(id))==false));           
     * (\old(\this).queryByUserId(id) ==null)==>exceptional_behavior(InvalidOperationException("Invalid User!"))                   
    */
	//请根据规格补充代码
	   if(this.queryByUserId(id)==null) {
		   throw new InvalidOperationException("Invalid User!");
	   }else {
		   accounts.remove(id);
	   }
   }
   
  
   public boolean isIn(Account a){
   /**
    * @ REQUIRES: a!= null ;
    * @ MODIFIES:none; 
    * @ EFFECTS:
    * (\result==true)==>(this.contains(a)==true);
    * (\result==false)==>(this.contains(a)==false);
    */
	//请根据规格补充代码
	   if(a==null) {
		   return false;
		   }
	   
	   if(this.accounts.contains(a)){
		   return true;
	   }else {
		   return false;
	   }
   }   

   public long size(){
   /**
    * @ EFFECTS: 
    * (\result==this.size());
    */
	//请根据规格补充代码
	   return this.accounts.size();
   }   
  
   public Iterator elements(){
    /**
	 * @ Effects: 
	 * (\result != null) && (\result instanceof Iterator) && (\all int i; 0<=i<\this.size;\result.contains(\this[i])); 
	 */
	//请根据规格补充代码
	   Object[] tempaccounts = accounts.toArray();
	   Iterator elem = new Iterator() {
		   private int i = 0;

		@Override
		public boolean hasNext() {
			// TODO Auto-generated method stub
			return i < tempaccounts.length && tempaccounts[i] != null;
		}

		@Override
		public Object next() {
			// TODO Auto-generated method stub
			return tempaccounts[i++];
		}
		   
	   };
	   return elem;
   }   
   
   public Account queryByAccountId(String accountId) throws InvalidOperationException{
   /**
    * @ REQUIRES: accountId!= null ;
    * @ EFFECTS: 
    * (\result==a)==>(\all Account a;(\this.contains(a)==true)&&a.getAccountId()==accountId);
    * (\all Account a;a.getAccountId()==accountId && (\this.contains(a)==false))==>exceptional_behavior("Invalid Account!") ;
    */
   //请根据规格补充代码
	   if(accountId==null) {
		   return null;
	   }
	   
	   Account a = new Account(accountId, null, null);
	   
	   if(accounts.contains(a) && a.getAccountId() == accountId) {
		   return a;
	   }else {
		   throw new InvalidOperationException("Invalid Account!");
	   }
   }   
          
   public AccountSet queryByUserId(String userId)throws InvalidOperationException{
   /**
    * @ REQUIRES: userId!= null ;        
    * @ EFFECTS: 
    * (\all Account a;(\result.contains(a)==true)==>a.getUserId()==userId && (\this.contains(a)==true));
    * (\all Account a;a.getUserId()==userId && (\this.contains(a)==false))==>exceptional_behavior("Invalid User!") ;  
    */
   //请根据规格补充代码
	   if(userId == null) {
		   return null;
	   }
	   
	   Account a = new Account(userId, null, null);
	   
	   if(accounts.contains(a) && a.getUserId()==userId) {
		   return null;
	   }else {
		   throw new InvalidOperationException("Invalid User!");
	   }
   }   
    
   public boolean repOK(){
   //请将repOK()方法补充完整
	//不变式：
	   return true;
   }
   
}

