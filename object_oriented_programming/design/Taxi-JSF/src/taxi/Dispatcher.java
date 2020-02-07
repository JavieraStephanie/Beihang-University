package taxi;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;

public class Dispatcher implements Runnable {
	ScheduledExecutorService exe = Executors.newSingleThreadScheduledExecutor();
	
	private TaxiGUI gui = null;
	private Thread dispThread;
	private Taxis taxis = new Taxis();
	private Queue queue = new Queue();
	
	public void initTaxi(TaxiGUI gui) throws InvalidRequestException, SameRequestException {
		/**
		 * @REQUIRES: gui;
		 * @MODIFIES: this.taxis, this.gui;
		 * @EFFECTS:
		 * \old(\this.gui) == gui;
		 * (\this.taxis.size == \old(\this.taxis).size+100); 
		 */
		
		this.gui = gui;
		for (int i = 0; i < 100; i++) {
			taxis.addTaxi(i+1);
			taxis.getTaxi(i).setGUI(this.gui);
		}
	}
	
	public boolean addReq(Request req) throws InvalidRequestException, SameRequestException {
		/**
		 * @REQUIRES: req;
		 * @MODIFIES: this.queue;
		 * @EFFECTS: \result == \this.queue.addQueue(req);
		 */
		return queue.addQueue(req);
	}
	
	public Queue getQueue() {
		return this.queue;
	}

	public synchronized void getOrder(Request curReq) {
		/**
		 * @REQUIRES: curReq;
		 * @MODIFIES: this.taxis;
		 * @EFFECTS:
		 * \this.taxis.sort();
		 * (\old.taxis.taxi(i).getStatus() == Status.WAITING) ==> (\this.taxis.taxi(i).setStatus() == Status.TAKEORDER);
		 * (\old.taxis.taxi(i).getStatus() == Status.TAKEORDER) ==> \this.taxis.taxi(i).start() ==> \this.taxis.remove(i);
		 */
		
		taxis.sortTaxi();
		long start = System.currentTimeMillis();
		long end = start + 3*1000;
		gui.RequestTaxi(curReq.getSrc(), curReq.getDst());
		for (int i = 0; i < 100; i ++) {
			if (taxis.getTaxi(i).getTaxiStat() == Status.WAITING) {
				taxis.getTaxi(i).setTaxiStat(Status.TAKEORDER);
			}
		}
		while (System.currentTimeMillis() < end) {
			for (int i = 0; i < 100; i++) {
				if (taxis.getTaxi(i).getTaxiStat() == Status.TAKEORDER) {
					if ((taxis.getTaxi(i).getCurPos().getX() - curReq.getSrc().getX() <= 4) || (taxis.getTaxi(i).getCurPos().getY() - curReq.getSrc().getY() <= 4)) {
						taxis.getTaxi(i).addReview(1);
						taxis.getTaxi(i).setRequest(curReq);
						try {
							queue.removeQueue(0);
						} catch (Exception except) {
							System.out.print(except.getMessage());
						}
						taxis.getTaxi(i).start();
						break;
					}
				}
			}
			if (queue.getQueueSize() <= 0) {
				for (int i = 0; i < 100; i ++) {
					if (taxis.getTaxi(i).getTaxiStat() == Status.TAKEORDER) {
						taxis.getTaxi(i).setTaxiStat(Status.WAITING);
					}
				}
				break;
			}
		}
	}
	
	@Override
	public void run() {
		Request curReq;
		// TODO Auto-generated method stub
		if (queue.getQueueSize() > 0) {
			curReq = queue.getQueue(0);
			getOrder(curReq);
		}
	}

	public void start() {
		// TODO Auto-generated method stub
		dispThread = new Thread (this);
		dispThread.start();
	}
}
