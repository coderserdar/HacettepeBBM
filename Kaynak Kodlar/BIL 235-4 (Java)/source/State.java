import java.util.*;

public class State {
	
	public Node StateNode ;
	public Edge StateEdge ;
	public int StateDistance ;
	
	public State(Edge stateEdge, int stateDistance) {		
		StateEdge = stateEdge;
		StateDistance = stateDistance;
	}
	
	public State(Node stateNode, int stateDistance) {		
		StateNode = stateNode;
		StateDistance = stateDistance;
	}
	
	public Node getStateNode() {
		return StateNode;
	}
	public void setStateNode(Node stateNode) {
		StateNode = stateNode;
	}
	public Edge getStateEdge() {
		return StateEdge;
	}
	public void setStateEdge(Edge stateEdge) {
		StateEdge = stateEdge;
	}
	public int getStateDistance() {
		return StateDistance;
	}
	public void setStateDistance(int stateDistance) {
		StateDistance = stateDistance;
	}

}
