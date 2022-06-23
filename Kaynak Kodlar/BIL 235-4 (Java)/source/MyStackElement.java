
public class MyStackElement {
	private int distance;
	private String path;
	private Node current;
	public MyStackElement(String path, int distance,Node current) {
		this.path=path;
		this.distance=distance;
		this.current=current;
	}
	public Node getCurrent() {
		return current;
	}
	public void setCurrent(Node current) {
		this.current = current;
	}

	public int getDistance() {
		return distance;
	}
	public void setDistance(int distance) {
		this.distance = distance;
	}
	public String getPath() {
		return path;
	}
	public void setPath(String path) {
		this.path = path;
	}

}
