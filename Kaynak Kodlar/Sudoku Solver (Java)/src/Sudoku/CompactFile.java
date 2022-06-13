package sudoku20421689;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.StringTokenizer;

public class CompactFile implements FileInterface{
	
	public CompactFile(){}
	
	
public int[][] readFile(String FileName) throws IOException{
		
		BufferedReader reader;
		
		File input = new File(FileName);
		int puzzle[][] = new int[9][9];
		
		try {
			
			reader = new BufferedReader(new FileReader(input));
			StringTokenizer tok;
			String line = reader.readLine();
			
			// initialize
			for(int i = 0; i < 9; i++)
				for(int j = 0; j < 9; j++)
					puzzle[i][j] = 0;
			
			while(line != null)
			{
				tok = new StringTokenizer(line,",:");					
				puzzle[Integer.parseInt(tok.nextToken())][Integer.parseInt(tok.nextToken())] = Integer.parseInt(tok.nextToken());

				line = reader.readLine();
			}	
			
			reader.close();
	   }catch(IOException e){
		   System.err.println("INPUT ERROR");
		   System.exit(1);
	   }	
		
		return puzzle;
	}
	
public void writeFile(String FileName, int[][] puzzle)  throws IOException
{
	
	BufferedWriter writer;
	File output = new File(FileName);
	
	try {
		
	writer = new BufferedWriter(new FileWriter(output));
	
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
			{
				writer.write(i + ",");
				writer.write(j + ":");
				
				writer.write(Integer.toString(puzzle[i][j]));
				
				writer.write("\n");
			}
		writer.write("\n");
		writer.close();
		}catch(IOException e){
	   	System.err.println("OUTPUT ERROR");
	   	System.exit(1);
   	}	

	}

}

