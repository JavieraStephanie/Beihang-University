package taxi;

import java.awt.Point;

public class Request {
	
	private Point src;
	private Point dst;
	public double req_time;
	
	public Request(Point src, Point dst, double req_time) {
		this.src = src;
		this.dst = dst;
		this.req_time = req_time;
	}
	
	public Point getSrc() {
		return this.src;
	}
	
	public Point getDst() {
		return this.dst;
	}
	
	public double getTime() {
		return this.req_time;
	}
}
