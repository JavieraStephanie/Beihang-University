package TicketDemo;

import java.util.Random;

public class SaleTicket implements Runnable {

	public int count;
	public int avaliable;
    
	
	public SaleTicket() {
		Tickets ts =new Tickets();
		avaliable=ts.getTotal();
		count = 0;
		
	}

	public void run() {
	       while (avaliable > 0) {        
	                  count++;
	                  avaliable--;
	                  System.out.println(Thread.currentThread().getName() + "\t当前票号：" + count+"\t余票张数："+avaliable);
	           	       }
	 }

public static void main(String[] args) {
SaleTicket st = new SaleTicket();
for(int i=1; i<=5; i++) {
new Thread(st, "售票点" + i).start();
}
}
}
