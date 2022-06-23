
import java.util.*;

/******************************************************************************
 * <p>Title: CMSC420 </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: </p>
 * @author Alexios Aliagas
 * @version 1.0
 * EMAIL : ale3hs@aliagas.gr
 *****************************************************************************/

public class BPTree implements SortedMap,java.io.Serializable {

  class IllegalOrderException extends Exception {
    IllegalOrderException(int order){
      super("Illegal order ("+order+") for B+ tree");
    }
  }
  class IllegalLeafSizeException extends Exception {
    IllegalLeafSizeException(int leafSize){
      super("Illegal leaf size ("+leafSize+") for B+ tree");
    }
  }

  private int num_keys;
  private int m_order;

  //private transient BPNode iNode = null; //iteration node
  private Comparator comparator = null;
  private transient BPNode root = null;
  /**
   * The number of entries in the tree
   */
  private transient int bp_size = 0;
  private transient int LeafSize;

  /**
   * The number of structural modifications to the tree.
   */
  private transient int modCount = 0;

  private void incrementSize()   { modCount++; bp_size++; }
  private void decrementSize()   { modCount++; bp_size--; }

  /******************************************************************************
   * CONSTRUCTOR
   * @param comp Comparator
   * @param order int
   * @param leafSize int
   ****************************************************************************/
  public BPTree(Comparator comp, int order,int leafSize){
    num_keys    = order;

    if(comp==null)
    this.comparator=new Comparator(){
        public int compare(Object o1, Object o2){
            Comparable c1 = (Comparable)o1;
            return c1.compareTo(o2);
          }
        };
    else comparator = comp;

    /*if(order<3) throw new IllegalOrderException(order);
    if(leafSize<order) throw new IllegalLeafSizeException(leafSize);*/

    m_order     = order;
    LeafSize    = leafSize;
  }


  /******************************************************************************
   * CONSTRUCTOR
   * @param order int
   * @param leafSize int
   ****************************************************************************/
  public BPTree(int order,int leafSize){
     this(null,order,leafSize);
  }


  /****************************************************************************
   *
   * @return int
   * return sizeof bptree
   ***************************************************************************/
  public int size(){
    return bp_size;
  }

  /****************************************************************************
   *
   * @return boolean
   * return if tree is empty
   ***************************************************************************/
  public boolean isEmpty(){

    return root == null;
  }

  /****************************************************************************
   * clear the bptree
   ***************************************************************************/
  public void clear(){
    root    = null;
    bp_size = 0;
  }

  /****************************************************************************
   *
   * @param key Object
   * @return boolean
   * check if tree contains Key key
   ***************************************************************************/
  public boolean containsKey(Object key){
     BPNode node   = root;
     while (node!=null) {
         int i = 0;
         if(node.getType() == BPNode.LEAF ){
             return ((BPLeafNode)node).containsKey(key)!=null;
         }
         for (; i<node.size()-1; i++) {
             if (compare(key,node.getKeyAt(i))==0) {
                 return true;
             } else if (compare(key,node.getKeyAt(i))<=0) {
                 break;
             }
         }
         node   = (BPNode) node.getItemAt(i);
         if(node.getType() == BPNode.LEAF){
             return ((BPLeafNode)node).containsKey(key)!=null;
         }
     }

      return false;
   }

   /****************************************************************************
    *
    * @param value Object
    * @return boolean
    * check if tree contains Value value
    ***************************************************************************/
   public boolean containsValue(Object value){
      Entry eRoot= this.firstEntry();
      return (eRoot==null ? false :
              (value==null ? valueSearchNull(eRoot)
                           : valueSearchNonNull(eRoot, value)));
    }

    /**************************************************************************
     *
     * @param n Entry
     * @param value Object
     * @return boolean
     *************************************************************************/
    private boolean valueSearchNull(Entry n) {
        if (n.getValue() == null)
            return true;

        // Check right trees for value
        return n.right != null && valueSearchNull(n.right);
    }

