package bank;

import java.util.ArrayList;

public class test {
	public static AccountSet accountset = new AccountSet();
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Account a1=new Account("01","jane","123", 1);
		accountset.insert(a1);
		Account a2=new Account("02","greece","123", 1);
		accountset.insert(a2);
		/*
		code continue
		*/
		CreditCardAccount c1 = new CreditCardAccount("03","testcredit1","123", 1);
		accountset.insert(c1);
		CreditCardAccount c2 = new CreditCardAccount("04","testcredit2","123", 1);
		accountset.insert(c2);
		c2.depositMoney(5000);
		c2.drawMoney(1000);
		try {
			c2.transferMoney("03", "testcredit1", 500, accountset);
		} catch (InvalidOperationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		DebitCardAccount d1 = new DebitCardAccount("05","testdebit1","123", 1);
		accountset.insert(d1);
		DebitCardAccount d2 = new DebitCardAccount("06","testdebit2","123", 1);
		accountset.insert(d2);
		d2.depositMoney(5000);
		d2.drawMoney(1000);
		try {
			d2.transferMoney("05", "testdebit1", 500, accountset);
		} catch (InvalidOperationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		try {
			accountset.queryByAccountId("03");
		} catch (InvalidOperationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		try {
			accountset.queryByUserId("03");
		} catch (InvalidOperationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		Account a3=new Account("07","maltese","123", 1);
		accountset.insert(a3);
		
		try {
			accountset.removeByAccountId("07");
		} catch (InvalidOperationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			accountset.removeByUserId("07");
		} catch (InvalidOperationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
