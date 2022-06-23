import java.util.*;
import java.io.*;
public class Main {
	public static void main(String[] args) throws IOException {
		File input;
		File output;
		File harddisk;
		StringTokenizer tok;
		String field,fileName,shortName,secondFile;
		int minute;
		input = new File(args[0]);
		output = new File(args[1]);
		harddisk = new File(args[2]);
		String line = new String();
		BufferedReader reader;
		FileWriter writer = null;
		writer = new FileWriter(output);
		reader = new BufferedReader(new FileReader(input));
		line = reader.readLine();
		tok = new StringTokenizer(line,"\",()");
		while(line != null)
		{//bunlarýn içi iþlemle doldurulacak
			writer.write(line + "\n");
			tok = new StringTokenizer(line,"\",()");
			if(line.startsWith("AddVideo"))
			{
				tok.nextToken();
				shortName = tok.nextToken();
				System.out.print(shortName + "\n");
				fileName = tok.nextToken();
				System.out.print(fileName + "\n");
				
			}//if we want to add a video we will make the processes in this chapter
			
			else if(line.startsWith("PrintFAT"))
			{
				tok.nextToken();
				fileName = tok.nextToken();
				System.out.print(fileName + "\n");
				secondFile = tok.nextToken();
				System.out.print(secondFile + "\n");
			}
			
			else if(line.startsWith("WatchVideo"))
			{
				tok.nextToken();
				shortName = tok.nextToken();
				System.out.print(shortName + "\n");
				field = tok.nextToken();
				minute = Integer.parseInt(field);
				System.out.print(minute + "\n");
			}
			
			else if(line.startsWith("PrintBufferPool"))
			{
				tok.nextToken();
				fileName = tok.nextToken();
				System.out.print(fileName + "\n");
			}
			
			else if(line.startsWith("RemoveVideo"))
			{
				tok.nextToken();
				shortName = tok.nextToken();
				System.out.print(shortName + "\n");
			}
			
			else if(line.startsWith("CloseVideo"))
			{
				tok.nextToken();
				shortName = tok.nextToken();
				System.out.print(shortName + "\n");
				field = tok.nextToken();
				minute = Integer.parseInt(field);
				System.out.print(minute + "\n");
			}
			
			else if(line.startsWith("CopyHDD"))
			{
				tok.nextToken();
				fileName = tok.nextToken();
				System.out.print(fileName + "\n");
			}
			line = reader.readLine();
			
		}
		writer.close();

	}

}
