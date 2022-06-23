

import java.util.*;

/******************************************************************************
 * <p>Title: CMSC420 </p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: </p>
 *
 * @author Alexios Aliagas
 * @version 1.0
 * EMAIL : ale3hs@aliagas.gr
 ******************************************************************************/

public class BPGuideNode implements BPNode {
  private Comparator   comparator;
  private int          ksize;     // occupied keys
  private Object[]     keys;      // index keys
  private static int   num_keys;  // number of index keys
  public BPNode[]      children;  // Children
  private static int   LeafSize;  // the leaf size

  /****************************************************************************
   *
   * @param comp Comparator
   * @param n_keys int
   ****************************************************************************/
  public BPGuideNode(Comparator comp,int n_keys,int LeafSize) {
    comparator = comp;
    num_keys   = n_keys;
    keys       = new Object[num_keys-1];
    children   = new BPNode[num_keys];
    this.LeafSize = LeafSize;
  }

  /****************************************************************************
   *
   * @return int
   * return GUIDE OR LEAF
   ***************************************************************************/
   public int getType(){
     return BPNode.GUIDE;
   }

   /****************************************************************************
    *
    * @return Comparator
    * returns comparator
    ***************************************************************************/
  public Comparator comparator(){
    return comparator;
  }

  /****************************************************************************
   *
   * @return boolean
   * specifies weather the node is full or not
   ***************************************************************************/
  public boolean isFull(){
    return num_keys==ksize;
  }

  /****************************************************************************
   *
   * @param index int
   * @return Object
   * gets child at index
   ***************************************************************************/
   public Object getItemAt(int index){
     return children[index];
   }

   /****************************************************************************
    *
    * @param index int
    * @return Object
    * gets key at index
    ***************************************************************************/
    public Object getKeyAt(int index){
      return keys[index];
   }

   /****************************************************************************
    *
    * @return int
    * return the size of the occupied
    ***************************************************************************/
   public int size(){
     return ksize;
   }

   /****************************************************************************
    *
    * @return Object
    * return the smallest key
    ***************************************************************************/
   public Object minKey(){
     return children[0].minKey();
   }


   /****************************************************************************
    * decrease size
    ***************************************************************************/
   public void decreaseSize(){
     ksize--;
   }

   /****************************************************************************
    * increase size
    ***************************************************************************/
   public void increaseSize(){
     ksize++;
   }

   /****************************************************************************
    *
    * @return int
    * fill factor
    ***************************************************************************/
   public int fillFactor(){
     int tmp =(int)Math.ceil(num_keys / 2.0);
     return tmp;
  }

  /****************************************************************************
   *
   * @return Object
   *
   * return the maximum key
   ***************************************************************************/
  public Object maxKey(){
     return keys[ksize-2];
  }

  /****************************************************************************
   *
   * @return int
   * return the max size, either keys or records
   ***************************************************************************/
   public int maxSize(){
     return num_keys;
   }

   /****************************************************************************
    *
    * @param new_size int
    * changes the size, used after shifts
    ***************************************************************************/
   public void modifySize(int new_size){
     ksize = new_size;
   }

   /**************************************************************************
    *
    * @param k1 Object
    * @param k2 Object
    * @return int
    * Compares two keys using the correct comparison method for this TreeMap.
    *************************************************************************/
   private int compare(Object k1, Object k2) {
       return (comparator==null ? ((Comparable)k1).compareTo(k2)
                                : comparator.compare(k1, k2));
   }

   /****************************************************************************
    *
    * @param entry Entry
    * @return BPNode
    * insert a new item
    ***************************************************************************/
   public BPNode put(BPTree.Entry entry){
     BPNode next_node=null,child=null;
     boolean done    = false;

     for (int i = 0; i<ksize-1; i++){
       if (compare(entry.getKey(),keys[i])<0) {
         //next_node =children[i].put(entry,this);
         next_node =do_insert(entry,i);
         done = true;
         break;
       }
     }

     if(!done){
      // next_node = children[ksize-1].put(entry,this);
      next_node =do_insert(entry,ksize-1);
     }

     if(next_node!=null){
       if(!this.isFull()){
         insertNext(next_node);
         //insertNonFull(entry,next_node);
       }else{
         child = split(next_node,null);
       }

     }

     return child;
   }


   /****************************************************************************
    *
    * @return BPNode
    * returns the rightest child, applies only to guide node
    ***************************************************************************/
   public BPNode getLastChild(){
     return children[ksize-1];
   }

