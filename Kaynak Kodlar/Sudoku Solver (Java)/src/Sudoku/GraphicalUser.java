package sudoku20421689;
import java.io.IOException;

public class GraphicalUser implements GraphicalUserInterface{
	
	private CoreInterface cin = null;
	
	int inputType=1,outputType=1;
	
	public GraphicalUser(CoreOperations cor) 
	{
		this.cin = cor;
	}
	
	
	public int[][] read(String fileName) throws IOException 
	{
			return this.cin.read(fileName,inputType);
	}
	
	
	public int[][][] SolveSudoku(int[][] puzzle,int solverId)
	{
		return this.cin.SolveSudoku(puzzle, solverId);
	}
	
	public boolean validateSudoku(int[][][] puzzles)
	{
		return this.cin.validateSudoku(puzzles);
	}
	
	public void writeSolutions(int[][][] puzzles,String fileName) throws IOException
	{
		this.cin.writeSolutions(puzzles,fileName,outputType);
		
	}




}
