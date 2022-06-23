import java.util.*;

public class Path
{
	public Vector<Node> pathNodes ;
	
    public Vector<Node> getPathNodes() {
		return pathNodes;
	}

	public void setPathNodes(Vector<Node> pathNodes) {
		this.pathNodes = pathNodes;
	}

	public Path(Vector<Node> pathNodes) {
		super();
		this.pathNodes = pathNodes;
	}

}