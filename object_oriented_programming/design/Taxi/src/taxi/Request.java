package taxi;

import java.util.Set;

public class Request {
	
	private String type;
	private Coordinate source;
	private Coordinate destination;
	private Set<Taxi> taxi;
	
	public Coordinate getSource() {
		return this.source;
		
	}
	
	public Coordinate getDestination() {
		return this.destination;
	}
	
	public Request (String type, Coordinate source, Coordinate destination) {
		
	}
	
	public void addTaxi(Taxi taxi) {
		
	}
	
	public Set<Taxi> getTaxiSet(){
		return this.taxi;
	}

}
