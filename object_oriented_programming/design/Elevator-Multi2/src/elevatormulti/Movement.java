package elevatormulti;

public interface Movement {
	abstract boolean moveUp(int dest, double time); 
	abstract boolean moveDown(int dest, double time);
	abstract boolean doorMove();
}
