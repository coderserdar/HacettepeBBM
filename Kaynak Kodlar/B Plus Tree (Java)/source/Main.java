import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

public class Main {	
	public static final int dataBufferSize=5000;
	public static int operation=0;
	public static Double dValue;
	public static char[] sValue;
	public static int control=0;
	public static int deletedCounter=0;
	public static int numberOfPassedNode=0;
	public static int deletedIndexArrayIndexes=0;
	public static Node nodepointer;
	static Node bPlusRoot = new BPlusTreeLeafNode() ;
	static Node bRoot = new BTreeNode() ;
	static ArrayList<Integer> arr= new ArrayList<Integer>();/*This is used only for display outputs at demanded format*/
	static Data []dataBuffer= new Data[dataBufferSize];
	static int []deletedIndexes= new int[dataBufferSize];
	public static void main(String[] args) {
		File dataFile = new File(args[0]);
		File commandFile = new File(args[1]);
		File outputFile = new File(args[2]);
		
		int Dataindex=0;
		/*B-Tree and B+ Tree structures*/
		BPlusTree bPlus=new BPlusTree();
		BTree bT =new BTree();

		Map<String, Integer> map1 = new HashMap<String, Integer>();/*this is used for executing commands*/
		Map<String, Integer> map2 = new HashMap<String, Integer>();/*this is used for executing commands*/
		map2.put("BW", 1);
		map2.put("EQ", 2);
		map2.put("GE", 3);
		map2.put("GT", 4);
		map2.put("LE", 5);
		map2.put("LT", 6);
		
		/*Read Data File and open output file*/
		FileWriter writer = null;
		try {
			Dataindex=readDataFile(dataFile, map1, dataBuffer, bT, bPlus);
			writer = new FileWriter(outputFile);/*outputfile*/
		} catch (IOException e1) {
			e1.printStackTrace();
		}

		/*Take commands And Execute Them*/
		String line=new String();
		StringTokenizer tok;
		String field;
		BufferedReader reader;
		try {
			reader = new BufferedReader(new FileReader(commandFile));
			line = reader.readLine();/*read a line from input file*/
			while(line!=null){
				
				tok= new StringTokenizer(line,";");
				field=tok.nextToken();
				int index;
				if(field.compareTo("Insert")==0)
				{
					writer.write("Insert;");
					if(deletedIndexArrayIndexes>0)
					{	
						index=deletedIndexes[deletedIndexArrayIndexes-1];
						deletedIndexArrayIndexes--;
					}
					else
					{
						index=Dataindex;
						Dataindex++;
					}		
					field=tok.nextToken();
					Double id=new Double(field);
					Entry newentry=new Entry();/*create a new entry for adding to each B-tree and B+ tree*/
					newentry.key=id;
					newentry.pointer_to_file=index;
					dataBuffer[index]=new Data();
					dataBuffer[index].id=id;
					writer.append(field+";");
					
					field=tok.nextToken();/*magnitute*/
					dataBuffer[index].magnitude=field.toCharArray();
					writer.append(field+";");
					
					field=tok.nextToken();/*latitute*/
					dataBuffer[index].latitude=field.toCharArray();
					writer.append(field+";");

					field=tok.nextToken();/*longtitute*/
					dataBuffer[index].longtitude=field.toCharArray();
					writer.append(field+";");
					
					field=tok.nextToken();/*depth*/
					dataBuffer[index].depth=field.toCharArray();
					writer.append(field+";");
					
					field=tok.nextToken();/*date*/
					dataBuffer[index].date=field.toCharArray();
					writer.append(field+";");
					
					field=tok.nextToken();/*time*/
					dataBuffer[index].time=field.toCharArray();
					writer.append(field+";");
					/*btree insertion*/
					numberOfPassedNode=0;
					bRoot=bT.insert(bRoot,newentry);
					writer.append(numberOfPassedNode+";");
					/*B+tree insertion*/
					numberOfPassedNode=0;
					bPlusRoot=bPlus.insert(bPlusRoot,newentry);
					writer.append(numberOfPassedNode+"\n");
					writer.write(control+";row;added\n");
				}
				else if(field.compareTo("Delete")==0)
				{
					
					field=tok.nextToken();/*it is for read "ID" field name*/
					writer.write("Delete;"+field+";");
					field=tok.nextToken();
					operation=map2.get(field);
					writer.append(field+";");
					field=tok.nextToken();
					Double value1=new Double(field);
					writer.append(value1+";");
					if(operation==1){
						deletedCounter=0;
						field=tok.nextToken();
						Double value2=new Double(field);
						writer.append(value2+";");
						/*Btree Between Delete*/
						numberOfPassedNode=0;
						bT.deleteBetween(value1,value2);
						writer.append(numberOfPassedNode+";");
						/*B+tree Between Delete*/
						numberOfPassedNode=0;
						bPlus.deleteBetween(value1,value2);
						writer.append(numberOfPassedNode+"\n");
						writer.write(deletedCounter+";row(s);deleted\n");
					}
					
					else if(operation==2){
						deletedCounter=0;
						/*btree delete*/
						numberOfPassedNode=0;
						bRoot=bT.delete(bRoot,value1);
						writer.append(numberOfPassedNode+";");
						/*bplustree delete*/
						numberOfPassedNode=0;
						bPlus.deleteOrList(bPlusRoot, value1);
						writer.append(numberOfPassedNode+"\n");
						writer.write(deletedCounter+";row(s);deleted\n");
					}
					else if(operation==3)
					{
						deletedCounter=0;
						/*btree delete*/
						numberOfPassedNode=0;
						bT.deleteGreater(value1);
						writer.append(numberOfPassedNode+";");
						/*b+tree delete*/
						numberOfPassedNode=0;
						bPlus.deleteGreater(value1);
						writer.append(numberOfPassedNode+"\n");
						writer.write(deletedCounter+";row(s);deleted\n");
					}
					else if(operation==4)
					{
						deletedCounter=0;
						/*btree delete*/
						numberOfPassedNode=0;
						bT.deleteGreater(value1);
						operation=4;
						writer.append(numberOfPassedNode+";");
						/*b+tree delete*/
						numberOfPassedNode=0;
						bPlus.deleteGreater(value1);
						writer.append(numberOfPassedNode+"\n");
						writer.write(deletedCounter+";row(s);deleted\n");
					}
					else if(operation==5)
					{
						deletedCounter=0;
						/*btree delete*/
						numberOfPassedNode=0;
						bT.deleteSmaller(value1);
						writer.append(numberOfPassedNode+";");
						/*b+tree delete*/
						numberOfPassedNode=0;
						bPlus.deleteSmaller(value1);
						writer.append(numberOfPassedNode+"\n");
						writer.write(deletedCounter+";row(s);deleted\n");
					}
					else{
						deletedCounter=0;
						/*btree delete*/
						numberOfPassedNode=0;
						bT.deleteSmaller(value1);
						writer.append(numberOfPassedNode+";");
						/*b+tree delete*/
						numberOfPassedNode=0;
						bPlus.deleteSmaller(value1);
						writer.append(numberOfPassedNode+"\n");
						writer.write(deletedCounter+";row(s);deleted\n");
					}
				}
				else{
					writer.write("List;");
					field=tok.nextToken();
					int columnNumber=map1.get(field);
					writer.append(field+";");
					field=tok.nextToken();
					operation=-map2.get(field);
					writer.append(field+";");
					field=tok.nextToken();	
					if(columnNumber==0){
						Double value1=new Double(field);
						writer.append(value1+";");
						if(operation==-1)
						{/*BW list*/
							field=tok.nextToken();
							Double value2=new Double(field);
							writer.append(value2+";");
							/*Btree list*/
							numberOfPassedNode=0;
							Main.dValue=value2;
							bT.listBetween((BTreeNode) bRoot,value1);
							writer.append(numberOfPassedNode+";");
							/*B+tree list*/
							numberOfPassedNode=0;
							Main.arr.removeAll(arr);
							dValue=value2;/*put input value to dValue(it act as upper limit)*/
							bPlus.deleteOrList(bPlusRoot, value1);
							writer.append(numberOfPassedNode+"\n");
							Main.list(writer);
						}
						else if(operation==-2)
						{/*EQ list*/
							/*Btree list*/
							numberOfPassedNode=0;
							bT.listEqual((BTreeNode) bRoot,value1);
							writer.append(numberOfPassedNode+";");
							/*B+tree list*/
							numberOfPassedNode=0;
							Main.arr.removeAll(arr);
							bPlus.deleteOrList(bPlusRoot, value1);
							writer.append(numberOfPassedNode+"\n");
							Main.list(writer);
						}
						else if(operation==-3)
						{/*GE list*/
							/*Btree list*/
							numberOfPassedNode=0;
							bT.listGreater((BTreeNode) bRoot,value1);
							writer.append(numberOfPassedNode+";");
							/*B+tree list*/
							numberOfPassedNode=0;
							Main.arr.removeAll(arr);
							bPlus.deleteOrList(bPlusRoot, value1);
							writer.append(numberOfPassedNode+"\n");
							Main.list(writer);
						}
						else if(operation==-4)
						{/*GT list*/
							/*Btree list*/
							numberOfPassedNode=0;
							bT.listGreater((BTreeNode) bRoot,value1);
							writer.append(numberOfPassedNode+";");
							/*B+tree list*/
							numberOfPassedNode=0;
							Main.arr.removeAll(arr);
							bPlus.deleteOrList(bPlusRoot, value1);
							writer.append(numberOfPassedNode+"\n");
							Main.list(writer);
						}
						else if(operation==-5)
						{/*LE list*/
							/*Btree list*/
							numberOfPassedNode=0;
							bT.listSmaller((BTreeNode) bRoot,value1);
							writer.append(numberOfPassedNode+";");
							/*B+tree list*/
							numberOfPassedNode=0;
							Main.arr.removeAll(arr);
							bPlus.listSmaller(bPlusRoot,bPlus,value1);
							writer.append(numberOfPassedNode+"\n");
							Main.list(writer);
						
						}
						else{
							/*Btree list*/
							numberOfPassedNode=0;
							bT.listSmaller((BTreeNode) bRoot,value1);
							writer.append(numberOfPassedNode+";");
							/*B+tree list*/
							numberOfPassedNode=0;
							Main.arr.removeAll(arr);
							bPlus.listSmaller(bPlusRoot,bPlus,value1);
							writer.append(numberOfPassedNode+"\n");
							Main.list(writer);
						}
					}
					else{/*with other columns from ID*/
						char[] value1;
						value1=field.toCharArray();
						writer.append(field+";");
						if(operation==-1)
						{/*BW list*/
							field=tok.nextToken();
							char[] value2;
							value2=	field.toCharArray();
							writer.append(field+";");
							Main.sValue=value2;
							/*Btree list*/
							bT.travelAll((BTreeNode) bRoot,value1,columnNumber);						
							/*B+tree list*/
							numberOfPassedNode=0;
							Main.arr.removeAll(arr);
							BPlusTreeLeafNode smallestNode=(BPlusTreeLeafNode) bPlus.findSmallest(bPlusRoot);
							bPlus.travelAllNodes(smallestNode,value1 ,columnNumber);
							writer.append(numberOfPassedNode+";"+numberOfPassedNode+"\n");
							Main.list(writer);
						}
						else{
							/*btree*/
							bT.travelAll((BTreeNode) bRoot,value1,columnNumber);
							/*B+tree list*/
							numberOfPassedNode=0;
							Main.arr.removeAll(arr);
							BPlusTreeLeafNode smallestNode=(BPlusTreeLeafNode) bPlus.findSmallest(bPlusRoot);
							bPlus.travelAllNodes(smallestNode,value1 ,columnNumber);
							writer.append(numberOfPassedNode+";"+numberOfPassedNode+"\n");
							Main.list(writer);
						}
					}
				
				}
				line = reader.readLine();/*read a line from input file*/
				}
		
		} catch (IOException e) {
			/*file exception occurs*/
			e.printStackTrace();
		}
		try {
			writer.close();
		} catch (IOException e) {
			/*file exception occurs*/
			e.printStackTrace();
		}
	

	}
	private static void list(FileWriter writer) throws IOException {
		writer.write(arr.size()+";row(s);listed\n");
		int i=0,j,k;
		while(i<arr.size())
		{
			j=arr.get(i);
			writer.write(dataBuffer[j].id+";");
			k=0;
			while(k<dataBuffer[j].magnitude.length)
			{
				writer.append(dataBuffer[j].magnitude[k]);
				k++;
			}
			writer.append(';');
			k=0;
			while(k<dataBuffer[j].latitude.length)
			{
				writer.append(dataBuffer[j].latitude[k]);
				k++;
			}
			writer.append(';');
			k=0;
			while(k<dataBuffer[j].longtitude.length)
			{
				writer.append(dataBuffer[j].longtitude[k]);
				k++;
			}
			writer.append(';');
			k=0;
			while(k<dataBuffer[j].depth.length)
			{
				writer.append(dataBuffer[j].depth[k]);
				k++;
			}
			writer.append(';');
			k=0;
			while(k<dataBuffer[j].date.length)
			{
				writer.append(dataBuffer[j].date[k]);
				k++;
			}
			writer.append(';');
			k=0;
			while(k<dataBuffer[j].time.length)
			{
				writer.append(dataBuffer[j].time[k]);
				k++;
			}
			writer.append('\n');
			
			i++;
		}
		arr.removeAll(arr);
		
	}
	public static int readDataFile(File dataFile,Map<String, Integer> map,Data []dataBuffer,BTree bT,BPlusTree bPlus) throws IOException
	{/*read data file*/

		BufferedReader reader = new BufferedReader(new FileReader(dataFile));/*hold input file in memory*/
		String line = reader.readLine();/*read a line from input file*/
		StringTokenizer tok= new StringTokenizer(line);
		int index=0;
		while(tok.hasMoreTokens()){
			map.put(tok.nextToken(";"),index );
			index++;
		}
		index=0;
		line = reader.readLine();/*read a line from input buffer*/
		while (line !=  null ) {
				tok= new StringTokenizer(line,";");
				String field;
				if(tok.hasMoreTokens()){
					
					field=tok.nextToken();
					Double id=new Double(field);
					
					Entry newentry=new Entry();/*create a new entry for adding to each B-tree and B+ tree*/
					newentry.key=id;
					newentry.pointer_to_file=index;
					dataBuffer[index]=new Data();
					dataBuffer[index].id=id;
					
					field=tok.nextToken();/*magnitute*/
					dataBuffer[index].magnitude=field.toCharArray();
					
					field=tok.nextToken();/*latitute*/
					dataBuffer[index].latitude=field.toCharArray();
	
					field=tok.nextToken();/*longtitute*/
					dataBuffer[index].longtitude=field.toCharArray();
					
					field=tok.nextToken();/*depth*/
					dataBuffer[index].depth=field.toCharArray();
					
					field=tok.nextToken();/*date*/
					dataBuffer[index].date=field.toCharArray();
					
					field=tok.nextToken();/*time*/
					dataBuffer[index].time=field.toCharArray();
	
					/*btree insertion*/
					bRoot=(BTreeNode) bT.insert(bRoot,newentry);
					/*B+tree insertion*/
					bPlusRoot=bPlus.insert(bPlusRoot,newentry);

			}
			index++;
			line = reader.readLine();/*read a line from input buffer*/
		}
		reader.close();/*close input file*/
		return index;
	}
	


}
