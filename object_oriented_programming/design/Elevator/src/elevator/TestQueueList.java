package elevator;

import elevator.Query.Direction;

public class TestQueueList {
	public static void main(String[] args) throws UnsortedException,InvalidRemoveException {
		
	QueryList ql=new QueryList(10,1);
	
	//测试不合法的remove
	try {
	System.out.println("remove from empty queue:"+ql.remove(3));
	} catch (InvalidRemoveException e) {
		System.out.println(e.getMessage());
	}
	
	ql.append(new Query(10,0.0));
	ql.append(new Query(8,1.0,Query.Direction.UP));
	ql.append(new Query(5,1.5,Query.Direction.DOWN));
	
	
	
	//测试合法的remove
	System.out.println("remove the first element from the queue:"+ql.remove(0));
	
	//测试不合法的remove
	try {
	System.out.println("remove an nonexistent element from the queue:"+ql.remove(-1));
	System.out.println("remove an exceeded element from the queue:"+ql.remove(4));
	} catch (InvalidRemoveException e) {
		System.out.println(e.getMessage());
	}
	
	try {
		System.out.println("go up when elevator is on 10th floor:"+ql.append(new Query(10,0.0,Query.Direction.UP)));
	} catch (UnsortedException e) {
		System.out.println(e.getMessage());
	}
	
	System.out.println("process queue:"+ql.append(new Query(5,1.5, Query.Direction.DOWN)));
 }
}
