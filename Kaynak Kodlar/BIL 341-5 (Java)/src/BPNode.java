
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
public interface BPNode {

  static byte GUIDE = 1;

  static byte LEAF  = 2;

   // returns comparator
   Comparator comparator();

   //specifies weather the node is full or not
   boolean isFull();

   //return the smallest key
   Object minKey();

   //return GUIDE OR LEAF
   int getType();

   //gets item at index
   // ****NOTE**** if its a guide node it returns the child at index
   // if its a leaf node it returns a record at index
   Object getItemAt(int index);

   //gets key at index
   Object getKeyAt(int index);

   //insert a new item
   BPNode put(BPTree.Entry entry);

   // return the occupied size
   int size();

   //shifts upwards
   BPNode shiftUp(int pos, int start);

   // fill factor
   int fillFactor();

   // remove
   BPNode remove(Object key);

   // decrease size
   void decreaseSize();

   // increase size
   void increaseSize();

   //shifts upwards
   void shiftDown(int pos);

   // append a child or record to the end
   void append(Object o);

   // puts something at the beginning of the children or records
   void putFirst(Object o);

   // return the max size, either keys or records
   int maxSize();

   // return the max key
   Object maxKey();

   // changes the size, used after shifts
   void modifySize(int new_size);

   //returns the rightest child, applies only to guide node
   BPNode getLastChild();

   //returns min record
   BPTree.Entry getMinRecord();


   //print XML String
   void printXML();
   void Print(String indent);


}