    /**************************************************************************
     *
     * @param n Entry
     * @param value Object
     * @return boolean
     *************************************************************************/
    private boolean valueSearchNonNull(Entry n, Object value) {
        // Check this node for the value
        if (value.equals(n.getValue()))
            return true;

        // Check right tress for value
        return n.right != null && valueSearchNonNull(n.right, value);
    }


  /*****************************************************************************
  * values
  * @return Collection
  *****************************************************************************/
   transient volatile Collection values = null;
    public Collection values() {
      if (values == null) {
          values = new AbstractCollection() {
              public Iterator iterator() {
                  throw new UnsupportedOperationException("Implement This");
              }

              public int size() {
                  throw new UnsupportedOperationException("Implement This");
              }

              public boolean contains(Object o) {
                  throw new UnsupportedOperationException("Implement This");
              }

              public boolean remove(Object o) {
                  throw new UnsupportedOperationException("Implement This");
              }

              public void clear() {
                  throw new UnsupportedOperationException("Implement This");
              }
          };
      }
      return values;

    }

  /****************************************************************************
      putAll(Map t)
      Copies all of the mappings from the specified map to bptree
  ****************************************************************************/
  public void putAll(Map t){
    Iterator i = t.entrySet().iterator();
    while (i.hasNext()) {
        Entry e = (Entry) i.next();
        put(e.getKey(), e.getValue());
    }
  }

 /****************************************************************************
  * Returns a Set view of the keys contained in this map.  The set's
  * iterator will return the keys in ascending order.  The map is backed by
  * this <tt>BPTree</tt> instance, so changes to this map are reflected in
  * the Set, and vice-versa.  The Set supports element removal, which
  * removes the corresponding mapping from the map, via the
  * <tt>Iterator.remove</tt>, <tt>Set.remove</tt>, <tt>removeAll</tt>,
  * <tt>retainAll</tt>, and <tt>clear</tt> operations.  It does not support
  * the <tt>add</tt> or <tt>addAll</tt> operations.
  *
  * @return a set view of the keys contained in this BPTree.
  ***************************************************************************/
 transient volatile Set        keySet = null;
 public Set keySet() {
     if (keySet == null) {
         keySet = new AbstractSet() {
             public Iterator iterator() {
                 throw new UnsupportedOperationException("Implement This");
             }

             public int size() {
                 throw new UnsupportedOperationException("Implement This");
             }

             public boolean contains(Object o) {
                 throw new UnsupportedOperationException("Implement This");
             }

             public boolean remove(Object o) {
                 throw new UnsupportedOperationException("Implement This");
             }

             public void clear() {
                 throw new UnsupportedOperationException("Implement This");
             }
         };
     }
     return keySet;
 }


  /****************************************************************************
  *    Object get(Object key)
  *    Returns the value to which this map maps the specified key.
  ****************************************************************************/
  public Object get(Object key){
      Entry p = getEntry(key);
      return (p==null ? null : p.getValue());
  }

  /****************************************************************************
  *    Object remove(Object key)
  *    Removes the mapping for this key from this map if it is present
  ****************************************************************************/
  public Object remove(Object key){
    if(this.isEmpty()) return null;

   BPNode tmp = root.remove(key);
   if(tmp!=null){
    root=tmp;
  }
    decrementSize();
   if(this.bp_size==0){
     root = null;
   }

    return new Object();
  }

  /****************************************************************************
      Object put(Object key,Object value)
      Associates the specified value with the specified key in this map
  ****************************************************************************/
  public Object put(Object key, Object value){
    Entry rec = new Entry();
    BPNode newNode = null;
    rec.setKey(key);
    rec.setValue(value);

    if(root==null){
      root = new BPLeafNode(comparator,LeafSize);
    }
    newNode = root.put(rec);

    if(newNode!=null){
      BPGuideNode nw = new BPGuideNode(comparator,num_keys,LeafSize);
      nw.append(root);
      nw.append(newNode);
      root = nw;
    }

    incrementSize();
    if(newNode==null)
      return root;
    else
      return newNode;

  }

