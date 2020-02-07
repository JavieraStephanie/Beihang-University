package tickets;

public class TicketSale implements Runnable{
	
	public int count;
	public int available;
	
	public TicketSale() {
		Tickets ts = new Tickets();
		available = ts.getTotal();
		count = 0;
	}
	
	public void run() {
		while(available > 0) {
			try {
				synchronized(this) {
					count++;
					available--;
					System.out.println(Thread.currentThread().getName() + "\t当前票号： " + count + "\t余票张数： " + available);
				}
				Thread.sleep(500);
			}
			
			catch(Exception e){
				e.printStackTrace();
			}
		}
		
	}

	public static void main(String[] args) {
		TicketSale st = new TicketSale();
		for(int i=1; i<=5; i++) {
			new Thread(st, "售票点" + i).start();
		}

	}

}
