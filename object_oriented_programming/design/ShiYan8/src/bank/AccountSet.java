package bank;

import java.util.ArrayList;
import java.util.Iterator;

public class AccountSet {
	
	ArrayList<Account> accounts= new ArrayList<Account>();
	
   //constructors
   public AccountSet(){
	   this.accounts.isEmpty();
	   return;
   }
   
   
   public boolean insert(Account a){
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
	   if(this.queryByAccountId(id)==null) {
		   throw new InvalidOperationException("Invalid Account!");
	   }else {
		   accounts.remove(id);
	   }
   }

   public void removeByUserId(String id)throws InvalidOperationException{
	   if(this.queryByUserId(id)==null) {
		   throw new InvalidOperationException("Invalid User!");
	   }else {
		   accounts.remove(id);
	   }
   }
   
  
   public boolean isIn(Account a){
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
	   return this.accounts.size();
   }   
  
   public Iterator elements(){
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
	   if(accountId==null) {
		   return null;
	   }
	   
	   Account a = new Account(accountId, null, null, 1);
	   
	   if(accounts.contains(a) && a.getAccountId() == accountId) {
		   return a;
	   }else {
		   throw new InvalidOperationException("Invalid Account!");
	   }
   }   
          
   public AccountSet queryByUserId(String userId)throws InvalidOperationException{
	   if(userId == null) {
		   return null;
	   }
	   
	   Account a = new Account(userId, null, null, 1);
	   
	   if(accounts.contains(a) && a.getUserId()==userId) {
		   return null;
	   }else {
		   throw new InvalidOperationException("Invalid User!");
	   }
   }   
   
}