  /****************************************************************************
   *   Object firstKey()
   *   Returns the first (lowest) key currently in this sorted map
   ****************************************************************************/
  public Object firstKey(){
    return firstEntry().getKey();
  }

  /****************************************************************************
  *   Object lastKey()
  *    Returns the last (highest) key currently in this sorted map
  ****************************************************************************/
  public Object lastKey(){
    return lastEntry().getKey();
  }

  /****************************************************************************
   *   Comparator comparator()
   *   Returns the comparator associated with this sorted map, or null if it
   *   uses its keys' natural ordering.
   ****************************************************************************/
  public Comparator comparator(){
    return comparator;
  }

 /****************************************************************************
  *
  * @param toKey Object
  * @return SortedMap
  * Returns a view of the portion of this sorted map whose keys are strictly
  * less than toKey
  ***************************************************************************/
 public SortedMap headMap(Object toKey){
     return new SubMap(toKey, true);
  }

  /****************************************************************************
   *
   * @param toKey Object
   * @return SortedMap
   * Returns a view of the portion of this sorted map whose keys are greater
   * than or equal to fromKey
   ***************************************************************************/
  public SortedMap tailMap(Object fromKey){
      return new SubMap(fromKey, false);
  }


 /****************************************************************************
  *
  * @param toKey Object
  * @return SortedMap
  * Returns a view of the portion of this sorted map whose keys range from
  * fromKey, inclusive, to toKey, exclusive.
  ***************************************************************************/
  public SortedMap subMap(Object fromKey, Object toKey){
    return new SubMap(fromKey, toKey);
  }


  /****************************************************************************
  *     Entry getEntry(Object key)
  *    Returns an entry from the BPTree based on the key
  ****************************************************************************/
  private Entry getEntry(Object key) {
    BPNode curNode = root;
    int i,cmp;

    while (curNode != null){
      if (curNode.getType() == BPNode.LEAF ) {
         return (Entry)((BPLeafNode)curNode).containsKey(key);
       }
      else {
        for (i = 0; i < curNode.size(); i++) {

          cmp = compare(key,curNode.getKeyAt(i));
          if (cmp < 0) {
            curNode = (BPNode)curNode.getItemAt(i);
            break;
          }else if(cmp==0){
            curNode = (BPNode)curNode.getItemAt(i+1);
            break;
          }else if(i+1==curNode.size()-1){
            curNode = (BPNode)curNode.getItemAt(i+1);
            break;
          }
        }

      }
    }
    return null;
    }

  /*****************************************************************************
  * Returns the height of the bptree
  *****************************************************************************/
    private int getHeight() {
        BPNode p  = root;
        int height = 0;
        if(p.getType() == BPNode.LEAF)
           return 1;
        if (p != null)
            while(p.getItemAt(0)!= null){
             height++;
             if(p.getType() == BPNode.LEAF) break;
             p = (BPNode)p.getItemAt(0);
            }
        return height;
    }

    /**************************************************************************
     * Returns the first Entry in the BPTree (according to the BPTree's
     * key-sort function).  Returns null if the BPTree is empty.
     **************************************************************************/
    private Entry firstEntry() {
        BPNode p  = root;
        Entry   rec = null;
        if(p.getType() == BPNode.LEAF) //if its a leaf get minKey MAY ONLY BE ONE NODE SO ITS A LEAF
           rec = (Entry)((BPLeafNode)p).getMinRecord();
        if (p != null)
            while(p.getItemAt(0)!= null && rec==null){
              if(p.getType() == BPNode.LEAF){ //if its a leaf get minKey
                rec = (Entry)((BPLeafNode)p).getMinRecord();
              }else p = (BPNode)p.getItemAt(0);
            }
        return rec;
    }

    /**************************************************************************
     * Returns the last Entry in the BPTree , Returns null if the BPTree is empty.
     *************************************************************************/
    private Entry lastEntry(){
      Iterator i = entrySet().iterator();
      Entry prev=null,e=null;
      while (i.hasNext()) {
           prev = e;
           e = (Entry) i.next();
      }

      return prev;

    }

