package sudoku20421689;

import java.io.IOException;

public interface CoreInterface {
	
	public int[][] read(String fileName, int inputType) throws IOException;
	public int[][][] SolveSudoku(int[][] puzzle,int solverId);
	public boolean validateSudoku(int[][][] puzzles);
	public void writeSolutions(int[][][] puzzles,String FileName, int outputName) throws IOException;
}
