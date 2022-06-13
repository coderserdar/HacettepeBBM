package sudoku20421689;

import java.io.IOException;

public interface FileInterface {
	
	public int[][] readFile(String FileName) throws IOException;
	public void writeFile(String FileName,int[][] puzzle) throws IOException;
}
