package demo2;

import java.util.Random;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;
/**
 服务中心
 
 */
public class Center extends Thread {  
    private BlockingQueue<Waiter> waiters;  
    private BlockingQueue<Customer> customers;  
    
    private Random rand = new Random(10);
    
    private final static int PRODUCERSLEEPSEED = 3000;  
    private final static int CONSUMERSLEEPSEED = 100000;  
  
    public Center(int num) {  
    	//创建提供服务的柜台队列和取得号的客户队列
    	this.waiters = new LinkedBlockingQueue<Waiter>(num);  
        for (int i = 0; i < num; i++) {  
            waiters.add(new Waiter());  
        }
        
        this.customers = new LinkedBlockingQueue<Customer>();  
        for (int j = 0; j < 20; j++) {  
            this.customers.add(new Customer());  
        }  
       
    }  
       //取号机生产等待服务的客户，注意模拟前后两个客户之间的时间间隔
    public void produce() {  
       try {
		TimeUnit.MILLISECONDS.sleep(rand.nextInt(PRODUCERSLEEPSEED));
	} catch (InterruptedException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
       this.customers.add(new Customer()); 
    }  
  //客户获得服务，请注意线程安全的实现
    public void consume() {  
        try {
        	Waiter waiter = this.waiters.take();  
            this.waiters.remove(waiter);
            
            Customer customer = this.customers.take();  
            this.customers.remove(customer); 
            
            System.out.println(waiter + "号窗口正在为" + customer + "号顾客办理业务");  
            TimeUnit.MILLISECONDS.sleep(rand.nextInt(CONSUMERSLEEPSEED));  
  
            this.waiters.add(waiter);  
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }  
} 