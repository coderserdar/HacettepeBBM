public class BPlusTree {
	public static final int d=2;
	Entry newentry=new Entry();
	int root=0;/*this variable is used to determine is there necessary a new root node*/
	public Node deleteOrList(Node rootNode,double id) {/*this function deletes or list group of entries*/
		Main.numberOfPassedNode++;
		int size=findNodeKeySize(rootNode);/*find size of current node*/
		int index=findNewIndex(rootNode,id,size);/*find index of id at current node*/
		if(rootNode.getClass().getName()=="BPlusTreeLeafNode")
		{/*if it is a leaf node*/
			deleteorListAtRoot((BPlusTreeLeafNode)rootNode,index,id);
			return rootNode;
		}
		else if(((BPlusTreeNonLeafNode)rootNode).nodes[0].getClass().getName()=="BPlusTreeLeafNode")
		{/*this is one upper level of leaf*/
			if(index<0)
				index=-(index+1);
			Main.numberOfPassedNode++;
			deleteFromLeaf(((BPlusTreeNonLeafNode)rootNode),index,id);
		}
		else
		{/*this level is far to leaf least two level*/
			if(index<0)
				index=-(index+1);
			root++;
			deleteOrList(((BPlusTreeNonLeafNode)rootNode).nodes[index], id);	
			if(newentry==null)
			{
				if(root!=0)
					root--;
				return rootNode;
			}
			index=findNewIndex(rootNode, newentry.key, size);
			deleteFromNode((BPlusTreeNonLeafNode)rootNode, index, newentry.key);
		}
		root--;
		if(root==-1&&rootNode.getClass().getName()=="BPlusTreeNonLeafNode")
		{/*is it necessary modification on root*/
			size=findNodeKeySize(rootNode);
			if(((BPlusTreeNonLeafNode)rootNode).nodes[0]!=null&&((BPlusTreeNonLeafNode)rootNode).nodes[1]==null)
				rootNode=((BPlusTreeNonLeafNode)rootNode).nodes[0];
			else if(newentry!=null&&((BPlusTreeNonLeafNode)rootNode).nodes[size]==null&&size>0)
				deleteEntry(rootNode, -(findNewIndex((rootNode), newentry.key,size)+1));
			root=0;
		}
		return rootNode;
		
	}
	private void deleteorListAtRoot(BPlusTreeLeafNode rootNode,int index,Double id)
	{
		if(Main.operation==1)
		{/*BW delete*/
			if (index<0)/*value is found convert it's index to positive*/
				index=-(index+1);
			while(((BPlusTreeLeafNode)rootNode).entries[index]!=null&&((BPlusTreeLeafNode)rootNode).entries[index].key<=Main.dValue)
			{/*delete entries*/
				Main.deletedIndexes[Main.deletedIndexArrayIndexes]=rootNode.entries[index].pointer_to_file;
				Main.deletedIndexArrayIndexes++;
				deleteEntry(rootNode, index);
				Main.deletedCounter++;
			}
		}	
		else if(Main.operation==2)
		{/*EQ delete*/
			/*it is a leaf node this node and  value founded*/
			if (index<0)/*value is found convert it's index to positive*/
			{	
				index=-(index+1);
				Main.deletedIndexes[Main.deletedIndexArrayIndexes]=rootNode.entries[index].pointer_to_file;
				Main.deletedIndexArrayIndexes++;
				deleteEntry(rootNode, index);
				Main.deletedCounter++;
			}
		}
		else if(Main.operation==3)
		{/*GE main.dvalue is upper limit*/
			if (index<0)/*value is found convert it's index to positive*/
				index=-(index+1);
			while(((BPlusTreeLeafNode)rootNode).entries[index]!=null)
			{/*delete entries*/
				Main.deletedIndexes[Main.deletedIndexArrayIndexes]=rootNode.entries[index].pointer_to_file;
				Main.deletedIndexArrayIndexes++;
				deleteEntry(rootNode, index);
				Main.deletedCounter++;
			}
			Main.dValue=null;
		}
		else if(Main.operation==4)
		{/*GT main.dvalue is upper limit*/
			if (index<0){/*value is found convert it's index to positive*/
				index=-(index+1);
				index++;
			}
			while(index<2*d&&((BPlusTreeLeafNode)rootNode).entries[index]!=null)
			{/*delete entries*/
				Main.deletedIndexes[Main.deletedIndexArrayIndexes]=rootNode.entries[index].pointer_to_file;
				Main.deletedIndexArrayIndexes++;
				deleteEntry(rootNode, index);
				Main.deletedCounter++;
			}
			Main.dValue=null;
		}
		else if(Main.operation==5)
		{/*LE */
			index=0;
			while(((BPlusTreeLeafNode)rootNode).entries[index]!=null&&((BPlusTreeLeafNode)rootNode).entries[index].key<=id)
			{/*delete entries*/
				Main.deletedIndexes[Main.deletedIndexArrayIndexes]=rootNode.entries[index].pointer_to_file;
				Main.deletedIndexArrayIndexes++;
				deleteEntry(rootNode, index);
				Main.deletedCounter++;
			}
			Main.dValue=null;
		}
		else if(Main.operation==6)
		{/*LT */
			index=0;
			while(((BPlusTreeLeafNode)rootNode).entries[index]!=null&&((BPlusTreeLeafNode)rootNode).entries[index].key<id)
			{/*delete entries*/
				Main.deletedIndexes[Main.deletedIndexArrayIndexes]=rootNode.entries[index].pointer_to_file;
				Main.deletedIndexArrayIndexes++;
				deleteEntry(rootNode, index);
				Main.deletedCounter++;
			}
			Main.dValue=null;
		}
		else if(Main.operation==-1)
		{/*BW list*/
			if (index<0)/*value is found convert it's index to positive*/
				index=-(index+1);
			while(index<2*d&&((BPlusTreeLeafNode)rootNode).entries[index]!=null&&((BPlusTreeLeafNode)rootNode).entries[index].key<=Main.dValue)
			{/*list entries*/
				Main.arr.add(((BPlusTreeLeafNode)rootNode).entries[index].pointer_to_file);
				index++;
			}
		}	
		else if(Main.operation==-2)
		{/*EQ list*/
			if(index<0)
			{/*it is a leaf node this node and  value founded*/
				index=-(index+1);
				Main.arr.add(((BPlusTreeLeafNode)rootNode).entries[index].pointer_to_file);
			}
		}
		else if(Main.operation==-3)
		{/*GE main.dvalue is upper limit*/
			if (index<0)/*value is found convert it's index to positive*/
				index=-(index+1);
			while(index<2*d&&((BPlusTreeLeafNode)rootNode).entries[index]!=null)
			{/*list entries*/
				Main.arr.add(((BPlusTreeLeafNode)rootNode).entries[index].pointer_to_file);
				index++;
			}
		}
		else if(Main.operation==-4)
		{/*GT main.dvalue is upper limit*/
			if (index<0){/*value is found convert it's index to positive*/
				index=-(index+1);
				index++;
			}
			while(index<2*d&&((BPlusTreeLeafNode)rootNode).entries[index]!=null)
			{/*delete entries*/
				Main.arr.add(((BPlusTreeLeafNode)rootNode).entries[index].pointer_to_file);
				index++;
			}
		}
		else if(Main.operation==-5)
		{/*LE */
			index=0;
			while(index<2*d&&((BPlusTreeLeafNode)rootNode).entries[index]!=null&&((BPlusTreeLeafNode)rootNode).entries[index].key<=id)
			{/*list entries*/
				Main.arr.add(((BPlusTreeLeafNode)rootNode).entries[index].pointer_to_file);
				index++;
			}
		}
		else
		{/*LT */
			index=0;
			while(index<2*d&&((BPlusTreeLeafNode)rootNode).entries[index]!=null&&((BPlusTreeLeafNode)rootNode).entries[index].key<id)
			{/*list entries*/
				Main.arr.add(((BPlusTreeLeafNode)rootNode).entries[index].pointer_to_file);
				index++;
			}
		}
	}
	private void deleteEntry(Node pointer,int index)
	{/*this procedure deletes one entry from affected node*/
		int i=index;
		if(pointer.getClass().getName()=="BPlusTreeNonLeafNode"){
			while(i<2*d-1&& ((BPlusTreeNonLeafNode)pointer).nodes[i]!=null)
			{/*split all values on deleted entry*/
				((BPlusTreeNonLeafNode)pointer).keys[i]=((BPlusTreeNonLeafNode)pointer).keys[i+1];
				i++;
			}
			((BPlusTreeNonLeafNode)pointer).keys[2*d-1]=null;/*the last entry absulately will be null*/
		}
		else
		{
			while(i<2*d-1&& ((BPlusTreeLeafNode)pointer).entries[i]!=null)
			{/*split all values on deleted entry*/
				((BPlusTreeLeafNode)pointer).entries[i]=((BPlusTreeLeafNode)pointer).entries[i+1];
				i++;
			}
			((BPlusTreeLeafNode)pointer).entries[2*d-1]=null;/*the last entry absulately will be null*/

		}
	}
	private void deleteNodes(BPlusTreeNonLeafNode pointer, int index) 
	{/*this procedure deletes one node pointer from affected node*/
		int i=index;
		while(i<2*d && pointer.nodes[i]!=null)
		{/*delete it and split all others(which are at right) 1 left*/
			pointer.nodes[i]=pointer.nodes[i+1];
			i++;
		}
		pointer.nodes[2*d]=null;/*last entry has to be null*/
	}
	private void makeReadyToAdd(int index, Node pointer) 
	{/*this function prepares pointer to add a new entry*/
		int size=findNodeKeySize(pointer);
		int i=size;
		if(pointer.getClass().getName()=="BPlusTreeLeafNode")
		{/*this is a BPlusTreeLeafNode element it has entries which will be reorganized here*/
			
			while(i>index){
				((BPlusTreeLeafNode)pointer).entries[i]=((BPlusTreeLeafNode)pointer).entries[i-1];
				i--;
			}
		}
		else
		{/*this is a BPlusTreeNonLeafNode it has keys which will be reorganized here*/
			while(i>index){
				((BPlusTreeNonLeafNode)pointer).keys[i]=((BPlusTreeNonLeafNode)pointer).keys[i-1];
				i--;
			}
			i=size+1;
			while(i>index){
				((BPlusTreeNonLeafNode)pointer).nodes[i]=((BPlusTreeNonLeafNode)pointer).nodes[i-1];
				i--;
			}
		}
		return;
	}
	public int findNewIndex(Node pointer, double value,int size) 
	{/*it finds an index to "value" in a node(between 0 and 2d)*/
		int i=0;
		if(pointer.getClass().getName()=="BPlusTreeNonLeafNode"){
			while(i<2*d)
			{/*compare all key values 0 to 2d*/
				if(size <=i||((BPlusTreeNonLeafNode)pointer).keys[i]>value)
					return i;
				if(size <=i||((BPlusTreeNonLeafNode)pointer).keys[i]==value)
					return -i-1;
					i++;
			}
		}
		else{
			while(i<2*d)
			{/*compare all entry key values 0 to 2d*/
				if(size <=i||((BPlusTreeLeafNode)pointer).entries[i].key>value)
					return i;
				if(size <=i||((BPlusTreeLeafNode)pointer).entries[i].key==value)
					return -i-1;
				i++;
			}			
		}
		return i;
	}
	public int findNodeKeySize(Node pointer)
	{/*it finds number of keys(or entry) in a node*/
		int i;
		int size;/*size of array it may include empty spaces*/
		if(pointer.getClass().getName()=="BPlusTreeNonLeafNode")
		{/*if this node is a BPlusTreeNonLeafNode*/
			i=2*d-1;
			size=2*d;
			while(i>-1)
			{/*find size of node with osing node pointers it is a bit of different from other*/
				if(((BPlusTreeNonLeafNode)pointer).keys[i]==null)
					size--;
					i--;
			}
			return size;
		}
		else
		{/*if this node is a BPlusTreeLeafNode*/
			i=2*d-1;
			size=2*d;
			while(i>-1)
			{/*find size of entrie with looking pointers with starting last element of entry list*/
				if(((BPlusTreeLeafNode)pointer).entries[i]==null)
					size--;
					i--;
			}
			return size;
		}
	}
	public Node insert(Node rootPointer,Entry entry)
	{/*this function inserts a vlue to b+tree*/		
		Main.numberOfPassedNode++;
		Node newChild=null;/*this is a node which holds new sibling node*/
		int i,index = 0;
		int size=findNodeKeySize(rootPointer);
		if(rootPointer.getClass().getName()=="BPlusTreeLeafNode")
		{/*find a avaliable index to an entry at node*/
			index=findNewIndex(((BPlusTreeLeafNode)rootPointer), entry.key,size);
			if(index<0){
				Main.control=0;/*0 value added*/
				return newChild;
			}
			Main.control=1;
			if( size < 2*d)
			{/*there is sufficient space for adding entry to node*/
				makeReadyToAdd(index,rootPointer);

				((BPlusTreeLeafNode)rootPointer).entries[index]=entry;	
				newentry=null;/*there is not a new entry*/
				newChild=rootPointer;/*there is not a new child*/
			} 
			else
			{/*split this node to two sibling nodes*/
				Main.numberOfPassedNode++;
				newChild=new BPlusTreeLeafNode();
				Entry tempentry=new Entry();
				if(index==2*d)
				{/* "tempentry" will be equal to "entry" which is bigger from all others*/
					tempentry=entry;
				}	
				else
				{/*keep the biggest value of node at tempentry and insert element to node"*/
					tempentry=((BPlusTreeLeafNode)rootPointer).entries[2*d-1];/*keep biggest value in "tempEntry"*/
					((BPlusTreeLeafNode)rootPointer).entries[2*d-1]=null;/*remove keeped value */
					makeReadyToAdd(index, rootPointer);
					((BPlusTreeLeafNode)rootPointer).entries[index]=entry;/*add "entry" to node*/
				}
				int indexOfLastKey=2*d-(d+2);/*new node's last entry will be at this index of new node*/
				i=2*d-1;
				while(i>d)
				{/*move entries d+1 to 2d to new node*/
					
					((BPlusTreeLeafNode)newChild).entries[indexOfLastKey]=((BPlusTreeLeafNode)rootPointer).entries[i];
					((BPlusTreeLeafNode)rootPointer).entries[i]=null;/*delete moved entries from node*/
					i--;
					indexOfLastKey--;
				}
				
				((BPlusTreeLeafNode)newChild).entries[(2*d-(d+1))]=tempentry;/*add biggest value to node*/
				((BPlusTreeLeafNode)newChild).node=((BPlusTreeLeafNode)rootPointer).node;/*tempnode's next element will be old node's next element*/
				((BPlusTreeLeafNode)rootPointer).node=newChild;/*old nodes next element will be tempnode*/
				newentry=((BPlusTreeLeafNode)rootPointer).entries[d];/*find entry which will inserted to up level*/
			}			
		}
		else
		{

			index=findNewIndex(((BPlusTreeNonLeafNode)rootPointer), entry.key,size);/*find a index value to access a sub-tree*/
			if(index<0){
				return newChild;
			}
			root++;/*level of rootpointer came close to leafs*/
			newChild=insert(((BPlusTreeNonLeafNode)rootPointer).nodes[index],entry);
			if (newentry==null){/*there is not a new entry to add this node*/
				if(root!=0)
					root--;/*level of rootpointer came close to root of tree*/
				return rootPointer;
			}
			size=findNodeKeySize(rootPointer);
			index=findNewIndex(((BPlusTreeNonLeafNode)rootPointer), newentry.key,size);/*find a new index value to add "newentry" this node*/
			if(findNodeKeySize(rootPointer) < 2*d)
			{/*there is sufficient space for adding key to node*/
				makeReadyToAdd(index, rootPointer);
				((BPlusTreeNonLeafNode)rootPointer).keys[index]=newentry.key;/*add key to node*/
				((BPlusTreeNonLeafNode)rootPointer).nodes[index+1]=newChild;/*add new node pointer to node*/
				newentry=null;/*there is no more entry which will be added to node*/
				newChild=rootPointer;/*there is not any new node pointer*/
			}
			else
			{/*split node to two sibling nodes*/
				Main.numberOfPassedNode++;
				Node tempnode=new BPlusTreeNonLeafNode();/*a temporarily node which keeps a node*/
				double tempkey;/*a temporarily node which keeps a key the biggest one*/
				if(index==2*d)
				{/*"newentry" will move to new node it's value is bigger from all others*/
					tempkey= newentry.key;/*"newkey" is the biggest*/
					tempnode= newChild;/*new child pointer is "newkey"s next pointer */
				}	
				else
				{
					tempkey=((BPlusTreeNonLeafNode)rootPointer).keys[2*d-1];/*keep biggest value in "tempEntry"*/
					tempnode =((BPlusTreeNonLeafNode)rootPointer).nodes[2*d];/*keep node pointer which is after "tempentry"*/
					
					((BPlusTreeNonLeafNode)rootPointer).keys[2*d-1]= null;/*delete keeped key*/
					((BPlusTreeNonLeafNode)rootPointer).nodes[2*d]= null;/*delete keeped key*/
					
					makeReadyToAdd(index, rootPointer);/*this function preparing node array*/
					
					((BPlusTreeNonLeafNode)rootPointer).keys[index]=newentry.key;/* add newentry key to node*/
					((BPlusTreeNonLeafNode)rootPointer).nodes[index+1]=newChild;/*add newentry's node pointer to node*/
				}
				newChild=new BPlusTreeNonLeafNode();/*new node*/
				int indexOfLastKey=2*d-(d+2);/*new node's last key will be at this index of new node*/
				i=2*d-1;
				while(i>d)
				{/*move entries d+1 to 2d to new node*/
					
					((BPlusTreeNonLeafNode)newChild).keys[indexOfLastKey]=((BPlusTreeNonLeafNode)rootPointer).keys[i];
					((BPlusTreeNonLeafNode)rootPointer).keys[i]=null;/*remove key*/
					
					((BPlusTreeNonLeafNode)newChild).nodes[indexOfLastKey]=((BPlusTreeNonLeafNode)rootPointer).nodes[i];
					((BPlusTreeNonLeafNode)rootPointer).nodes[i]=null;
					i--;
					indexOfLastKey--;
				}
				((BPlusTreeNonLeafNode)newChild).nodes[2*d-(d+1)]=((BPlusTreeNonLeafNode)rootPointer).nodes[2*d];/*add last keys left node pointer*/
				((BPlusTreeNonLeafNode)rootPointer).nodes[2*d]=null;
				((BPlusTreeNonLeafNode)newChild).keys[2*d-(d+1)]=tempkey;/*add last entry's key number*/
				((BPlusTreeNonLeafNode)newChild).nodes[2*d-(d)]=tempnode;/*add last key's last right node pointer*/
				newentry =new Entry();
				newentry.key=((BPlusTreeNonLeafNode)rootPointer).keys[d];
				((BPlusTreeNonLeafNode)rootPointer).keys[d]=null;/*remove key*/
			}
		}
		root--;
		if(root==-1)
		{
			if(newChild!=rootPointer)
			{
				Main.numberOfPassedNode++;
				BPlusTreeNonLeafNode newRoot=new BPlusTreeNonLeafNode();/*create a new root to tree*/
				newRoot.keys[0]=newentry.key;/*insert it's key value*/
				newRoot.nodes[0]=rootPointer;/*insert it's left node pointer*/
				newRoot.nodes[1]=newChild;/*insert it's right pointer*/
				newChild=newRoot;/*return root of tree*/
			}
			root=0;
		}
		return newChild;
	}
	private void deleteFromNode(BPlusTreeNonLeafNode rootPointer,int index,double id)
	{/*this function deletes a subtree's node and it makes redistribution or sibling if it is necessary*/
		int leftSiblingSize=0;/*left sibling of current node*/
		int rightSiblingSize=0;/*right sibling of current node*/
		if(index>0&&Main.operation>0){/*is there exist a left sibling?*/
			leftSiblingSize=findNodeKeySize(((BPlusTreeNonLeafNode)rootPointer.nodes[index-1]));
			Main.numberOfPassedNode++; 
		}
		if(index<findNodeKeySize(((BPlusTreeNonLeafNode)rootPointer))&&Main.operation>0){/*is there exist a right siblings?*/
			rightSiblingSize=findNodeKeySize(((BPlusTreeNonLeafNode)rootPointer.nodes[index+1]));
			Main.numberOfPassedNode++;
		}
		int currentSiblingSize=findNodeKeySize(((BPlusTreeNonLeafNode)rootPointer.nodes[index]));/*find current siblings size*/
		int i=findNewIndex((BPlusTreeNonLeafNode)rootPointer.nodes[index],id,currentSiblingSize);/*find id's index*/
		if(i<0)
			i=-(i+1);
		else return;
		deleteEntry((BPlusTreeNonLeafNode)rootPointer.nodes[index],i);/*delete related entry at node*/
		currentSiblingSize--;/*an entry deleted from current node*/
		if(currentSiblingSize>=d)/*there is not a sub overflow*/
			return;
		else if(leftSiblingSize>d)
		{/*try to redistribution with left sibling*/
			makeReadyToAdd(0, (BPlusTreeNonLeafNode)rootPointer.nodes[index]);/*current node will take left parents entry*/
			((BPlusTreeNonLeafNode)rootPointer.nodes[index]).keys[0]=rootPointer.keys[index-1];
			rootPointer.keys[index-1]=((BPlusTreeNonLeafNode)rootPointer.nodes[index-1]).keys[leftSiblingSize-1];/*left parent node will take left sibling node's biggest value*/
			((BPlusTreeNonLeafNode)rootPointer.nodes[index-1]).keys[leftSiblingSize-1]=null;/*left sibling node's biggest value will be null*/
			
			((BPlusTreeNonLeafNode)rootPointer.nodes[index]).nodes[0]=((BPlusTreeNonLeafNode)rootPointer.nodes[index-1]).nodes[leftSiblingSize];/*update nodes*/
			deleteNodes(((BPlusTreeNonLeafNode)rootPointer.nodes[index-1]),leftSiblingSize);
			newentry=null;
		}
		else if(rightSiblingSize>d)
		{/*try to redistribution with right sibling*/
			((BPlusTreeNonLeafNode)rootPointer.nodes[index]).keys[currentSiblingSize]=rootPointer.keys[index];/*right parent will be current node's last entry*/
			rootPointer.keys[index]=((BPlusTreeNonLeafNode)rootPointer.nodes[index+1]).keys[0];/*right parent will take rightSiblings smallest entry*/
			deleteEntry(((BPlusTreeNonLeafNode)rootPointer.nodes[index+1]),0);/*delete rightsiblings smallest entry*/
			
			((BPlusTreeNonLeafNode)rootPointer.nodes[index]).nodes[currentSiblingSize+1]=((BPlusTreeNonLeafNode)rootPointer.nodes[index+1]).nodes[0];/*update nodes*/
			deleteNodes(((BPlusTreeNonLeafNode)rootPointer.nodes[index+1]),0);
			newentry=null;
		}
		else if(leftSiblingSize>0)
		{/*try to merging node with left sibling*/
			newentry=new Entry();
			newentry.key=rootPointer.keys[index-1];
			((BPlusTreeNonLeafNode)rootPointer.nodes[index-1]).keys[leftSiblingSize]=rootPointer.keys[index-1];/*add left parent to left sibling */
			leftSiblingSize++;
			i=0;
			while(leftSiblingSize<2*d)
			{
				((BPlusTreeNonLeafNode)rootPointer.nodes[index-1]).keys[leftSiblingSize]=((BPlusTreeNonLeafNode)rootPointer.nodes[index]).keys[i];/*add current node entries to left sibling*/
				((BPlusTreeNonLeafNode)rootPointer.nodes[index]).keys[i]=null;
		
				((BPlusTreeNonLeafNode)rootPointer.nodes[index-1]).nodes[leftSiblingSize]=((BPlusTreeNonLeafNode)rootPointer.nodes[index]).nodes[i];
				((BPlusTreeNonLeafNode)rootPointer.nodes[index]).nodes[i]=null;
				currentSiblingSize--;
				
				leftSiblingSize++;
				i++;
			}
			((BPlusTreeNonLeafNode)rootPointer.nodes[index-1]).nodes[leftSiblingSize]=((BPlusTreeNonLeafNode)rootPointer.nodes[index]).nodes[i];
			((BPlusTreeNonLeafNode)rootPointer.nodes[index]).nodes[i]=null;
			while(index<findNodeKeySize(rootPointer)&&rootPointer.nodes[index+1]!=null)
			{/*update nodes*/
				rootPointer.nodes[index]=rootPointer.nodes[index+1];	
				index++;
			}
			rootPointer.nodes[index]=null;
		}
		else
		{/*try  to merging node with right sibling*/	
			newentry=new Entry();
			newentry.key=rootPointer.keys[index];
			((BPlusTreeNonLeafNode)rootPointer.nodes[index]).keys[currentSiblingSize]=rootPointer.keys[index];/*add the right parent to current*/
			currentSiblingSize++;
			i=0;
	
			while(currentSiblingSize<2*d)
			{
				((BPlusTreeNonLeafNode)rootPointer.nodes[index]).keys[currentSiblingSize]=((BPlusTreeNonLeafNode)rootPointer.nodes[index+1]).keys[i];/*add right sibling entries to current node*/
				((BPlusTreeNonLeafNode)rootPointer.nodes[index+1]).keys[i]=null;
				
				((BPlusTreeNonLeafNode)rootPointer.nodes[index]).nodes[currentSiblingSize]=((BPlusTreeNonLeafNode)rootPointer.nodes[index+1]).nodes[i];
				((BPlusTreeNonLeafNode)rootPointer.nodes[index+1]).nodes[i]=null;
				
				currentSiblingSize++;
				i++;
			}
			((BPlusTreeNonLeafNode)rootPointer.nodes[index]).nodes[currentSiblingSize]=((BPlusTreeNonLeafNode)rootPointer.nodes[index+1]).nodes[i];
			((BPlusTreeNonLeafNode)rootPointer.nodes[index+1]).nodes[i]=null;

			index++;
			while(index<findNodeKeySize(rootPointer)&&rootPointer.nodes[index+1]!=null)
			{/*update nodes*/
				rootPointer.nodes[index]=rootPointer.nodes[index+1];	
				index++;
			}
			rootPointer.nodes[index]=null;
		}
	}
	private void deleteFromLeaf(BPlusTreeNonLeafNode rootPointer,int index,double id)
	{/*this function deletes a subtree's node and it makes redistribution or sibling if it is necessary*/
		int leftSiblingSize=0;/*left sibling of current node*/
		int rightSiblingSize=0;/*right sibling of current node*/
		if(index>0&&Main.operation>0){/*is there exist a left sibling?*/
			leftSiblingSize=findNodeKeySize(rootPointer.nodes[index-1]);
			Main.numberOfPassedNode++;
		}
		if(index<findNodeKeySize(rootPointer)&&Main.operation>0){/*is there exist a right siblings?*/
			rightSiblingSize=findNodeKeySize(rootPointer.nodes[index+1]);
			Main.numberOfPassedNode++;
		}
		int currentSiblingSize=findNodeKeySize((rootPointer.nodes[index]));/*find current siblings size*/
		int i=findNewIndex(rootPointer.nodes[index],id,currentSiblingSize);/*find id's index*/
		newentry=null;
		/*control operations*/
		if(Main.operation==1||Main.operation==3||Main.operation==4)
		{/*BW ,GE or GT delete*/
			int control=0;
			if(i<0){
				i=-(i+1);
				control=1;
			}
			else if(i==currentSiblingSize){
				Main.dValue=null;
				return;/*this is greater from all tree nodes*/
			}
			if(Main.operation==1&&((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[i].key>Main.dValue)
			{/*control top restrict*/
				Main.dValue=((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[i].key;
				return;
			}
			if(i+1<2*d&&((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[i+1]!=null)
			{/*find next deleting value from same node*/
				Main.dValue=((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[i+1].key;
			}
			else if(((BPlusTreeLeafNode)rootPointer.nodes[index]).node!=null)
			{/*find next deleting value from next node*/
				Main.dValue=((BPlusTreeLeafNode)(((BPlusTreeLeafNode)rootPointer.nodes[index]).node)).entries[0].key;
			}
			else
			{/*there is no bigger value*/
				Main.dValue=null;
			}
			if((Main.operation!=4&&control==1)||(control==0)){
				Main.deletedIndexes[Main.deletedIndexArrayIndexes]=((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[i].pointer_to_file;
				Main.deletedIndexArrayIndexes++;
				deleteEntry(rootPointer.nodes[index],i);/*delete related entry at node*/
				currentSiblingSize--;/*an entry deleted from current node*/
				Main.deletedCounter++;
			}
			else if(Main.operation==4){ 
				Main.operation=3;/*it missed current value because it must star to delete next*/
				return;
			}
			else{
				return;
			}
		}
		else if(Main.operation==2)
		{/*EQ delete*/
			if(i<0)
				i=-(i+1);
			else {/*value is not present*/
				return;
			}
			Main.deletedIndexes[Main.deletedIndexArrayIndexes]=((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[i].pointer_to_file;
			Main.deletedIndexArrayIndexes++;
			deleteEntry(rootPointer.nodes[index],i);/*delete related entry at node*/
			Main.deletedCounter++;
			currentSiblingSize--;/*an entry deleted from current node*/
		}
		else if(Main.operation>=5)
		{/*LE or LG delete*/
			if(i<0)
				i=-(i+1);
			if(i+1<2*d&&((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[i+1]!=null)
			{/*find next deleted value at same node*/
				Main.dValue=((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[i+1].key;
			}
			else if(((BPlusTreeLeafNode)rootPointer.nodes[index]).node!=null)
			{/*find next deleted value from next node*/
				Main.dValue=((BPlusTreeLeafNode)(((BPlusTreeLeafNode)rootPointer.nodes[index]).node)).entries[0].key;
			}
			else
			{/*there is no more value to delete*/
				Main.dValue=null;
			}
			Main.deletedIndexes[Main.deletedIndexArrayIndexes]=((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[i].pointer_to_file;
			Main.deletedIndexArrayIndexes++;
			deleteEntry(rootPointer.nodes[index],i);/*delete related entry at node*/
			Main.deletedCounter++;
			currentSiblingSize--;/*an entry deleted from current node*/
		}
		else if(Main.operation==-1)
		{/*BW list*/
			if(i<0)
				i=-(i+1);
			else if(i==currentSiblingSize)
			{/*there is no more value to list*/
				Main.dValue=null;
				return;/*this is greater from all tree nodes*/
			}
			listBetwen((BPlusTreeLeafNode) rootPointer.nodes[index], i);
			return;
		}
		else if(Main.operation==-2)
		{/*EQ list*/
			if(i<0)
				i=-(i+1);
			else 
			{/*there is not any value to list*/
				return;
			}
			i=((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[i].pointer_to_file;
			Main.arr.add(i);/*list data' all values at main*/
			return;
		}
		else if(Main.operation==-3||Main.operation==-4)
		{/*GE or GT list*/
			int control=0;/*to understand sub value is exist or not*/
			if(i<0){
				i=-(i+1);
				control=1;/*subvalue exist*/
			}
			else if(i==currentSiblingSize)
			{/*there is not any value to list*/
				Main.dValue=null;
				return;
			}
			listGreater(((BPlusTreeLeafNode) rootPointer.nodes[index]),i,control);
			return;
		}
		
		if(currentSiblingSize>=d)/*there is not a sub overflow*/
		{/*update index of node*/
			if(index!=2*d&&rootPointer.keys[index]!=null&&i==currentSiblingSize)
				rootPointer.keys[index]=((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[currentSiblingSize-1].key;
			return;
		}
		else if(leftSiblingSize>d)
		{/*try to redistribution with left sibling*/
			makeReadyToAdd(0, (BPlusTreeLeafNode)rootPointer.nodes[index]);/*current node will take left parents entry*/
			((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[0]=((BPlusTreeLeafNode)rootPointer.nodes[index-1]).entries[leftSiblingSize-1];/*current sibling node will take left sibling node's biggest value*/
			rootPointer.keys[index-1]=((BPlusTreeLeafNode)rootPointer.nodes[index-1]).entries[leftSiblingSize-2].key;/*left parent node will take left sibling node's 2. biggest value*/
			((BPlusTreeLeafNode)rootPointer.nodes[index-1]).entries[leftSiblingSize-1]=null;/*left sibling node's biggest value will be null*/
		}
		else if(rightSiblingSize>d)
		{/*try to redistribution with right sibling*/
			((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[currentSiblingSize]=((BPlusTreeLeafNode)rootPointer.nodes[index+1]).entries[0];/*current sibling's last entry will be right sibling node's first entry*/
			rootPointer.keys[index]=((BPlusTreeLeafNode)rootPointer.nodes[index+1]).entries[0].key;/*right parent will take rightSiblings smallest entry*/
			deleteEntry(((BPlusTreeLeafNode)rootPointer.nodes[index+1]),0);/*delete right siblings smallest entry*/
		}
		else if(leftSiblingSize>0)
		{/*try to merging node with left sibling*/
			newentry=new Entry();
			newentry.key=rootPointer.keys[index-1];
			i=0;
			while(leftSiblingSize<2*d-1)
			{
				((BPlusTreeLeafNode)rootPointer.nodes[index-1]).entries[leftSiblingSize]=((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[i];/*add current node entries to left sibling*/
				((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[i]=null;
				currentSiblingSize--;
				leftSiblingSize++;
				i++;
			}
			((BPlusTreeLeafNode)rootPointer.nodes[index-1]).node=((BPlusTreeLeafNode)rootPointer.nodes[index]).node;/*left node's node pointer will point to current siblings node's nodepointer value */
			
			while(index<findNodeKeySize(rootPointer)&&rootPointer.nodes[index+1]!=null)
			{/*update nodes*/
				rootPointer.nodes[index]=rootPointer.nodes[index+1];	
				index++;
			}
			rootPointer.nodes[index]=null;
		}
		else
		{/*try  to merging node with right sibling*/	
			newentry=new Entry();
			newentry.key=rootPointer.keys[index];
			i=0;
			while(currentSiblingSize<2*d-1)
			{
				((BPlusTreeLeafNode)rootPointer.nodes[index]).entries[currentSiblingSize]=((BPlusTreeLeafNode)rootPointer.nodes[index+1]).entries[i];/*add right sibling entries to current node*/
				((BPlusTreeLeafNode)rootPointer.nodes[index+1]).entries[i]=null;
				currentSiblingSize++;
				i++;
			}
			((BPlusTreeLeafNode)rootPointer.nodes[index]).node=((BPlusTreeLeafNode)rootPointer.nodes[index+1]).node;
			index++;
			while(index<findNodeKeySize(rootPointer)&&rootPointer.nodes[index+1]!=null)
			{/*update nodes*/
				rootPointer.nodes[index]=rootPointer.nodes[index+1];	
				index++;
			}
			rootPointer.nodes[index]=null;
		}
	}
	public void listBetwen(BPlusTreeLeafNode startingNode,int startingIndex)
	{/*this procedure (BW list) this function listing entries starting with a sub value until reaching a up value*/
		int index;
		while(startingNode.entries[startingIndex].key <= Main.dValue)
		{/*list values until reaching to upper limit*/
			index=startingNode.entries[startingIndex].pointer_to_file;
			Main.arr.add(index);/*list all fields at main*/
			if(startingNode.entries[startingIndex+1]==null)
			{/*this node has no more entry go to next node*/
				Main.numberOfPassedNode++;
				startingNode=(BPlusTreeLeafNode) startingNode.node;
				startingIndex=0;/*start to listing from next node's first entry*/
				if(startingNode.entries[startingIndex]==null)
					break;/*it is finished*/
			}
			else{
				startingIndex++;/*next element at same node*/
			}
		}
		Main.numberOfPassedNode--;/*last node didnot keeped*/
	}
	private void listGreater(BPlusTreeLeafNode pointer,int index,int control)
	{/*this procedure (GT or GE list) start from a node and list all after this*/
		if(Main.operation==-3||control==0)
		{/*GE add value to list*/
			Main.arr.add(pointer.entries[index].pointer_to_file);
		}
		while(true)
		{/*list all values */
			if(index+1<findNodeKeySize(pointer))
			{
				index++;
			}
			else if(pointer.node!=null)
			{
				index=0;
				pointer=(BPlusTreeLeafNode) pointer.node;
				Main.numberOfPassedNode++;
			}
			else break;
			Main.arr.add(pointer.entries[index].pointer_to_file);
		}
	}
	public Node findSmallest(Node pointer)
	{/*this function finds the smallest node in b plus tree recursively*/
		if(pointer.getClass().getName()!="BPlusTreeLeafNode"){/*if it is leaf node return*/
			pointer=findSmallest(((BPlusTreeNonLeafNode)pointer).nodes[0]);
			Main.numberOfPassedNode++;
		}
		return pointer;
	}
	public void travelAllNodes(BPlusTreeLeafNode bPlusSmallestPointer,char[] sTemp,int fieldNo)
	{/*this procedure travel all nodes and list wanted values*/
		int i=0,j;
		while(bPlusSmallestPointer!=null)
		{/*until reaching last node*/
			while(i<2*d&&bPlusSmallestPointer.entries[i]!=null)
			{/*until reaching last entry in a node*/	
				j=bPlusSmallestPointer.entries[i].pointer_to_file;
				if(fieldNo==1)
				{
					if(Main.operation==-1&&(compareFields(Main.dataBuffer[j].magnitude,Main.sValue)<1&&compareFields(Main.dataBuffer[j].magnitude,sTemp)>-1))
						Main.arr.add(j);/*BW list*/
					else if(Main.operation==-2&&(compareFields(Main.dataBuffer[j].magnitude,sTemp)==0))
						Main.arr.add(j);/*EQ list*/
					else if(Main.operation==-3&&(compareFields(Main.dataBuffer[j].magnitude,sTemp)>-1))
						Main.arr.add(j);/*GE list*/
					else if(Main.operation==-4&&(compareFields(Main.dataBuffer[j].magnitude,sTemp)>0))
						Main.arr.add(j);/*GT list*/
					else if(Main.operation==-5&&(compareFields(Main.dataBuffer[j].magnitude,sTemp)<1))
						Main.arr.add(j);/*LE list*/
					else if(Main.operation==-6&&compareFields(Main.dataBuffer[j].magnitude,sTemp)<0)
						Main.arr.add(j);/*LT list*/
				}

				else if(fieldNo==2)
				{
					if(Main.operation==-1&&(compareFields(Main.dataBuffer[j].latitude,Main.sValue)<1&&compareFields(Main.dataBuffer[j].latitude,sTemp)>-1))
						Main.arr.add(j);/*BW list*/
					else if(Main.operation==-2&&(compareFields(Main.dataBuffer[j].latitude,sTemp)==0))
						Main.arr.add(j);/*EQ list*/
					else if(Main.operation==-3&&(compareFields(Main.dataBuffer[j].latitude,sTemp)>-1))
						Main.arr.add(j);/*GE list*/
					else if(Main.operation==-4&&(compareFields(Main.dataBuffer[j].latitude,sTemp)>0))
						Main.arr.add(j);/*GT list*/
					else if(Main.operation==-5&&(compareFields(Main.dataBuffer[j].latitude,sTemp)<1))
						Main.arr.add(j);/*LE list*/
					else if(Main.operation==-6&&compareFields(Main.dataBuffer[j].latitude,sTemp)<0)
						Main.arr.add(j);/*LT list*/

				}
				else if(fieldNo==3)
				{
					if(Main.operation==-1&&(compareFields(Main.dataBuffer[j].longtitude,Main.sValue)<1&&compareFields(Main.dataBuffer[j].longtitude,sTemp)>-1))
						Main.arr.add(j);/*BW list*/
					else if(Main.operation==-2&&(compareFields(Main.dataBuffer[j].longtitude,sTemp)==0))
						Main.arr.add(j);/*EQ list*/
					else if(Main.operation==-3&&(compareFields(Main.dataBuffer[j].longtitude,sTemp)>-1))
						Main.arr.add(j);/*GE list*/
					else if(Main.operation==-4&&(compareFields(Main.dataBuffer[j].longtitude,sTemp)>0))
						Main.arr.add(j);/*GT list*/
					else if(Main.operation==-5&&(compareFields(Main.dataBuffer[j].longtitude,sTemp)<1))
						Main.arr.add(j);/*LE list*/
					else if(Main.operation==-6&&compareFields(Main.dataBuffer[j].longtitude,sTemp)<0)
						Main.arr.add(j);/*LT list*/
				}
				else if(fieldNo==4)
				{
					if(Main.operation==-1&&(compareFields(Main.dataBuffer[j].depth,Main.sValue)<1&&compareFields(Main.dataBuffer[j].depth,sTemp)>-1))
						Main.arr.add(j);/*BW list*/
					else if(Main.operation==-2&&(compareFields(Main.dataBuffer[j].depth,sTemp)==0))
						Main.arr.add(j);/*EQ list*/
					else if(Main.operation==-3&&(compareFields(Main.dataBuffer[j].depth,sTemp)>-1))
						Main.arr.add(j);/*GE list*/
					else if(Main.operation==-4&&(compareFields(Main.dataBuffer[j].depth,sTemp)>0))
						Main.arr.add(j);/*GT list*/
					else if(Main.operation==-5&&(compareFields(Main.dataBuffer[j].depth,sTemp)<1))
						Main.arr.add(j);/*LE list*/
					else if(Main.operation==-6&&compareFields(Main.dataBuffer[j].depth,sTemp)<0)
						Main.arr.add(j);/*LT list*/
				}
				else if(fieldNo==5)
				{
					if(Main.operation==-1&&(compareFields(Main.dataBuffer[j].date,Main.sValue)<1&&compareFields(Main.dataBuffer[j].date,sTemp)>-1))
						Main.arr.add(j);/*BW list*/
					else if(Main.operation==-2&&(compareFields(Main.dataBuffer[j].date,sTemp)==0))
						Main.arr.add(j);/*EQ list*/
					else if(Main.operation==-3&&(compareFields(Main.dataBuffer[j].date,sTemp)>-1))
						Main.arr.add(j);/*GE list*/
					else if(Main.operation==-4&&(compareFields(Main.dataBuffer[j].date,sTemp)>0))
						Main.arr.add(j);/*GT list*/
					else if(Main.operation==-5&&(compareFields(Main.dataBuffer[j].date,sTemp)<1))
						Main.arr.add(j);/*LE list*/
					else if(Main.operation==-6&&compareFields(Main.dataBuffer[j].date,sTemp)<0)
						Main.arr.add(j);/*LT list*/
				}
				else
				{
					if(Main.operation==-1&&(compareFields(Main.dataBuffer[j].time,Main.sValue)<1&&compareFields(Main.dataBuffer[j].time,sTemp)>-1))
						Main.arr.add(j);/*BW list*/
					else if(Main.operation==-2&&(compareFields(Main.dataBuffer[j].time,sTemp)==0))
						Main.arr.add(j);/*EQ list*/
					else if(Main.operation==-3&&(compareFields(Main.dataBuffer[j].time,sTemp)>-1))
						Main.arr.add(j);/*GE list*/
					else if(Main.operation==-4&&(compareFields(Main.dataBuffer[j].time,sTemp)>0))
						Main.arr.add(j);/*GT list*/
					else if(Main.operation==-5&&(compareFields(Main.dataBuffer[j].time,sTemp)<1))
						Main.arr.add(j);/*LE list*/
					else if(Main.operation==-6&&compareFields(Main.dataBuffer[j].time,sTemp)<0)
						Main.arr.add(j);/*LT list*/
				}
				i++;
			}
			i=0;
			bPlusSmallestPointer=(BPlusTreeLeafNode) bPlusSmallestPointer.node;
			Main.numberOfPassedNode++;
		}	
	}
	private int compareFields(char[] str1,char[] str2)
	{/*compares to char array returns -1 if str1<str2 return 1 str1<str2 or returns 0 str1==str2*/
		int i=0;
		while(i<str1.length)
		{
			if(str1[i]>str2[i])
				return 1;
			else if(str1[i]<str2[i])
				return -1;
			i++;
		}
		return 0;
	}
	public void listSmaller(Node bPlusRoot,BPlusTree bPlus,Double value1)
	{/*this procedure list all values smaller than value1*/
		if(bPlusRoot.getClass().getName()!="BPlusTreeLeafNode"){
			BPlusTreeLeafNode pointer=(BPlusTreeLeafNode) bPlus.findSmallest(bPlusRoot);
			int index=0;
			int control=0;
			Main.dValue=value1;/*put input value to dValue(it act as upper limit)*/
			while(pointer!=null&&control==0){
				while(pointer.entries[index]!=null){
					if(pointer.entries[index].key<Main.dValue)
						Main.arr.add(pointer.entries[index].pointer_to_file);
					else if(pointer.entries[index].key<Main.dValue&&Main.operation==-5)
						Main.arr.add(pointer.entries[index].pointer_to_file);
					else{ 
						control=1;/*to finish command execution*/
						break;
					}
					index++;
				}
				index=0;
				pointer=(BPlusTreeLeafNode) pointer.node;
			}
		}
		else
			bPlus.deleteOrList(bPlusRoot, value1);
	
	}	
	public void deleteSmaller(Double value1)
	{/*this procedure deletes all values smaller than value1*/
		if(Main.bPlusRoot.getClass().getName()!="BPlusTreeLeafNode"){
			BPlusTreeLeafNode pointer=(BPlusTreeLeafNode)findSmallest(Main.bPlusRoot);
			Main.dValue=pointer.entries[0].key;

			while(Main.dValue!=null&&Main.dValue<value1){/*call function until reaching up limits*/
					Main.bPlusRoot=deleteOrList(Main.bPlusRoot, Main.dValue);/*call function for value*/
			}
			if(Main.operation==5&&Main.dValue!=null&&Main.dValue>=value1+0.0)
				Main.bPlusRoot=deleteOrList(Main.bPlusRoot, Main.dValue);/*call function for value*/
			else if(Main.dValue==null&&Main.bPlusRoot.getClass().getName()=="BPlusTreeLeafNode")
				Main.bPlusRoot=deleteOrList(Main.bPlusRoot, value1);
		}
		else{
				Main.bPlusRoot=deleteOrList(Main.bPlusRoot, value1);/*call function for value*/
		}
	} 
	public void deleteGreater(Double value1)
	{/*this procedure deletes all values bigger than value1*/
		Main.bPlusRoot=deleteOrList(Main.bPlusRoot, value1);/*call function for value*/
		if(Main.bPlusRoot.getClass().getName()!="BPlusTreeLeafNode"){/*deletion at BPlusTreeNonLeafNode*/
			while(Main.dValue!=null)
			{/*call function until reaching up limits*/
					Main.bPlusRoot=deleteOrList(Main.bPlusRoot, Main.dValue);/*call function for value*/
			}
			if(Main.dValue==null&&Main.bPlusRoot.getClass().getName()=="BPlusTreeLeafNode")
				Main.bPlusRoot=deleteOrList(Main.bPlusRoot, value1);
		}
	}
	public void deleteBetween(Double value1,Double value2)
	{/*this procedure deletes all values between value1 and value2*/
		if(Main.bPlusRoot.getClass().getName()!="BPlusTreeLeafNode"){
			Main.dValue=value2;/*deletion at BPlusTreeNonLeafNode*/
			Main.bPlusRoot=deleteOrList(Main.bPlusRoot, value1);/*call function for value*/
			while(Main.dValue!=null&&Main.dValue<=value2){/*call function until reaching up limits*/
				Main.bPlusRoot=deleteOrList(Main.bPlusRoot, Main.dValue);/*call function for value*/
			}
			if(Main.dValue==null&&Main.bPlusRoot.getClass().getName()=="BPlusTreeLeafNode")
			{/*deletion at BPlusTreeLeafNode*/	
				Main.dValue=value2;
				Main.bPlusRoot=deleteOrList(Main.bPlusRoot, value1);
			}

		}
		else
		{/*deletion at BPlusTreeLeafNode*/
			Main.dValue=value2;
			Main.bPlusRoot=deleteOrList(Main.bPlusRoot, value1);/*call function for value*/
		}
	}
	public void hatabulucu(Node bn)
	{
		int size=findNodeKeySize(bn);
		int i=0;
		while(i<=size)
		{
			if(((BPlusTreeNonLeafNode)bn).nodes[size]==null)
			{
				System.out.println("HEY1");
			}
			int j=0;
			while(j<size){
				if(((BPlusTreeNonLeafNode)bn).nodes[j]==((BPlusTreeNonLeafNode)bn).nodes[j+1])
					System.out.println("HEY2"+((BPlusTreeNonLeafNode)((BPlusTreeNonLeafNode)bn).nodes[j]).keys[0]);
					j++;
			}
			if(((BPlusTreeNonLeafNode)bn).nodes[i].getClass().getName()=="BPlusTreeNonLeafNode")
				hatabulucu(((BPlusTreeNonLeafNode)bn).nodes[i]);
			i++;
		}
	}
	
}