    /**************************************************************************
     * Test two values  for equality.  Differs from o1.equals(o2) only in
     * that it copes with with <tt>null</tt> o1 properly.
     *************************************************************************/
    private static boolean valEquals(Object o1, Object o2) {
        return (o1==null ? o2==null : o1.equals(o2));
    }


    /**************************************************************************
     * Compares the specified object with this map for equality.  Returns
     * <tt>true</tt> if the given object is also a map and the two maps
     * represent the same mappings.  More formally, two maps <tt>t1</tt> and
     * <tt>t2</tt> represent the same mappings if
     * <tt>t1.keySet().equals(t2.keySet())</tt> and for every key <tt>k</tt>
     * in <tt>t1.keySet()</tt>, <tt> (t1.get(k)==null ? t2.get(k)==null :
     * t1.get(k).equals(t2.get(k))) </tt>.  This ensures that the
     * <tt>equals</tt> method works properly across different implementations
     * of the map interface.<p>
     *
     * This implementation first checks if the specified object is this map;
     * if so it returns <tt>true</tt>.  Then, it checks if the specified
     * object is a map whose size is identical to the size of this set; if
     * not, it it returns <tt>false</tt>.  If so, it iterates over this map's
     * <tt>entrySet</tt> collection, and checks that the specified map
     * contains each mapping that this map contains.  If the specified map
     * fails to contain such a mapping, <tt>false</tt> is returned.  If the
     * iteration completes, <tt>true</tt> is returned.
     *
     * @param o object to be compared for equality with this map.
     * @return <tt>true</tt> if the specified object is equal to this map.
     *************************************************************************/
    public boolean equals(Object o) {
        if (o == this)
            return true;

        if (!(o instanceof Map))
            return false;
        Map t = (Map) o;
        if (t.size() != size())
            return false;

        try {
            Iterator i = entrySet().iterator();
            while (i.hasNext()) {
                Entry e = (Entry) i.next();
                Object key   = e.getKey();
                Object value = e.getValue();
                if (value == null) {
                    if (!(t.get(key)==null && t.containsKey(key)))
                        return false;
                } else {
                    if (!value.equals(t.get(key)))
                        return false;
                }
            }
        } catch(ClassCastException unused)   {
            return false;
        } catch(NullPointerException unused) {
            return false;
        }

        return true;
    }

    /*************************************************************************
     * Returns the successor of the specified Entry, or null if no such.
     *************************************************************************/
    private Entry successor(Entry t) {
      Entry tmp_rec   =  (Entry)t;
      BPNode tmp_parent = tmp_rec.parent;
      //get the first record in the next leaf node if applicable
      if(tmp_rec.rec_index >=tmp_parent.size()-1){
        tmp_rec=(Entry)tmp_parent.getItemAt(tmp_parent.maxSize()-1);
        tmp_parent = tmp_rec.parent;
      }

      return tmp_rec.getRight();
    }

    /**************************************************************************
     * PrintXML outputs the tree in XML format
     *
     *************************************************************************/

    public void printXML(){
      System.out.println("<bptree cardinality=\""+bp_size+"\" height=\""
       +getHeight()+"\" order=\""+m_order+"\" leafSize=\""+LeafSize +"\">");
      root.printXML();
      System.out.println("</bptree>");
    }

    /**************************************************************************
     * Prints the keys in xml
     *
     *************************************************************************/
    public void printKeysXML(){
      Iterator iter = BPTree.this.entrySet().iterator();
      while ( iter.hasNext() ) {
          System.out.println("<BPTree.Entry.Key value=\""+((BPTree.Entry)iter.next()).key+"\"/>");
      }
    }

    /**************************************************************************
     * Prints the keys in xml
     *
     *************************************************************************/
    public void printKeys(){
      Iterator iter = BPTree.this.entrySet().iterator();
      while ( iter.hasNext() ) {
          System.out.print(((BPTree.Entry)iter.next()).key+" ");
      }
      System.out.println();
    }


