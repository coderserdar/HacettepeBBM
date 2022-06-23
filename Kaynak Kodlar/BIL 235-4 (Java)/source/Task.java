import java.util.*;

public class Task {
	
	public String Source ;
	public String Destination ;
	public Vector<Node> shortestPath ;
	public int PackageNumber ;
	
	public Task(String source, String destination, Vector<Node> shortestPath,
			int packageNumber) {
		super();
		Source = source;
		Destination = destination;
		this.shortestPath = shortestPath;
		PackageNumber = packageNumber;
	}
	
	public String getSource() {
		return Source;
	}
	public void setSource(String source) {
		Source = source;
	}
	public String getDestination() {
		return Destination;
	}
	public void setDestination(String destination) {
		Destination = destination;
	}
	public Vector<Node> getShortestPath() {
		return shortestPath;
	}
	public void setShortestPath(Vector<Node> shortestPath) {
		this.shortestPath = shortestPath;
	}
	public int getPackageNumber() {
		return PackageNumber;
	}
	public void setPackageNumber(int packageNumber) {
		PackageNumber = packageNumber;
	}
	
	
	
}