   /****************************************************************************
    *
    * @param o Object
    *  puts something at the beginning of the children or records
    ***************************************************************************/
   public void putFirst(Object o){
     children[0] = (BPNode)o;
   }

   /****************************************************************************
    *
    * @param key Object
    * @return BPNode
    * REMOVE A RECORD AND THEN ORGANIZE
    ***************************************************************************/
  public BPNode remove(Object key){
     throw new UnsupportedOperationException("Implement This");
  }


  /****************************************************************************
       does the actual shifts and insertions
  ****************************************************************************/
   private BPNode do_insert(BPTree.Entry entry, int to_index){
     BPNode next_node = null;
     boolean done     = false;

     if(children[to_index].isFull()){
       done = rotateLeft(to_index,entry);
       if(!done){
         done = rotateRight(to_index,entry);
       }
     }
     if(!done){
       next_node = children[to_index].put(entry);
     }

     return next_node;
   }

   /****************************************************************************
    *
    * @param o Object
    * append a child or record to the end
    ***************************************************************************/
   public void append(Object o){
      boolean done = false;

      for(int i=0;i<ksize;i++){
        if(compare(((BPNode)o).minKey(),children[i].minKey())<0){
          if(i==0){
            shiftDown(0);
            children[0] = (BPNode)o;
            keys[0] = children[1].minKey();

          }
          else{
            shiftDown(i - 1);
            keys[i - 1] = (Object) ( (BPNode) o).minKey();
            children[i] = (BPNode) o;
          }
          done = true;
          break;
        }
      }

      if(done) return;
      children[ksize] = (BPNode)o;

      if(ksize >= 1){
       keys[ksize - 1] = (Object) ((BPNode)o).minKey();
      }

    ksize++;
   }


   /****************************************************************************
    *
    * @param key Object
    * puts in a new child ONLY GUIDE CALL FUNCTION NOT PART OF BPNODE
    ***************************************************************************/
   public void putMidKey(Object key){

      keys[0]=key;
   }

   /****************************************************************************
    *
    * @param pos int
    * @param start int
    * @return BPNode
    * shift the records upwards (TO THE LEFT)
    ***************************************************************************/
   public BPNode shiftUp(int pos, int start){
     int p=start;

     for(int i=pos;i<ksize;i++){
       children[p] = children[i];
       if(i<ksize-1)
          keys[p]  = keys[i];
       p++;
     }

     ksize = ksize - (int)Math.abs(pos-start);
     return null;
  }

  /****************************************************************************
   *
   * @param pos int
   * shift the records downwards
   ***************************************************************************/
  public void shiftDown(int pos){
    int p=pos+1;

    for(int i=ksize;i>pos;i--){
      children[i] = children[i-1];
      if(i>=1)
         keys[i-1]   = children[i].minKey();

    }
   ksize = ksize +1;

   }


  /****************************************************************************
   *
   * @param curr int
   * @param entry Entry
   * @return boolean
   * rotate children or keys to the left
   ***************************************************************************/
  private boolean rotateLeft(int curr,BPTree.Entry entry){
    boolean success = false;
    if(curr>0){
      if(!children[curr-1].isFull()){//left sibling not full
        if(children[curr].getType() == BPNode.LEAF ){
          BPTree.Entry tmp = (BPTree.Entry)children[curr].getItemAt(0);
          if(compare(entry.getKey(),tmp.getKey())<0){//its greater
          // it would distort the order of the b+tree
            return false;
          }
          //tmp.setRight(((TRecord)children[curr+1].getItemAt(0)));
        }else{
          BPNode tmp = (BPNode)children[curr].getItemAt(0);
          Object wKey ;
          if(tmp.getType() == BPNode.LEAF){
            wKey = ((BPLeafNode)tmp).getMaxRecord();
            wKey = ((BPTree.Entry)wKey).getKey();
          }else{
            wKey = tmp.getLastChild().maxKey();
          }
          if(compare(entry.getKey(),wKey)<0){//its greater
          // it would distort the order of the b+tree
            return false;
          }
        }

        children[curr-1].append(children[curr].getItemAt(0)); //add next min record to previous sibling
        children[curr].shiftUp(1,0); //shift recs to the left

        children[curr].put(entry);
        keys[curr-1] = children[curr].minKey();
        success = true;
      }
    }
    return success;
  }

