import java.util.*;
import java.io.*;
public class Main {

	public static void main(String[] args) throws IOException {
		File input;
		File output;
		input = new File(args[0]);
		output = new File(args[1]);
		String line = new String();
		StringTokenizer tok;
		String field,other;
		int x,y;
		BufferedReader reader;
		FileWriter writer = null;
		Vector<Point> v = new Vector<Point>();
		writer = new FileWriter(output);
		reader = new BufferedReader(new FileReader(input));
		line = reader.readLine();
		int counter = 0;
		while(line != null)
		{
			tok = new StringTokenizer(line,", ");
			field = tok.nextToken();
			writer.write(field + " ");
			//System.out.println(field + " ");
			other = tok.nextToken();
			writer.write(other + "\n");
			//System.out.println(other + " ");
			x = Integer.parseInt(field);
			y = Integer.parseInt(other);
			Point a = new Point(x,y);
			v.addElement(a);
			line = reader.readLine();
		}
		/*
		for (int i = 0;i <v.size();i++)
		{
			System.out.print(v.elementAt(i).x + " " + v.elementAt(i).y + "\n");
		}
		*/
		Operations o = new Operations(v);

		writer.close();
	}

}