    /**************************************************************************
     * Prints the keys in xml
     *
     *************************************************************************/
    public void printValuesXML(){
      Iterator iter = BPTree.this.entrySet().iterator();
      while ( iter.hasNext() ) {
          System.out.println("<BPTree.Entry.Value value=\""+((BPTree.Entry)iter.next()).data+"\"/>");
      }
    }


   // just for testing
    void Print() {
            if (root.size()>0 ) {
                    root.Print("");
            }
  }
  /****************************************************************************
  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
                           CLASS ENTRY
  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  ****************************************************************************/
 // Views

 /**
  * This field is initialized to contain an instance of the entry set
  * view the first time this view is requested.  The view is stateless,
  * so there's no reason to create more than one.
  */
 private transient volatile Set entrySet = null;

 /**
  * Returns a set view of the mappings contained in this map.  The set's
  * iterator returns the mappings in ascending key order.  Each element in
  * the returned set is a <tt>Map.Entry</tt>.  The set is backed by this
  * map, so changes to this map are reflected in the set, and vice-versa.
  * The set supports element removal, which removes the corresponding
  * mapping from the BPTree, through the <tt>Iterator.remove</tt>,
  * <tt>Set.remove</tt>, <tt>removeAll</tt>, <tt>retainAll</tt> and
  * <tt>clear</tt> operations.  It does not support the <tt>add</tt> or
  * <tt>addAll</tt> operations.
  *
  * @return a set view of the mappings contained in this map.
  * @see Map.Entry
  */
 public Set entrySet() {
     if (entrySet == null) {
         entrySet = new AbstractSet() {
             public Iterator iterator() {
                 return new EntryIterator();
             }

             public boolean contains(Object o) {
                 if (!(o instanceof Entry))
                     return false;
                 Entry entry = (Entry)o;
                 Object value = entry.getValue();
                 Entry p = getEntry(entry.getKey());
                 return p != null && valEquals(p.getValue(), value);
             }

             public boolean remove(Object o) {
                 if (!(o instanceof Entry))
                     return false;
                 Entry entry = (Entry)o;
                 Object value = entry.getValue();
                 Entry p = getEntry(entry.getKey());
                 if (p != null && valEquals(p.getValue(), value)) {
                     BPTree.this.remove(p);
                     return true;
                 }
                 return false;
             }

             public int size() {
                 return BPTree.this.size();
             }

             public void clear() {
                 BPTree.this.clear();
             }
         };
     }
     return entrySet;
 }


 private class ValueIterator extends EntryIterator {

   /***************************************************************************
    * next()
    * @return Object
    **************************************************************************/
   public Object next() {
     return nextEntry().getValue();
    }
  }

  private class KeyIterator extends EntryIterator {
      public Object next() {
          return nextEntry().key;
      }
  }

  /****************************************************************************
  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
                         CLASS BPTREE.ENTRY
  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  ****************************************************************************/


  static class Entry implements Map.Entry {
    private Object  key;
    private Object  data;
    private Entry   left;
    public  Entry   right;
    public  BPNode  parent = null;
    public  int     rec_index = 0;


    /****************************************************************************
        Constructor
     ****************************************************************************/
    public Entry() {
      key   = new Object();
      data  = new Object();
      left  = null;
      right = null;
    }


    public void nullPtrs(){
      left = right = null;
    }

    /****************************************************************************
       Constructor TRecord(Object dataKey, Object dataType)
    ****************************************************************************/

    public Entry(Object dataKey, Object dataType){

      key  = dataKey;
      data = dataType;

    }
        /**
         * Returns the key corresponding to this entry.
         *
         * @return the key corresponding to this entry.
         */
        public Object getKey(){
          return key;
        }

        public Object setKey(Object val){
          Object old = new Object();
          old = key;
          key = val;
          return old;
        }


        /**
         * Returns the value corresponding to this entry.  If the mapping
         * has been removed from the backing map (by the iterator's
         * <tt>remove</tt> operation), the results of this call are undefined.
         *
         * @return the value corresponding to this entry.
         */
        public Object getValue(){
          return data;
        }

