public class BTree {
	public static final int d=2;
	Entry newentry=new Entry();
	int root=0;/*this variable is used to determine is there necessary a new root node*/
	public Node delete(Node rootNode,double id)  {/*this function deletin an entry from and related nodes from b tree*/
		Main.numberOfPassedNode++;
		int size=findNodeKeySize((BTreeNode)rootNode);
		int index=findNewIndex((BTreeNode)rootNode,id,size);
		if(index<0)
		{/*it is at this node*/
			index=-(index+1);
			if(((BTreeNode)rootNode).nodes[0]==null)
			{/*it is a leaf node*/
				index=-(index+1);
				deleteEntryWithOptionsFromRoot(((BTreeNode)rootNode),index,id);
				newentry=null;
			}
			else
			{/*it is a root node*/
				if(Main.operation==1||Main.operation==2||Main.operation==3||Main.operation==5)/*this value will be daleted find value one bigger from this*/
				{	
					((BTreeNode)rootNode).entries[index]=swapRootAndLeaf(((BTreeNode)rootNode).nodes[index+1],((BTreeNode)rootNode).entries[index]);
					if(Main.operation==1||Main.operation==3)
					{/*swapped value will be deleted next call because it is one bigger value*/
						Main.dValue=((BTreeNode)rootNode).entries[index].key;
					}
				}
				else if(Main.operation==6){/*if LT deletion*/
					newentry=null;
					if(root!=0)
						root--;
					return rootNode;
				}
				else if(Main.operation==4){/*if GE deletion*/
					newentry=null;
					findOneNextRightValue(((BTreeNode)rootNode).nodes[index+1]);
					if(root!=0)
						root--;
					return rootNode;
				}
				if((((BTreeNode)rootNode).nodes[0]).nodes[0]!=null)
				{/*this level is least 2 level far to leafs*/
					root++;	
					delete(((BTreeNode)rootNode).nodes[index+1],id);/*call function recursively*/
					if(newentry==null){
						if(root!=0)
							root--;
						return rootNode;
					}
					index=findNewIndex((BTreeNode)rootNode,newentry.key,size);
					deleteFromNode((BTreeNode)rootNode,index,newentry.key);
				}
				else
				{/*this level is previous level of leaf level*/
					Main.numberOfPassedNode++;
					deleteFromNode((BTreeNode)rootNode,index+1,id);
					
				}
			}
		}
		else
		{/*the value is not at this node, it can be at sub-levels(near to leafs)*/
			
			if(((BTreeNode)rootNode).nodes[0]==null)
			{/*it is a leaf node*/
				deleteEntryWithOptionsFromRoot(((BTreeNode)rootNode),index,id);
			}
			else if((((BTreeNode)rootNode).nodes[0]).nodes[0]!=null)
			{/*this level is least 2 level far to leafs*/
				root++;
				delete(((BTreeNode)rootNode).nodes[index],id);/*call function recursively*/
				if(Main.dValue==null&&Main.operation!=2&&size>index)
					Main.dValue=((BTreeNode)rootNode).entries[index].key;
				if(newentry==null)
				{	
					if(root!=0)
						root--;
					return rootNode;
				}
				size=findNodeKeySize((BTreeNode)rootNode);
				index=findNewIndex((BTreeNode)rootNode,newentry.key,size);
				deleteFromNode((BTreeNode)rootNode,index,newentry.key);
	
			}
			else
			{/*this level is previous level of leaf level*/
				Main.numberOfPassedNode++;
				deleteFromNode((BTreeNode)rootNode,index,id);
			}
		}
		root--;
		if(root==-1)
		{
			size=findNodeKeySize((BTreeNode)rootNode);
			if(((BTreeNode)rootNode).nodes[0]!=null&&((BTreeNode)rootNode).nodes[1]==null)
				rootNode=((BTreeNode)rootNode).nodes[0];
			else if(newentry!=null&&((BTreeNode)rootNode).nodes[size]==null&&size>0)
				deleteEntry(((BTreeNode)rootNode), -(findNewIndex(((BTreeNode)rootNode), newentry.key,size)+1));
			root=0;
		}
		return rootNode;
		
	}
	private void deleteEntryWithOptionsFromRoot(BTreeNode rootNode, int index,double id) {
		newentry=null;
		if(Main.operation==1)
		{/*BW delete*/
			if (index<0)/*value is found convert it's index to positive*/
				index=-(index+1);
			while(((BTreeNode)rootNode).entries[index]!=null&&((BTreeNode)rootNode).entries[index].key<=Main.dValue)
			{/*delete entries*/
				deleteEntry(((BTreeNode)rootNode), index);

			}
		}	
		else if(Main.operation==2)
		{/*EQ delete*/
			if(index<0)
			{/*it is a leaf node this node and  value founded*/
				index=-(index+1);
				deleteEntry(((BTreeNode)rootNode), index);

			}
		}
		else if(Main.operation==3)
		{/*GE main.dvalue is upper limit*/
			if (index<0)/*value is found convert it's index to positive*/
				index=-(index+1);
			while(((BTreeNode)rootNode).entries[index]!=null)
			{/*delete entries*/
				deleteEntry(((BTreeNode)rootNode), index);

			}
		}
		else if(Main.operation==4)
		{/*GT main.dvalue is upper limit*/
			if (index<0){/*value is found convert it's index to positive*/
				index=-(index+1);
				index++;
			}
			while(index<2*d&&((BTreeNode)rootNode).entries[index]!=null&&((BTreeNode)rootNode).entries[index].key>id)
			{/*delete entries*/
				deleteEntry(((BTreeNode)rootNode), index);

			}
		}
		else if(Main.operation==5)
		{/*LE */
			index=0;
			while(((BTreeNode)rootNode).entries[index]!=null&&((BTreeNode)rootNode).entries[index].key<=id)
			{/*delete entries*/
				deleteEntry(((BTreeNode)rootNode), index);
			}
		}
		else if(Main.operation==6)
		{/*LT */
			index=0;
			while(((BTreeNode)rootNode).entries[index]!=null&&((BTreeNode)rootNode).entries[index].key<id)
			{/*delete entries*/
				deleteEntry(((BTreeNode)rootNode), index);
			}
		}
	}
	private void findOneNextRightValue(BTreeNode pointer) 
	{/*this procedure finds a double value to delete at next "delete" call*/
		while(pointer.nodes[0]!=null){/*find leftmost-sub node of node entry's right node*/
			pointer=pointer.nodes[0];
			Main.numberOfPassedNode++;
		}
		Main.dValue=new Double(pointer.entries[0].key);
	}
	private void deleteNodes(BTreeNode pointer, int index) 
	{/*this procedure deletes one node pointer from affected node*/
		int i=index;
		while(i<2*d && pointer.nodes[i]!=null)
		{/*delete it and split all others(which are at right) 1 left*/
			pointer.nodes[i]=pointer.nodes[i+1];
			i++;
		}
		pointer.nodes[2*d]=null;/*last entry has to be null*/
	}
	private Entry swapRootAndLeaf(BTreeNode pointer,Entry rootpointer)
	{/*this function swap a node entry with leaf entry. Leaf entry must be next bigger value of node entries*/
		Entry tempentry=new Entry();/*take temporarily entry*/
		while(pointer.nodes[0]!=null)/*find leftmost-sub node of node of entry's right node*/
		{	
			pointer=pointer.nodes[0];
			Main.numberOfPassedNode++;
		}
		tempentry=pointer.entries[0];/*keep leaf entry's value in tempentry*/
		pointer.entries[0]=rootpointer;/*swap it with node entry*/
		return tempentry;/*return old leaf entry*/
	}
	private void deleteEntry(BTreeNode pointer,int i)
	{/*this procedure deletes one entry from affected node*/
		while(i<2*d-1 && pointer.entries[i]!=null)
		{/*split all values on deleted entry*/
			pointer.entries[i]=pointer.entries[i+1];
			i++;
		}
		pointer.entries[2*d-1]=null;/*the last entry absolutely will be null*/
	}
	private void makeReadyToAddEntry(int index, BTreeNode pointer) 
	{/*this function prepares pointer to add a new entry*/
		int size=findNodeKeySize(pointer);
		int i=size;
		while(i>index){/*slip entries and create a empty space at index*/
			pointer.entries[i]=pointer.entries[i-1];
			i--;
		}
		i=size+1;
		while(i>index){/*slip keys and create an empty space at index*/
			pointer.nodes[i]=pointer.nodes[i-1];
			i--;
		}
		return;
	}
	private int findNewIndex(BTreeNode pointer, double value,int size) 
	{/*this function finds an index to "value" in a node(between 0 and 2d)*/
		int i=0;
		while(i<2*d)
		{/*compare all entry key values 0 to 2d*/
			if(size<=i||pointer.entries[i].key > value)
				return i;
			if(size<=i||pointer.entries[i].key ==value)
				return -i-1;
			i++;
		}			
		return i;
	}
	private int findNodeKeySize(BTreeNode pointer)
	{/*this function finds number of entries in a node*/
		int i;
		int size;/*size of array it may include empty spaces*/
		i=2*d-1;/*last index*/
		size=2*d;/*length of array*/
		while(i>-1)
		{/*find size of entry with looking pointers with starting last element of node*/
			if(pointer.entries[i]==null)
				size--;
			i--;
		}
		return size;/*return real size of node's entry array*/
	}
	private void deleteFromNode(BTreeNode rootPointer,int index,double id)
	{/*this procedure deletes a subtree's node and it makes redistribution or merging if it is necessary*/
		int leftSiblingSize=0;/*left sibling of current node*/
		int rightSiblingSize=0;/*right sibling of current node*/
		if(index>0)/*is there exist a left sibling?*/
		{	
			Main.numberOfPassedNode++;
			leftSiblingSize=findNodeKeySize(((BTreeNode)rootPointer.nodes[index-1]));
		}
		if(index<findNodeKeySize(((BTreeNode)rootPointer)))/*is there exist a right siblings?*/
		{	
			Main.numberOfPassedNode++;
			rightSiblingSize=findNodeKeySize(((BTreeNode)rootPointer.nodes[index+1]));
		}
		int currentSiblingSize=findNodeKeySize(((BTreeNode)rootPointer.nodes[index]));/*find current siblings size*/
		int i=findNewIndex((BTreeNode)rootPointer.nodes[index],id,currentSiblingSize);/*find id's index*/
		if(Main.operation==1||Main.operation==3||Main.operation==4)
		{/*BW or GE or GT delete*/
			int control=0;
			if(i<0){
				i=-(i+1);
				control=1;
			}
			else if(i==currentSiblingSize){
				Main.dValue=null;
				if(rightSiblingSize>0)
				{/*find next delete value from right parent*/
					Main.dValue=new Double(rootPointer.entries[index].key);
				}
				return;/*this is greater from all tree nodes*/
			}
			if(((BTreeNode)rootPointer.nodes[index]).nodes[0]==null&&Main.operation==1&&Main.dValue!=null&&((BTreeNode)rootPointer.nodes[index]).entries[i].key>Main.dValue)
			{/*control top restrict*/
				Main.dValue=((BTreeNode)rootPointer.nodes[index]).entries[i].key;
				return;
			}
			if(Main.dValue==null){	
				if(i+1<2*d&&(rootPointer.nodes[index]).entries[i+1]!=null)
				{/*find next delete value from same node*/
					Main.dValue=new Double((rootPointer.nodes[index]).entries[i+1].key);
				}
				else if(rightSiblingSize>0)
				{/*find next delete value from right parent*/
					Main.dValue=new Double(rootPointer.entries[index].key);
				}
			}
			if((Main.operation!=4&&control==1)||(control==0)){
				deleteEntry((BTreeNode)rootPointer.nodes[index],i);/*delete related entry at node*/
				currentSiblingSize--;/*an entry deleted from current node*/
			}
			else{ 
				newentry=null;
				Main.operation=3;/*it missed current value because it must star to delete next*/
				return;
			}
		}
		else if(Main.operation==2)
		{/*EQ delete*/
			if(i<0)
				i=-(i+1);
			else {/*value is not present*/
				newentry=null;
				return;
			}
			deleteEntry((BTreeNode)rootPointer.nodes[index],i);/*delete related entry at node*/
			currentSiblingSize--;/*an entry deleted from current node*/
		}
		else if(Main.operation>=5)
		{/*LE or LG delete*/
			if(i<0)
				i=-(i+1);
			if(Main.dValue==null){	
				if(i+1<2*d&&(rootPointer.nodes[index]).entries[i+1]!=null)
				{/*find next deleted value from same node*/
					Main.dValue=new Double((rootPointer.nodes[index]).entries[i+1].key);
				}
				else if(rightSiblingSize>0)
				{/*find next deleted value from right parent*/
					Main.dValue=new Double(rootPointer.entries[index].key);
				}
			}

			deleteEntry((BTreeNode)rootPointer.nodes[index],i);/*delete related entry at node*/
			currentSiblingSize--;/*an entry deleted from current node*/
		}	
		if(currentSiblingSize>=d)/*there is not a sub overflow*/
		{	newentry=null;
			return;
		}
		else if(leftSiblingSize>d)
		{/*try to redistribution with left sibling*/
			makeReadyToAddEntry(0, (BTreeNode)rootPointer.nodes[index]);/*current node will take left parents entry*/
			((BTreeNode)rootPointer.nodes[index]).entries[0]=rootPointer.entries[index-1];
			rootPointer.entries[index-1]=((BTreeNode)rootPointer.nodes[index-1]).entries[leftSiblingSize-1];/*left parent node will take left sibling node's biggest value*/
			((BTreeNode)rootPointer.nodes[index-1]).entries[leftSiblingSize-1]=null;/*left sibling node's biggest value will be null*/
			
			((BTreeNode)rootPointer.nodes[index]).nodes[0]=((BTreeNode)rootPointer.nodes[index-1]).nodes[leftSiblingSize];/*update nodes*/
			((BTreeNode)rootPointer.nodes[index-1]).nodes[leftSiblingSize]=null;
			newentry=null;
		}
		else if(rightSiblingSize>d)
		{/*try to redistribution with right sibling*/
			((BTreeNode)rootPointer.nodes[index]).entries[currentSiblingSize]=rootPointer.entries[index];/*right parent will be current node's last entry*/
			rootPointer.entries[index]=((BTreeNode)rootPointer.nodes[index+1]).entries[0];/*right parent will take rightSiblings smallest entry*/
			deleteEntry(((BTreeNode)rootPointer.nodes[index+1]),0);/*delete rightsiblings smallest entry*/
			
			((BTreeNode)rootPointer.nodes[index]).nodes[currentSiblingSize+1]=((BTreeNode)rootPointer.nodes[index+1]).nodes[0];/*update nodes*/
			deleteNodes(((BTreeNode)rootPointer.nodes[index+1]),0);
			newentry=null;
		}
		else if(leftSiblingSize>0)
		{/*try to merging node with left sibling*/
			newentry=rootPointer.entries[index-1];
			((BTreeNode)rootPointer.nodes[index-1]).entries[leftSiblingSize]=rootPointer.entries[index-1];/*add left parent to left sibling */
			leftSiblingSize++;
			i=0;
			while(leftSiblingSize<2*d)
			{
				((BTreeNode)rootPointer.nodes[index-1]).entries[leftSiblingSize]=((BTreeNode)rootPointer.nodes[index]).entries[i];/*add current node entries to left sibling*/
				((BTreeNode)rootPointer.nodes[index]).entries[i]=null;
		
				((BTreeNode)rootPointer.nodes[index-1]).nodes[leftSiblingSize]=((BTreeNode)rootPointer.nodes[index]).nodes[i];
				((BTreeNode)rootPointer.nodes[index]).nodes[i]=null;
				currentSiblingSize--;
				
				leftSiblingSize++;
				i++;
			}
			((BTreeNode)rootPointer.nodes[index-1]).nodes[leftSiblingSize]=((BTreeNode)rootPointer.nodes[index]).nodes[i];
			((BTreeNode)rootPointer.nodes[index]).nodes[i]=null;
			while(index<findNodeKeySize(rootPointer)&&rootPointer.nodes[index+1]!=null)
			{/*update nodes*/
				rootPointer.nodes[index]=rootPointer.nodes[index+1];	
				index++;
			}
			rootPointer.nodes[index]=null;
		}
		else
		{/*try  to merging node with right sibling*/	
	
			newentry=rootPointer.entries[index];
			((BTreeNode)rootPointer.nodes[index]).entries[currentSiblingSize]=rootPointer.entries[index];/*add the right parent to current*/
			currentSiblingSize++;
			i=0;
	
			while(currentSiblingSize<2*d)
			{
				((BTreeNode)rootPointer.nodes[index]).entries[currentSiblingSize]=((BTreeNode)rootPointer.nodes[index+1]).entries[i];/*add right sibling entries to current node*/
				((BTreeNode)rootPointer.nodes[index+1]).entries[i]=null;
				
				((BTreeNode)rootPointer.nodes[index]).nodes[currentSiblingSize]=((BTreeNode)rootPointer.nodes[index+1]).nodes[i];
				((BTreeNode)rootPointer.nodes[index+1]).nodes[i]=null;
				
				currentSiblingSize++;
				i++;
			}
			((BTreeNode)rootPointer.nodes[index]).nodes[currentSiblingSize]=((BTreeNode)rootPointer.nodes[index+1]).nodes[i];
			((BTreeNode)rootPointer.nodes[index+1]).nodes[i]=null;

			index++;
			while(index<findNodeKeySize(rootPointer)&&rootPointer.nodes[index+1]!=null)
			{/*update nodes*/
				rootPointer.nodes[index]=rootPointer.nodes[index+1];	
				index++;
			}
			rootPointer.nodes[index]=null;
		}
	}
	public Node findSmallest(BTreeNode pointer)
	{/*this function finds the smallest node in b plus tree recursively*/
		if(pointer.nodes[0]!=null){/*go to left most node in tree*/
			pointer=(BTreeNode) findSmallest((pointer).nodes[0]);
			Main.numberOfPassedNode++;
		}
		return pointer;
	}
	public Node insert(Node rootPointer,Entry entry) 
	{/*this procedure inserts value to Btree*/	
		Main.numberOfPassedNode++;
		BTreeNode newChild=null;/*this is a node which holds new sibling node*/
		int i;
		int size=findNodeKeySize((BTreeNode)rootPointer);/*find size of root*/
		int index=findNewIndex(((BTreeNode)rootPointer), entry.key,size);/*find a index value to access a sub-tree*/
		if(((BTreeNode)rootPointer).nodes[0]==null)
		{/*it is a leaf node find a avaliable index to an entry at node*/
			if(index<0){
				return newChild;
			}
			if( size < 2*d)
			{/*there is sufficient space for adding entry to node*/
				makeReadyToAddEntry(index,(BTreeNode)rootPointer);

				((BTreeNode)rootPointer).entries[index]=entry;	
				newentry=null;/*there is not a new entry*/
				newChild=((BTreeNode)rootPointer);/*there is not a new child*/
			} 
			else
			{/*split this node to two sibling nodes*/
				Main.numberOfPassedNode++;
				newChild=new BTreeNode();
				Entry tempentry=new Entry();
				if(index==2*d)
				{/* "tempentry" will be equal to "entry" which is bigger from all others*/
					tempentry=entry;
				}	
				else
				{/*keep the biggest value of node at tempentry and insert element to node"*/
					tempentry=((BTreeNode)rootPointer).entries[2*d-1];/*keep biggest value in "tempEntry"*/
					((BTreeNode)rootPointer).entries[2*d-1]=null;/*remove keeped value */
					makeReadyToAddEntry(index, (BTreeNode)rootPointer);
					((BTreeNode)rootPointer).entries[index]=entry;/*add "entry" to node*/
				}
				int indexOfLastKey=2*d-(d+2);/*new node's last entry will be at this index of new node*/
				i=2*d-1;
				while(i>d)
				{/*move entries d+1 to 2d to new node*/
					
					((BTreeNode)newChild).entries[indexOfLastKey]=((BTreeNode)rootPointer).entries[i];
					((BTreeNode)rootPointer).entries[i]=null;/*delete moved entries from node*/
					i--;
					indexOfLastKey--;
				}
				
				((BTreeNode)newChild).entries[(2*d-(d+1))]=tempentry;/*add biggest value to node*/
				newentry=((BTreeNode)rootPointer).entries[d];/*find entry which will be inserted to up level*/
				((BTreeNode)rootPointer).entries[d]=null;
			}			
		}
		else
		{
			if(index<0){
				return newChild;
			}
			root++;/*level of rootpointer came close to leafs*/
			newChild=(BTreeNode) insert(((BTreeNode)rootPointer).nodes[index],entry);
			if (newentry==null){/*there is not a new entry to add this node*/
				if(root!=0)
					root--;/*level of rootpointer came close to root of tree*/
				return rootPointer;
			}
			size=findNodeKeySize((BTreeNode)rootPointer);
			index=findNewIndex(((BTreeNode)rootPointer), newentry.key,size);/*find a new index value to add "newentry" this node*/
			if(findNodeKeySize((BTreeNode)rootPointer) < 2*d)
			{/*there is sufficient space for adding key to node*/
				makeReadyToAddEntry(index, (BTreeNode)rootPointer);
				((BTreeNode)rootPointer).entries[index]=newentry;/*add key to node*/
				((BTreeNode)rootPointer).nodes[index+1]=newChild;/*add new node pointer to node*/
				newentry=null;/*there is no more entry which will be added to node*/
				newChild=(BTreeNode) rootPointer;/*there is not any new node pointer*/
			}
			else
			{/*split node to two sibling nodes*/
				Main.numberOfPassedNode++;
				BTreeNode tempnode=new BTreeNode();/*a temporarily node which keeps a node*/
				Entry tempkey =new Entry();/*a temporarily node which keeps a key the biggest one*/
				if(index==2*d)
				{/*"newentry" will move to new node it's value is bigger from all others*/
					tempkey= newentry;/*"newkey" is the biggest*/
					tempnode= newChild;/*new child pointer is "newkey"s next pointer */
				}	
				else
				{
					tempkey=((BTreeNode)rootPointer).entries[2*d-1];/*keep biggest value in "tempEntry"*/
					tempnode =((BTreeNode)rootPointer).nodes[2*d];/*keep node pointer which is after "tempentry"*/
					
					((BTreeNode)rootPointer).entries[2*d-1]= null;/*delete keeped key*/
					((BTreeNode)rootPointer).nodes[2*d]= null;/*delete keeped key*/
					
					makeReadyToAddEntry(index,(BTreeNode) rootPointer);/*this function preparing node array*/
					
					((BTreeNode)rootPointer).entries[index]=newentry;/* add newentry key to node*/
					((BTreeNode)rootPointer).nodes[index+1]=newChild;/*add newentry's node pointer to node*/
				}
				newChild= new BTreeNode();/*new node*/
				int indexOfLastKey=2*d-(d+2);/*new node's last key will be at this index of new node*/
				i=2*d-1;
				while(i>d)
				{/*move entries d+1 to 2d to new node*/
					
					newChild.entries[indexOfLastKey]=((BTreeNode)rootPointer).entries[i];
					((BTreeNode)rootPointer).entries[i]=null;/*remove key*/
					
					newChild.nodes[indexOfLastKey]=((BTreeNode)rootPointer).nodes[i];
					((BTreeNode)rootPointer).nodes[i]=null;
					i--;
					indexOfLastKey--;
				}
				newChild.nodes[2*d-(d+1)]=((BTreeNode)rootPointer).nodes[2*d];/*add last keys left node pointer*/
				((BTreeNode)rootPointer).nodes[2*d]=null;
				newChild.entries[2*d-(d+1)]=tempkey;/*add last entry's key number*/
				newChild.nodes[2*d-(d)]= tempnode;/*add last key's last right node pointer*/
				newentry =new Entry();
				newentry=((BTreeNode)rootPointer).entries[d];
				((BTreeNode)rootPointer).entries[d]=null;/*remove key*/
			}
		}
		root--;
		if(root==-1)
		{
			if(newChild!=rootPointer)
			{
				Main.numberOfPassedNode++;
				BTreeNode newRoot=new BTreeNode();/*create a new root to tree*/
				newRoot.entries[0]=newentry;/*insert it's key value*/
				newRoot.nodes[0]=(BTreeNode) rootPointer;/*insert it's left node pointer*/
				newRoot.nodes[1]=newChild;/*insert it's right pointer*/
				newChild=newRoot;/*return root of tree*/
			}
			root=0;
		}
		return newChild;
	}
	public void listSmaller(BTreeNode pointer,Double id)
	{/*this procedure list all values which are smaller than "id"*/
		if(pointer==null)
			return;
		int size=findNodeKeySize(pointer);/*find size of current node*/
		int index=findNewIndex(pointer, id, size);/*find index of*/
		int i;
		if(index<0)
		{/*if index negative value is found*/
			i=0;
			index=-(index+1);/*convert index to positive*/
			while(i<index)
			{/*loop is starting from index and go to 0 */
				listAll(pointer.nodes[i]);/*call list all function*/
				Main.arr.add(pointer.entries[i].pointer_to_file);/*add index to arraylist to display it to output file after*/
				i++;
			}
			listAll(pointer.nodes[i]);/*call list all function*/
			if(Main.operation==-5)
				Main.arr.add(pointer.entries[i].pointer_to_file);/*add index to arraylist to display it to output file after*/
		}
		else
		{/*else value couldn't found*/
			i=0;
			while(i<index)
			{/*loop is starting from 0 and go to index */
				listAll(pointer.nodes[i]);/*call list all function*/
				Main.arr.add(pointer.entries[i].pointer_to_file);/*add index to arraylist to display it to output file after*/
				i++;
			}
			listSmaller(pointer.nodes[index],id);/*call function recursively*/
		}
	}
	public void listGreater(BTreeNode pointer,Double id)
	{/*this procedure list all values which are greater than "id"*/
		if(pointer==null)
			return;
		int size=findNodeKeySize(pointer);/*find size of current node*/
		int index=findNewIndex(pointer, id, size);/*find index of "id"*/
		if(index>=0&&index<size+1){/*if index positive and smaller than size of node value is found*/
			listGreater(pointer.nodes[index],id);/*call function recursively*/
			if(pointer.entries[index]!=null)
				Main.arr.add(pointer.entries[index].pointer_to_file);/*add entry's pointer data buffer to arraylist it will listed later*/
			index++;
			while(index<2*d&&pointer.entries[index]!=null)
			{/*loop is starting from index and go to 0 */
				listAll(pointer.nodes[index]);/*call list all function*/
				Main.arr.add(pointer.entries[index].pointer_to_file);/*add entry's pointer data buffer to arraylist it will listed later*/
				index++;
			}
			if(pointer.nodes[index]!=null)
			{/*if last node pointer is exist list it's right node entries*/
				listAll(pointer.nodes[index]);/*call list all function*/
			}
		}
		else if(index==size+1)return;/*else value couldn't found and it is not and there is not any greater value from it.*/
		else{/*else value couldn't found*/
			index=-(index+1);
			if(Main.operation==-3)/*if listing operation is GE*/
				Main.arr.add(pointer.entries[index].pointer_to_file);/*add entry's pointer data buffer to arraylist it will listed later*/
			
			index++;
			while(index<2*d&&pointer.entries[index]!=null)
			{/*loop is starting with index go until size of node*/
				listAll(pointer.nodes[index]);/*call list all function*/
				Main.arr.add(pointer.entries[index].pointer_to_file);/*add entry's pointer data buffer to arraylist it will listed later*/
				index++;
			}
			if(pointer.nodes[index]!=null)
			{/*if last node pointer is exist list it's right node entries*/
				listAll(pointer.nodes[index]);/*call list all function*/
			}	

		}
	}
	public void listBetween(BTreeNode pointer,Double id)
	{/*this procedure list all values which are greater than "id" and smaller than Main.dValue */
		if(pointer==null)
			return;
		int size=findNodeKeySize(pointer);/*find size of current node*/
		int index=findNewIndex(pointer, id, size);/*find index of "id"*/
		if(index>=0&&index<size+1){
			listBetween(pointer.nodes[index],id);/*call function recursively*/
			if(pointer.entries[index]!=null&&pointer.entries[index].key<=Main.dValue)
				Main.arr.add(pointer.entries[index].pointer_to_file);/*add entry's pointer data buffer to arraylist it will listed later*/
			index++;
			while(index<2*d&&pointer.entries[index]!=null&&pointer.entries[index].key<Main.dValue)
			{
				listAll(pointer.nodes[index]);/*call list all function*/
				Main.arr.add(pointer.entries[index].pointer_to_file);/*add entry's pointer data buffer to arraylist it will listed later*/
				index++;
			}
			if(pointer.nodes[index]!=null&&pointer.entries[index-1].key<Main.dValue)
			{
				listBetween(pointer.nodes[index],id);/*call function recursively*/
			}
			if(index<2*d&&pointer.entries[index]!=null&&pointer.entries[index].key==Main.dValue)
			{
				Main.arr.add(pointer.entries[index].pointer_to_file);/*add entry's pointer data buffer to arraylist it will listed later*/
			}
		}
		else if(index==size+1)return;
		else{
			index=-(index+1);
			Main.arr.add(pointer.entries[index].pointer_to_file);
			
			index++;
			while(index<2*d&&pointer.entries[index]!=null&&pointer.entries[index].key<Main.dValue)
			{
				listAll(pointer.nodes[index]);/*call list all function*/
				Main.arr.add(pointer.entries[index].pointer_to_file);/*add pointer_to_databuffer to arraylist which will be listed to output file*/
				index++;
			}
			if(pointer.nodes[index]!=null&&pointer.entries[index-1].key<Main.dValue)
			{
				listBetween(pointer.nodes[index],id);/*call this function recursively*/
			}
			if(index<2*d&&pointer.entries[index]!=null&&pointer.entries[index].key==Main.dValue)
			{
				Main.arr.add(pointer.entries[index].pointer_to_file);/*add pointer_to_databuffer to arraylist which will be listed to output file*/
			}	
			
		}
	}
	public void listEqual(BTreeNode pointer,Double id)
	{/*this procedure list a value which is equal to "id"*/
		if(pointer==null)
			return;
		int size=findNodeKeySize(pointer);/*find current pointer size*/
		int index=findNewIndex(pointer, id, size);/*find index of related entry*/
		if(index<0)
		{/*if it is found*/
			index=-(index+1);
			Main.arr.add(pointer.entries[index].pointer_to_file);/*add pointer_to_databuffer to arraylist which willbe listed to output file*/
		}
		else{/*value not  found*/		
			if(index+1==size)
				return;
			listEqual(pointer.nodes[index],id);/*call functiobn recursively*/
		}
	}
	private void listAll(BTreeNode pointer) 
	{/*this procedure list all values at b tree*/
		if(pointer==null)
			return;
		int i=0;
		int size=findNodeKeySize(pointer);/*find size of currrent pointer*/
		while(i<size&&pointer.entries[i]!=null)
		{/*list all values until reaching size */
			listAll(pointer.nodes[i]);/*list all nodes*/
			Main.arr.add(pointer.entries[i].pointer_to_file);/*add entry index to arraylist*/
			i++;
		}
		listAll(pointer.nodes[i]);/*list all nodes*/
	}
	public void travelAll(BTreeNode pointer,char[] sTemp,int fieldNo) 
	{/*this procedure travelling all nodes at b tree*/
		Main.numberOfPassedNode++;
		if(pointer==null)
			return;
		int i=0;
		int size=findNodeKeySize(pointer);/*find size of current node*/
		while(i<size&&pointer.entries[i]!=null)
		{
			travelAll(pointer.nodes[i],sTemp,fieldNo);/*call function recursively*/
			int j=pointer.entries[i].pointer_to_file;
			if(fieldNo==1)
			{/*comparing field no is 1*/
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
			{/*comparing field no is 2*/
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
			{/*comparing field no is 3*/
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
			{/*comparing field no is 4*/
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
			{/*comparing field no is 5*/
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
			{/*comparing field no is 6*/
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
		travelAll(pointer.nodes[i],sTemp,fieldNo);/*call function recursively*/
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
	public void deleteSmaller(Double value1)
	{/*this procedure daletes all entries which are smaller than value1*/
		if(((BTreeNode)Main.bRoot).nodes[0]!=null){
			BTreeNode pointer=(BTreeNode)findSmallest((BTreeNode) Main.bRoot);/*find smallest node at tree*/
			Main.dValue=pointer.entries[0].key;
			while(Main.dValue!=null&&Main.dValue<value1&&((BTreeNode)Main.bRoot).nodes[0]!=null)
			{/*main.dvalue is keeps next value which will be deleted*/

				Double newValue=new Double(Main.dValue);
				Main.dValue=null;
				Main.bRoot=(BTreeNode) delete(Main.bRoot, newValue);/*call function for value*/

			}
			if(Main.operation==5&&Main.dValue!=null&&Main.dValue==value1+0.0&&((BTreeNode)Main.bRoot).nodes[0]!=null)
			{/*if deletion operation is LE than delete value2 to*/
				Double newValue=new Double(Main.dValue);
				Main.dValue=null;
				Main.bRoot=(BTreeNode) delete(Main.bRoot, newValue);/*call function for value*/
			}
			if(((BTreeNode)Main.bRoot).nodes[0]==null)
			{
				Main.bRoot=(BTreeNode) delete(Main.bRoot, value1);

			}
		}
		else{
			Main.bRoot=(BTreeNode) delete(Main.bRoot, value1);/*call function for value*/
		}
	}
	public void deleteGreater(Double value1)
	{/*this procedure delete all greater values from "value1"*/
		int control=0;
		Main.bRoot=delete(Main.bRoot, value1);/*call function for value*/
		int operation=Main.operation;
		Main.operation=3;
		while(Main.dValue!=null)
		{

			Double newValue=new Double(Main.dValue);
			Main.dValue=null;
			Main.bRoot=delete(Main.bRoot, newValue);/*call function for value*/
			control=1;
		}
		if(control==1&&((BTreeNode)Main.bRoot).nodes[0]==null)
		{
			Main.operation=operation;
			Main.bRoot=delete(Main.bRoot, value1);/*call function for value*/
			control=0;
		}	
	}
	public void deleteBetween(Double value1,Double value2)
	{/*this procedure delete all greater values from "value1" and smaller from "value2"*/
		if(((BTreeNode)Main.bRoot).nodes[0]!=null){
			Main.dValue=value2;
			Main.bRoot=delete(Main.bRoot, value1);/*call function for value*/

			while(Main.dValue!=null&&Main.dValue<=value2&&((BTreeNode)Main.bRoot).nodes[0]!=null)
			{

				Double newValue=new Double(Main.dValue);
				Main.dValue=null;
				Main.bRoot=delete(Main.bRoot, newValue);/*call delete function for newValue*/
			}
			if(((BTreeNode)Main.bRoot).nodes[0]==null)
			{
				Main.dValue=value2;
				Main.bRoot=delete(Main.bRoot, value1);/*call delete function for newValue*/
			}
		}
		else{
			Main.dValue=value2;
			Main.bRoot=delete(Main.bRoot, value1);/*call function for value*/
		}
	}
}
