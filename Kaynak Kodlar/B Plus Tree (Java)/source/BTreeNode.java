public class BTreeNode implements Node{
	Entry[] entries=new Entry[2*d];
	BTreeNode[] nodes= new BTreeNode[2*d+1];
}
