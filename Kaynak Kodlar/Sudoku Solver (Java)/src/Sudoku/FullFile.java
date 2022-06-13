package sudoku20421689;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.StringTokenizer;

public class FullFile implements FileInterface{
	
public FullFile(){}
		
	public int[][] readFile(String FileName) throws IOException{
		
		BufferedReader reader;
		
		File input = new File(FileName);
		int puzzle[][] = new int[9][9];
		
		try {
			
			reader = new BufferedReader(new FileReader(input));
			int rowNumber = 0;
			StringTokenizer tok;
			String line = reader.readLine();
			
			while(line != null)
			{
				tok = new StringTokenizer(line,", []\n");
					if(tok.hasMoreElements()){
						for(int i = 0; i < 9; i++)	
							puzzle[rowNumber][i] = Integer.parseInt(tok.nextToken());
					
					rowNumber++;
					}
				
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
		
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++)
			{
				if(j % 3 == 0)
					writer.write("[");
				writer.write(Integer.toString(puzzle[i][j]));
				
				if(j % 3 != 2)
					writer.write(",");
				if(j % 3 == 2)
					writer.write("]");
				if(j % 3 == 2 && j != 8)
					writer.write(" ");
				
			}
			if(i % 3 == 2 && i != 8)
				writer.write("\n");
			if(i != 8)
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

