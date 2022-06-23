import java.util.*;
import java.io.*;

public class Operations {
	
	public Operations()
	{
		
	}// constructor of the Operations class

	public void ReadInputFile(String inputFile, String outputFile) throws IOException , FileNotFoundException {
		
		String line , block , blocknumber , btreeorder , temp , command , filename , filesize ;
		int blocks , blocknumbers , btreeorders , filesizes ;
		BufferedReader input = new BufferedReader(new FileReader(inputFile));
		BufferedWriter output = new BufferedWriter(new FileWriter(outputFile));
		line = input.readLine() ;
		output.write(line);
		output.newLine() ;
		StringTokenizer token = new StringTokenizer(line);
		block = token.nextToken() ;
		temp = block.substring(7); //the size of the string "blocks=" is 7 so with this we will take just number
		blocks = Integer.parseInt(temp) ;
		blocknumber = token.nextToken() ;
		temp = blocknumber.substring(10); // the size of the string "blocksize=" is 10 so with this we will take just the number
		blocknumbers = Integer.parseInt(temp);
		btreeorder = token.nextToken() ;
		temp = btreeorder.substring(11) ; // the size of the string "btreeorder=" is 11 so with this we will take just number
		btreeorders = Integer.parseInt(temp);
		output.write(blocks + "  "  + blocknumbers + "  " + btreeorders);
		output.newLine() ;
		while((line = input.readLine()) != null)
		{
			output.write(line);
			output.newLine() ;
			StringTokenizer token2 = new StringTokenizer(line);
			command = token2.nextToken() ;
			
			if(command.equals("createfile"))
			{
				filename = token2.nextToken() ;
				filesize = token2.nextToken() ;
				filesizes = Integer.parseInt(filesize);
				createFile(filename , filesizes , output) ;
			}
			
			else if(command.equals("removefile"))
			{
				filename = token2.nextToken() ;
				removeFile(filename , output) ;
			}
			
			else if(command.equals("listfiles"))
			{
				listFiles(output);
			}
			
			else if(command.equals("defragfree"))
			{
				defragTree(output);
			}
			
			else if(command.equals("listfreeblocksbysize"))
			{
				listFreeBlocksBySize(output);
			}
			
			else if(command.equals("listfreeblocksbylocation"))
			{
				listFreeBlocksByLocation(output);
			}
			
			else
			{
				output.write("this is not a suitable command for this experiment.");
				output.newLine() ;
			}
		}
		output.close() ;
	}//that is the end of the read input file function of the operation class

	private void listFreeBlocksByLocation(BufferedWriter output) {
		// TODO Auto-generated method stub
		
	}

	private void listFreeBlocksBySize(BufferedWriter output) {
		// TODO Auto-generated method stub
		
	}

	private void defragTree(BufferedWriter output) {
		// TODO Auto-generated method stub
		
	}

	private void listFiles(BufferedWriter output) {
		// TODO Auto-generated method stub
		
	}

	private void removeFile(String filename, BufferedWriter output) {
		// TODO Auto-generated method stub
		
	}

	private void createFile(String filename, int filesizes,
			BufferedWriter output) {
		// TODO Auto-generated method stub
		
	}

}
