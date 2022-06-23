
import java.util.*;


/*****************************************************************************
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
 ****************************************************************************/

public class BPLeafNode implements BPNode {
  private Comparator     comparator;
  private int            rsize;         // occupied keys
  private static int     num_records;  // number of records
  private BPTree.Entry[] records;      // records
  private BPGuideNode    GuideParent;

  /****************************************************************************
   * CONSTRUCTOR
   *
   * @param comp Comparator
   * @param n_recs int
   ***************************************************************************/

  public BPLeafNode(Comparator comp,int n_recs) {
    comparator  = comp;
    num_records = n_recs;
    records     = new BPTree.Entry[num_records];
    rsize       = 0;
    initPointers();
    GuideParent = null;
  }

  /****************************************************************************
   * CONSTRUCTOR
   *
   * @param o BPLeafNode
   ***************************************************************************/

  public BPLeafNode(BPLeafNode o) {
    comparator  = o.comparator;
    num_records = o.num_records;
    GuideParent = o.GuideParent;
    records     = new BPTree.Entry[num_records];
    rsize       = o.rsize;
    initPointers();
    for(int i=0;i<rsize;i++){
      copyRecord(i,o.records[i]);
    }
    GuideParent = null;
  }


  /****************************************************************************
   *
   * @return int
   * return GUIDE OR LEAF
   ***************************************************************************/
  public int getType(){
     return BPNode.LEAF;
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
   * @return Object
   * return the max key
   ***************************************************************************/
  public Object maxKey(){
    return records[rsize-1].getKey();
  }


  /****************************************************************************
   *
   * @return boolean
   * specifies weather the node is full or not
   ***************************************************************************/
  public boolean isFull(){
    return num_records==rsize;
  }


  /****************************************************************************
   *
   * @param index int
   * @return Object
   * gets child at index
   ***************************************************************************/
  public Object getItemAt(int index){
     return records[index];
   }


   /****************************************************************************
    *
    * @param index int
    * @return Object
    * gets key at index
    ***************************************************************************/
   public Object getKeyAt(int index){
      return records[index].getKey();
   }

   /****************************************************************************
    *
    * @return int
    * return the size of the occupied
    ***************************************************************************/

   public int size(){
     return rsize;
   }


   /****************************************************************************
    *
    * @return Object
    * return the smallest key
    ***************************************************************************/
   public Object minKey(){

     return records[0].getKey();
   }


   /****************************************************************************
    *
    * @param new_size int
    * changes the size, used after shifts
    ***************************************************************************/
   public void modifySize(int new_size){
     rsize = new_size;
   }

   /****************************************************************************
    *
    * @return int
    * return the max size, either keys or records
    ***************************************************************************/
   public int maxSize(){
     return num_records;
   }


   /****************************************************************************
    *
    * @return int
    * fill factor
    ***************************************************************************/
   public int fillFactor(){
     return (num_records+1)/2;
  }


  /****************************************************************************
   * decrease size
   ***************************************************************************/
  public void decreaseSize(){
    rsize--;
  }


  /****************************************************************************
   * increase size
   ***************************************************************************/
  public void increaseSize(){
    rsize++;
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
     BPNode ret_node=null;

     if(!this.isFull()){
       //entry.parent = this;
       insertNext(entry);
     }else{
       ret_node = split(entry);
       //records[num_records-1].setRight((TRecord)ret_node.getItemAt(0));
     }

     return ret_node;
   }


   /****************************************************************************
    *
    * @return BPNode
    * returns the rightest child, applies only to guide node
    ***************************************************************************/
   public BPNode getLastChild(){
     return null;
   }


  /****************************************************************************
   *
   * @param entry Entry
   *
   * inserts the record in the appropriate position since there is
   * space in this node without splitting
   ***************************************************************************/
  private void insertNext(BPTree.Entry entry){
    boolean done = false;

      for (int i = 0; i < rsize; i++){
        if (compare(entry.getKey(), records[i].getKey()) < 0) {
          for (int j = rsize; j > i; j--) {
            copyRecord(j,records[j-1]);
          }
          copyRecord(i,entry);
          done = true;
          break;
        }
    }

    if (!done){
      copyRecord(rsize,entry);
    }
    rsize++;
  }


  /****************************************************************************
   *
   * @param o Object
   *  append a child or record to the end
   ***************************************************************************/
  public void append(Object o){
     //Object key = ((BPTree.Entry)o).getKey();

     copyRecord(rsize,(BPTree.Entry)o);
     rsize++;
   }


   /****************************************************************************
    *
    * @param o Object
    *  puts something at the beginning of the children or records
    ***************************************************************************/
   public void putFirst(Object o){
     copyRecord(0,(BPTree.Entry)o);
   }


   /****************************************************************************
    *
    * @param pos int
    * shift the records downwards
    ***************************************************************************/
   public void shiftDown(int pos){

     for(int i=rsize;i>pos;i--){
       copyRecord(i,records[i-1]);
     }

    rsize = rsize +1;

   }


   /****************************************************************************
    *
    * @param pos int
    * @param start int
    * @return BPNode
    * shift the records upwards (TO THE LEFT)
    ***************************************************************************/
   public BPNode shiftUp(int pos, int start){
    int p=pos-1;

    for(int i=pos;i<rsize;i++){
      copyRecord(p++,records[i]);
    }

    rsize = rsize - 1;
    return null;
  }


  /****************************************************************************
   *
   * @param key Object
   * @return BPNode
   * REMOVE A RECORD AND THEN ORGANIZE
   ***************************************************************************/
  public BPNode remove(Object key){
    int idx = binarySearch(key);

    if(idx==0){ //first index in record set
      shiftUp(1,0);
    }else if(idx == rsize-1){//last index in record set
      rsize--; //just change the size
    }else if(idx !=-1){//somewhere in the middle
      shiftUp(idx+1,0);
    }

    return null;

  }


   /****************************************************************************
    *
    * @param entry Entry
    * @return BPLeafNode
    * SPLIT FUNCTION
    * find the middle, add it including the entry if it is greater than the
    * middle, else add it to this recordset
    * also insert the middle into the guide that called this.put
    ***************************************************************************/
   private BPLeafNode split(BPTree.Entry entry){
    BPLeafNode next = new BPLeafNode(comparator,num_records);
    int min_size;

    int mid = (rsize+1) / 2;
    min_size = mid;

    for(int i=mid;i<rsize;i++){
      next.put(records[i]);//null because it cant be full yet
    }

    rsize = mid;

    if(compare(entry.getKey(),next.minKey())<0){
      boolean done = false;
      if(rsize>=min_size && next.size()<min_size){ //check if min size met
        if(compare(records[rsize-1].getKey(),entry.getKey())<0){
          //check to see if new entry is larger than the last in this
          next.put(entry);
          done= true;
        }else{
          next.shiftDown(0);
          BPTree.Entry tmp = new BPTree.Entry(records[rsize - 1].getKey(),
                                    records[rsize - 1].getValue());
          next.putFirst(tmp);
          this.rsize--; //reduce size

        }
      }
      if(!done)
          this.put(entry); // null once again, it cant be full
    }else{
      next.put(entry);

    }

    next.records[num_records-1].right=records[num_records-1].right;
    records[num_records-1].setRight((BPTree.Entry)next.getMinRecord());
    next.records[0].setLeft(records[num_records-1]);
    return next;
  }


   /****************************************************************************
    * Object initPointers();
    * initializes internal pointers
    ***************************************************************************/
   public void initPointers(){

      for(int i = 0;i<num_records;i++){
        records[i]=new BPTree.Entry();
        records[i].rec_index = i;
        if(i>0){
          records[i-1].setRight(records[i]);
          records[i].setLeft(records[i-1]);
        }
      }
  }

  /****************************************************************************
   *
   * @param to int
   * @param from Entry
   * sets the value of a record in the array to the value in "from" param
   ***************************************************************************/
  public void copyRecord(int to, BPTree.Entry from){

    records[to].setValue(from.getValue());
    records[to].setKey(from.getKey());
    records[to].parent = this;
  }


  /****************************************************************************
   *
   * @param key Object
   * @return Object
   *  return true if contains key
   ***************************************************************************/
  public Object containsKey(Object key){
     BPTree.Entry ret=null;
     int idx;

     if((idx=binarySearch(key))!=-1){
       ret = records[idx];
     }

     return ret;
  }


  /****************************************************************************
   *
   * @return Object
   * return the smallest record in the set
   ***************************************************************************/
  public  Object getMaxRecord(){
    return records[rsize-1];
  }


  /****************************************************************************
   *
   * @return .Entry
   * return the smallest record in the set
   ***************************************************************************/
  public  BPTree.Entry getMinRecord(){
    return records[0];
  }


  /****************************************************************************
   *
   * print XML String
   ***************************************************************************/
  public void printXML(){
    System.out.println("<leaf>");
    for(int i=0;i<rsize;i++){
      System.out.println(records[i].toString());
    }
    System.out.println("</leaf>");

  }

  /****************************************************************************
   *
   * @param o Object
   * @return int
   * simple binary search on the records
   ***************************************************************************/
  private int binarySearch( Object o){
    int start, end, midPt;

    start = 0;
    end = rsize-1;

    while (start <= end) {
        midPt = (start + end) / 2;
        if (compare(records[midPt].getKey(), o)==0) {
            return midPt;
        }
        else if (compare(records[midPt].getKey(), o)<0) {
            start = midPt + 1;
        }
        else {
            end = midPt - 1;
        }
    }
    return -1;
  }



// TEST PRINTER
  public void Print(String indent) {
          System.out.print(indent +'[');
          for (int i = 0; i < rsize - 1; i++) {
                  records[i].Print();
                  System.out.print(" ,");
          }
          records[rsize-1].Print();
          System.out.println(indent +']');
  }
}