  /****************************************************************************
   *
   * @param curr int
   * @param entry Entry
   * @return boolean
   * rotate children or keys to the right
   ***************************************************************************/
  private boolean rotateRight(int curr,BPTree.Entry entry){
    boolean success = false;
    if(ksize>curr+1){
      if(!children[curr+1].isFull()){//left sibling not full
        if(children[curr].getType() == BPNode.LEAF){
          BPTree.Entry tmp = (BPTree.Entry)children[curr].getItemAt(children[curr].size()-1);
          if(compare(entry.getKey(),tmp.getKey())>0){//its greater
          // it would distort the order of the b+tree
            return false;
          }
          //tmp.setRight(((TRecord)children[curr+1].getItemAt(0)));
        }else{
          BPNode tmp = (BPNode)children[curr].getItemAt(children[curr].size()-1);
          if(compare(entry.getKey(),tmp.minKey())>0){//its greater
          // it would distort the order of the b+tree
            return false;
          }
        }
        children[curr+1].shiftDown(0); //shift recs to the right
        children[curr+1].putFirst(children[curr].getItemAt(children[curr].size()-1)); //add next min record to previous sibling
        children[curr].modifySize(children[curr].size()-1);
        children[curr].put(entry);
        keys[curr] = children[curr+1].minKey();
        success = true;
      }
    }
    return success;
  }


  /****************************************************************************
   *
   * @param entry Entry
   *
   * inserts the record in the appropriate position since there is
   * space in this node without splitting
   ***************************************************************************/
   private int insertNext(BPNode node){
     boolean done = false;
     int position = 0;

       for (int i = 0; i < ksize-1; i++){
         if (compare(node.minKey(), keys[i]) < 0) {
           shiftDown(i+1);
           done = true;
           keys[i]   = node.minKey();
           children[i+1] = node;
           position    = i;
           ksize--;//fix size because shift messed it up
           break;
         }
     }

     if (!done){
       children[ksize] = node;
       position        = ksize;
       keys[ksize-1]   = node.minKey();

     }

     ksize++;
     return position;
  }

   /****************************************************************************
    *
    * @param entry BPNode
    * @param caller BPNode
    * @return BPGuideNode
    *  SPLIT FUNCTION GUIDE
    *  find the middle, add it including the entry if it is greater than the
    *  middle, else add it to this recordset
    *  also insert the middle into the guide that called this.put
    *
    *  split children, middile key gets promoted to higher level
    *  less than middle key go to left, greater goto right
    ***************************************************************************/
   private BPGuideNode split(BPNode entry,BPNode caller){
    BPGuideNode next = new BPGuideNode(comparator,num_keys,LeafSize);
    BPNode   firstChild = null;
    BPNode   split_child=null;
    int mid = (int)Math.ceil(ksize / 2.0)-1;
    boolean intoThis = false;
    split_child = children[mid];

    if(compare(entry.minKey(), split_child.minKey())<0){
      mid--;
      intoThis = true;
    }

    for (int i = mid+1; i < ksize; i++){
      if(firstChild==null){
        firstChild = children[i];
      }
      next.append(children[i]);
    }
    ksize = mid+1;
    if(intoThis){
      if(isFull()){ //check if min size met
        if (!next.isFull()) {
          next.shiftDown(0);
          BPNode tmp;
          if (children[ksize - 1].getType() == BPNode.LEAF) {
            tmp = new BPLeafNode(comparator, LeafSize);
          }
          else tmp = new BPGuideNode(comparator, num_keys,LeafSize);
          tmp = children[ksize - 1];
          next.putFirst(tmp);
          this.ksize--; //reduce size
          next.keys[0]=((BPNode)next.getItemAt(1)).minKey();
        }
      }
    append(entry);
    }else
      next.append(entry);

    return next;
  }

  /****************************************************************************
   *
   * print XML String
   ***************************************************************************/
  public void printXML(){

    System.out.println("<guide>");
    for(int i=0;i<ksize;i++){
        if(i>0){
          System.out.println("<key value=\""+keys[i-1].toString()+"\"/>");
        }
      children[i].printXML();
    }
    System.out.println("</guide>");

  }

  public void Print(String indent) {
          System.out.println(indent +'^');
          children[0].Print(indent + "\t");
          for (int i = 1; i < ksize; i++) {
                  System.out.println(indent +keys[i-1]);
                  children[i].Print(indent + '\t');
          }
          System.out.println(indent +'v');
  }



  public BPTree.Entry getMinRecord(){
    BPNode child =(BPNode) this.getItemAt(this.size()-1);

    while(child!=null && child.getType()!=BPNode.LEAF){
        child =(BPNode) child.getItemAt(0);
    }

    return child.getMinRecord();
  }


}