        /**
         * Replaces the value corresponding to this entry with the specified
         * value (optional operation).  (Writes through to the map.)  The
         * behavior of this call is undefined if the mapping has already been
         * removed from the map (by the iterator's <tt>remove</tt> operation).
         *
         * @param value new value to be stored in this entry.
         * @return old value corresponding to the entry.
         *
         * @throws UnsupportedOperationException if the <tt>put</tt> operation
         *	      is not supported by the backing map.
         * @throws ClassCastException if the class of the specified value
         * 	      prevents it from being stored in the backing map.
         * @throws    IllegalArgumentException if some aspect of this value
         *	      prevents it from being stored in the backing map.
         * @throws NullPointerException the backing map does not permit
         *	      <tt>null</tt> values, and the specified value is
         *	      <tt>null</tt>.
         */
      public Object setValue(Object val){
          Object old = new Object();
          old = data;
          data = val;
          return old;
      }

        /**
         * Compares the specified object with this entry for equality.
         * Returns <tt>true</tt> if the given object is also a map entry and
         * the two entries represent the same mapping.  More formally, two
         * entries <tt>e1</tt> and <tt>e2</tt> represent the same mapping
         * if<pre>
         *     (e1.getKey()==null ?
         *      e2.getKey()==null : e1.getKey().equals(e2.getKey()))  &&
         *     (e1.getValue()==null ?
         *      e2.getValue()==null : e1.getValue().equals(e2.getValue()))
         * </pre>
         * This ensures that the <tt>equals</tt> method works properly across
         * different implementations of the <tt>Map.Entry</tt> interface.
         *
         * @param o object to be compared for equality with this map entry.
         * @return <tt>true</tt> if the specified object is equal to this map
         *         entry.
         */
        public boolean equals(Object o){
          return true;
        }

        /**
         * Returns the hash code value for this map entry.  The hash code
         * of a map entry <tt>e</tt> is defined to be: <pre>
         *     (e.getKey()==null   ? 0 : e.getKey().hashCode()) ^
         *     (e.getValue()==null ? 0 : e.getValue().hashCode())
         * </pre>
         * This ensures that <tt>e1.equals(e2)</tt> implies that
         * <tt>e1.hashCode()==e2.hashCode()</tt> for any two Entries
         * <tt>e1</tt> and <tt>e2</tt>, as required by the general
         * contract of <tt>Object.hashCode</tt>.
         *
         * @return the hash code value for this map entry.
         * @see Object#hashCode()
         * @see Object#equals(Object)
         * @see #equals(Object)
         */
        public int hashCode(){
          int keyHash = (key==null ? 0 : key.hashCode());
          int valueHash = (data==null ? 0 : data.hashCode());
          return keyHash ^ valueHash;
        }




    public void Print(){
      System.out.print(data);
    }

    /****************************************************************************
         Object getLeftLeaf();
        return the left leaf
     ****************************************************************************/
    public  Entry getLeft(){
      return left;
    }

    /****************************************************************************
         Object getRightLeaf();
        return the right leaf
     ****************************************************************************/
    public  Entry getRight(){
      return right;
    }

    /****************************************************************************
         Object setLeftLeaf();
        sert the left leaf
     ****************************************************************************/
    public  void setLeft(Entry node){
       left = node;
    }

    /****************************************************************************
         Object setRightLeaf();
        set the right leaf
     ****************************************************************************/
    public void setRight(Entry node){
       right = node;
    }


    public String toString(){
      return "<entry key=\""+key +"\" value=\""+data.toString()+"\"/>";
    }

  }

  /****************************************************************************
   *
   * @param e Entry
   * @return Object
   * Returns the key corresonding to the specified Entry.  Throw
   * NoSuchElementException if the Entry is <tt>null</tt>.
   *
   ***************************************************************************/

  private static Object key(Entry e) {
      if (e==null)
          throw new NoSuchElementException();
      return e.key;
  }


