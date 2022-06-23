import java.util.*;

public class Node implements Comparable<Node>{
	
	public char NodeName ;
	public Vector<Edge> EdgeList ;
	public Vector<Node> Nodelist ;
	public Stack<Package> PackageStack ;
	public Node previous ;
	public int NodeLength = Integer.MAX_VALUE;
	
	public Node(char nodeName, Vector<Edge> edgeList, Vector<Node> nodelist,
			Stack<Package> packageStack, int nodeLength, int nodeNumber) {
		super();
		NodeName = nodeName;
		EdgeList = edgeList;
		Nodelist = nodelist;
		PackageStack = packageStack;
		NodeLength = nodeLength;
		NodeNumber = nodeNumber;
	}
	
	public char getNodeName() {
		return NodeName;
	}
	public void setNodeName(char nodeName) {
		NodeName = nodeName;
	}
	public Vector<Edge> getEdgeList() {
		return EdgeList;
	}
	public void setEdgeList(Vector<Edge> edgeList) {
		EdgeList = edgeList;
	}
	public Vector<Node> getNodelist() {
		return Nodelist;
	}
	public void setNodelist(Vector<Node> nodelist) {
		Nodelist = nodelist;
	}
	public Stack<Package> getPackageStack() {
		return PackageStack;
	}
	public void setPackageStack(Stack<Package> packageStack) {
		PackageStack = packageStack;
	}
	public int getNodeLength() {
		return NodeLength;
	}
	public void setNodeLength(int nodeLength) {
		NodeLength = nodeLength;
	}
	public int getNodeNumber() {
		return NodeNumber;
	}
	public void setNodeNumber(int nodeNumber) {
		NodeNumber = nodeNumber;
	}
	public int NodeNumber ;

	public int compareTo(Node arg0) {
		return Double.compare(this.NodeLength, arg0.NodeLength);
	}
	
	
	
	
}
