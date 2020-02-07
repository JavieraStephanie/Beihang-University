package taxi;

import java.awt.Point;
import java.util.ArrayList;
import java.util.Collections;

public class Taxi implements Runnable, Comparable<Taxi> {
	private int taxinum;
	private int review = 0;
	private TaxiGUI gui = null;
	private Point curPos = new Point (0,0);
	private Status taxiStat = Status.WAITING;
	private Thread taxiThread = null;
	private Request curReq = null;
	private boolean noUp = false;
	private boolean noDown = false;
	private boolean noLeft = false;
	private boolean noRight = false;
	
	public Taxi (int taxinum) {
		this.taxinum = taxinum;
	}
	
	public void setGUI(TaxiGUI gui) {
		this.gui = gui;
	}
	
	public int getTaxiNum() {
		return this.taxinum;
	}
	
	public int getReview() {
		return this.review;
	}
	
	public Point getCurPos() {
		return this.curPos;
	}
	
	public Status getTaxiStat() {
		return this.taxiStat;
	}
	
	public synchronized void addReview(int add) {
		this.review += add;
	}
	
	public void setCurPos(Point curPos) {
		this.curPos = curPos;
	}
	
	public void setTaxiStat(Status taxiStat) {
		this.taxiStat = taxiStat;
	}

	public int compareTo(Taxi taxi) {		
		int comparereview=((Taxi)taxi).getReview();
		return comparereview-this.review;
	}
	
	public void setRequest(Request req) {
		this.curReq = req;
	}
	
	public void moveDown() {
		curPos.x += 1;
		this.taxiStat = Status.SERVING;
		gui.SetTaxiStatus(this.taxinum, new Point(curPos.x, curPos.y), 1);
		gv.stay(200);
	}
	
	public void moveUp() {
		curPos.x -= 1;
		this.taxiStat = Status.SERVING;
		gui.SetTaxiStatus(this.taxinum, new Point(curPos.x, curPos.y), 1);
		gv.stay(200);
	}
	
	public void moveRight() {
		curPos.y += 1;
		this.taxiStat = Status.SERVING;
		gui.SetTaxiStatus(this.taxinum, new Point(curPos.x, curPos.y), 1);
		gv.stay(200);
	}
	
	public void moveLeft() {
		curPos.y -= 1;
		this.taxiStat = Status.SERVING;
		gui.SetTaxiStatus(this.taxinum, new Point(curPos.x, curPos.y), 1);
		gv.stay(200);
	}
	
	public boolean leftExist() {
		if (guigv.m.map[(int) curPos.getX()][(int) curPos.getY()-1] == 1 || guigv.m.map[(int) curPos.getX()][(int) curPos.getY()-1] == 3) {
			return true;
		}
		return false;
	}
	
	public boolean rightExist() {
		if (guigv.m.map[(int) curPos.getX()][(int) curPos.getY()] == 1 || guigv.m.map[(int) curPos.getX()][(int) curPos.getY()] == 3) {
			return true;
		}
		return false;
	}
	
	public boolean upExist() {
		if (guigv.m.map[(int) curPos.getX()-1][(int) curPos.getY()] == 2 || guigv.m.map[(int) curPos.getX()-1][(int) curPos.getY()] == 3) {
			return true;
		}
		
		return false;
	}
	
	public boolean downExist() {
		if (guigv.m.map[(int) curPos.getX()][(int) curPos.getY()] == 2 || guigv.m.map[(int) curPos.getX()][(int) curPos.getY()] == 3) {
			return true;
		}
		return false;
	}
	