  /****************************************************************************
  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
                         CLASS ENTRYITERATOR
  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  ****************************************************************************/

 private class EntryIterator implements Iterator {
     private int expectedModCount = BPTree.this.modCount;
     private Entry lastReturned = null;
     Entry next;

     /*************************************************************************
      * return first entry in constructor
      *************************************************************************/
     EntryIterator() {
         next = firstEntry();
     }
     /**************************************************************************
      *
      * @param first Entry
      * CONTRUCTOR param with first entry, specifies the first entry
      *************************************************************************/
     // Used by SubMapEntryIterator
     EntryIterator(Entry first) {
         next = first;
     }
     /**************************************************************************
      *
      * @return boolean
      * specifies whether or not there exist more items to iterate through
      *************************************************************************/
     public boolean hasNext() {
         return next != null;
     }

     /**************************************************************************
      *
      * @return Entry
      * get the next item
      *************************************************************************/
     final Entry nextEntry() {
         if (next == null)
             throw new NoSuchElementException();
         if (modCount != expectedModCount)
             throw new ConcurrentModificationException();
         lastReturned = next;
         next = successor(next);
         return lastReturned;
     }

     /**************************************************************************
      *
      * @return Object
      * call the above function
      *************************************************************************/
     public Object next() {
         return nextEntry();
     }
     /**************************************************************************
      *
      *
      * call BPTree remove
      *************************************************************************/
     public void remove() {
       throw new UnsupportedOperationException("Implement This");
     }

    }


    /**************************************************************************
     *
     * @param k1 Object
     * @param k2 Object
     * @return int
     * Compares two keys using the correct comparison method for this BPTree.
     *************************************************************************/
    private int compare(Object k1, Object k2) {
        return (comparator==null ? ((Comparable)k1).compareTo(k2)
                                 : comparator.compare(k1, k2));
    }


    /****************************************************************************
    &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
                                    SUBMAP
    &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    ****************************************************************************/

