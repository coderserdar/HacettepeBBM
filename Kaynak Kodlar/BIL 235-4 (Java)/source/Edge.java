import java.util.*;

public class Edge {
	
	public String EdgeName ;
	public Node SourceNode ;
	public Node DestinationNode ;
	public int EdgeDistance ;
	
	public Edge(Node sourceNode, Node destinationNode, int edgeDistance) {
		super();
		SourceNode = sourceNode;
		DestinationNode = destinationNode;
		EdgeDistance = edgeDistance;
	}
	
	public Node getSourceNode() {
		return SourceNode;
	}
	public void setSourceNode(Node sourceNode) {
		SourceNode = sourceNode;
	}
	public Node getDestinationNode() {
		return DestinationNode;
	}
	public void setDestinationNode(Node destinationNode) {
		DestinationNode = destinationNode;
	}
	public int getEdgeDistance() {
		return EdgeDistance;
	}
	public void setEdgeDistance(int edgeDistance) {
		EdgeDistance = edgeDistance;
	}

}