	public void findRoad(Point taxiPos, Point destPos) {
		while (curPos.getX() != destPos.getX() || curPos.getY() != destPos.getY()) {
			if (curPos.getX() < destPos.getX()) {
				if (downExist()) {
					moveDown();
					noUp = true;
				}
				else if (curPos.getX() != 0 || curPos.getY() != 0) {
					if(noRight) {
						while (leftExist() && !downExist()) {
							moveLeft();
						}
						noRight = false;
						moveDown();
						noUp = true;
					}
					
					else if (noLeft) {
						while (rightExist() && !downExist()) {
							moveLeft();
						}
						noLeft = false;
						moveDown();
						noUp = true;
					}
					continue;
				}
			}
			if (curPos.getX() > destPos.getX()) {
				if (upExist()) {
					moveUp();
					noDown = true;
				}
				else if (curPos.getX() != 0 || curPos.getY() != 0) {
					if (noRight) {
						while (leftExist() && !upExist()) {
							moveLeft();
						}
						noRight = false;
						moveUp();
						noDown = true;
					}
					else if (noLeft) {
						while (rightExist() && !upExist()) {
							moveRight();
						}
						noLeft = false;
						moveUp();
						noDown = true;
					}
					continue;
				}
			}
			if (curPos.getY() < destPos.getY()) {
				if (rightExist()) {
					moveRight();
					noLeft = true;
				}
				else if (curPos.getX() != 0 || curPos.getY() != 0) {
					if (noUp) {
						while (downExist() && !rightExist()) {
							moveDown();
						}
						noUp = false;
						moveRight();
						noLeft = true;
					}
					
					else if (noDown) {
						while (upExist() && !rightExist()) {
							moveDown();
						}
						noDown = false;
						moveRight();
						noLeft = true;
					}
					continue;
				}
			}
			if (curPos.getY() > destPos.getY()) {
				if (leftExist()) {
					moveLeft();
					noRight = true;
				}
				else if (curPos.getX() != 0 || curPos.getY() != 0) {
					if (noUp) {
						while (downExist() && !leftExist()) {
							moveDown();
						}
						noUp = false;
						moveLeft();
						noLeft = true;
					}
					
					else if (noDown) {
						while (upExist() && !leftExist()) {
							moveDown();
						}
						noDown = false;
						moveLeft();
						noLeft = true;
					}
					continue;
				}
			}
		}
	}
	
	public void getOrder() {
		System.out.println("HERE");
		System.out.println(curPos.getX() + ", " + curPos.getY());
		System.out.println(this.curReq.getSrc().getX() + ", " + this.curReq.getSrc().getY());
		
		findRoad(curPos, curReq.getSrc());
	}
	public void moveTaxi() {
		System.out.println("HERE?");
		System.out.println(curPos.getX() + ", " + curPos.getY());
		System.out.println(this.curReq.getDst().getX() + ", " + this.curReq.getDst().getY());
		
		findRoad(curPos, curReq.getDst());
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		this.taxiStat = Status.SERVING;
		
		getOrder();
		moveTaxi();
		
		gui.SetTaxiStatus(this.taxinum, new Point(curPos.x, curPos.y), 2);
		this.addReview(3);
		this.taxiStat = Status.WAITING;
		
		try {
			Thread.sleep(20000);
			gui.SetTaxiStatus(this.taxinum, new Point(curPos.x, curPos.y), 0);
			this.taxiStat = Status.STOP;
			Thread.sleep(1000);
			gui.SetTaxiStatus(this.taxinum, new Point(curPos.x, curPos.y), 2);
			this.taxiStat = Status.WAITING;
		} catch (Exception except) {
			System.out.print(except.getMessage());
		}
		
		taxiThread = null;
		return;
	}
	
	public void start() {
		if (taxiThread == null) {
			taxiThread = new Thread (this);
			taxiThread.start();
		}
	}
}

class Taxis {
	private ArrayList<Taxi> taxis = new ArrayList<Taxi>();
	
	public boolean addTaxi (int taxinum) {
		taxis.add(new Taxi(taxinum));
		return true;
	}
	
	public Taxi getTaxi (int i) {
		return taxis.get(i);
	}
	
	public int getTaxiSize() {
		return taxis.size();
	}
	
	public void sortTaxi() {
		Collections.sort(taxis);
	}
}
