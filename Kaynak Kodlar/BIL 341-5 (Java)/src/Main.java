import java.util.*;
import java.io.*;

public class Main {
	
	public static void main(String[] args) throws IOException {
			
			Operations o = new Operations();
			String InputFile = args[0];
			String OutputFile = args[1];		
			o.ReadInputFile(InputFile , OutputFile);
			
	}

}