    private class SubMap extends AbstractMap
                             implements SortedMap, java.io.Serializable {

        /**
         * fromKey is significant only if fromStart is false.  Similarly,
         * toKey is significant only if toStart is false.
         */
        private boolean fromStart = false, toEnd = false;
        private Object  fromKey,           toKey;

        /**********************************************************************
         * CONSTRUCTOR
         * @param fromKey Object
         * @param toKey Object
         ***********************************************************************/
        SubMap(Object fromKey, Object toKey) {
            throw new UnsupportedOperationException("Implement This");
        }
        /************************************************************************
         * CONSTRUCTOR
         * @param key Object
         * @param headMap boolean
         ***********************************************************************/
        SubMap(Object key, boolean headMap) {
            throw new UnsupportedOperationException("Implement This");
        }
        /************************************************************************
         * CONSTRUCTOR
         * @param fromStart boolean
         * @param fromKey Object
         * @param toEnd boolean
         * @param toKey Object
         ***********************************************************************/
        SubMap(boolean fromStart, Object fromKey, boolean toEnd, Object toKey){
            throw new UnsupportedOperationException("Implement This");
        }
        /************************************************************************
         *
         * @return boolean
         * return if set is empty
         ***********************************************************************/
        public boolean isEmpty() {
            throw new UnsupportedOperationException("Implement This");
        }
        /************************************************************************
         *
         * @param key Object
         * @return boolean
         * checks range, then checks b+tree if the key exists;
         ***********************************************************************/
        public boolean containsKey(Object key) {
            throw new UnsupportedOperationException("Implement This");
        }
        /************************************************************************
         *
         * @param key Object
         * @return Object
         * again, checks the range, then the tree
         ***********************************************************************/
        public Object get(Object key) {
           throw new UnsupportedOperationException("Implement This");
        }
        /************************************************************************
         *
         * @param key Object
         * @param value Object
         * @return Object
         * inserts a new value
         ***********************************************************************/
        public Object put(Object key, Object value) {
            throw new UnsupportedOperationException("Implement This");
        }

        /************************************************************************
         *
         * @return Comparator
         ***********************************************************************/
        public Comparator comparator() {
           throw new UnsupportedOperationException("Implement This");
        }
        /************************************************************************
         *
         * @return Object
         * get the first key,
         ***********************************************************************/
        public Object firstKey() {
            throw new UnsupportedOperationException("Implement This");
        }
        /************************************************************************
         *
         * @return Object
         * get the last key
         ***********************************************************************/
        public Object lastKey() {
            throw new UnsupportedOperationException("Implement This");
        }
        /************************************************************************
         * SUBMAP ENTRYSET
         ***********************************************************************/
        private transient Set entrySet = new EntrySetView();
        /************************************************************************
         *
         * @return Set
         ***********************************************************************/
        public Set entrySet() {
            throw new UnsupportedOperationException("Implement This");
        }
        /************************************************************************
         *  CLASS ENtry SEt View
         * <p>Title: CMSC420 PROJ2</p>
         * <p>Description: </p>
         * <p>Copyright: Copyright (c) 2004</p>
         * <p>Company: </p>
         * @author Alexios Aliagas fmh20055
         * @version 1.0
         ***********************************************************************/
        private class EntrySetView extends AbstractSet {
            private transient int size = -1, sizeModCount;
            /*****************************************************************
             *
             * @return int
             ******************************************************************/
            public int size() {
                throw new UnsupportedOperationException("Implement This");
            }
            /*******************************************************************
             *
             * @return boolean
             * return if empty
             ******************************************************************/

            public boolean isEmpty() {
                throw new UnsupportedOperationException("Implement This");
            }
            /*******************************************************************
             *
             * @param o Object
             * @return boolean
             * checks if the submap contains the object
             ******************************************************************/
            public boolean contains(Object o) {
                throw new UnsupportedOperationException("Implement This");
            }
            /*******************************************************************
             *
             * @param o Object
             * @return boolean
             * remove object
             ******************************************************************/
            public boolean remove(Object o) {
               throw new UnsupportedOperationException("Implement This");
            }
            /*******************************************************************
             *
             * @return Iterator
             *
             * return a submap iterator
             ******************************************************************/
            public Iterator iterator() {
                throw new UnsupportedOperationException("Implement This");
            }
        }

        /*******************************************************************
         *
         * @param fromKey Object
         * @param toKey Object
         * @return SortedMap
         *
         * return a sorted map fromKey toKey
         ******************************************************************/
        public SortedMap subMap(Object fromKey, Object toKey) {
            throw new UnsupportedOperationException("Implement This");
        }

        /*******************************************************************
         *
         * @param toKey Object
         * @return SortedMap
         * return a sorted map from head toKey
         ******************************************************************/
        public SortedMap headMap(Object toKey) {
            throw new UnsupportedOperationException("Implement This");
        }
        /*******************************************************************
         *
         * @param fromKey Object
         * @return SortedMap
         * return a sorted map fromkey toTail
         ******************************************************************/
        public SortedMap tailMap(Object fromKey) {
            throw new UnsupportedOperationException("Implement This");
        }

    }



    /****************************************************************************
    &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
                             SubMapEntryIterator
    &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    ****************************************************************************/

    private class SubMapEntryIterator extends EntryIterator {
        private final Object firstExcludedKey;
        /*******************************************************************
         * CONSTRUCTOR
         * @param first Entry
         * @param firstExcluded Entry
         ******************************************************************/
        SubMapEntryIterator(Entry first, Entry firstExcluded) {
            throw new UnsupportedOperationException("Implement This");
        }
        /*******************************************************************
         *
         * @return boolean
         * retuns if there exists another item to iterate through
         ******************************************************************/
        public boolean hasNext() {
            throw new UnsupportedOperationException("Implement This");
        }

        /*******************************************************************
         *
         * @return Object
         *
         * return next item
         ******************************************************************/
        public Object next() {
           throw new UnsupportedOperationException("Implement This");
        }
    }

}


