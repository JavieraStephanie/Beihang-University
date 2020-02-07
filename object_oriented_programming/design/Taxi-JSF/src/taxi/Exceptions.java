package taxi;

class InvalidRequestException extends Exception {
	private static final long serialVersionUID = 1L;
	public InvalidRequestException(String message) {
		super(message);
	}
}

class SameRequestException extends Exception {
	private static final long serialVersionUID = 1L;
	public SameRequestException(String message) {
		super(message);
	}
}

class CannotRemoveException extends Exception {
	private static final long serialVersionUID = 1L;

	public CannotRemoveException(String message) {
		super(message);
	}
}