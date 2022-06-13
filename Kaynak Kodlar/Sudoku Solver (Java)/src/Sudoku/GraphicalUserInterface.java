package sudoku20421689;

import java.io.IOException;

public interface GraphicalUserInterface{
	
	public int[][] read(String fileName) throws IOException;
	public int[][][] SolveSudoku(int[][] puzzle,int solverId);
	public boolean validateSudoku(int[][][] puzzles);
	public void writeSolutions(int[][][] puzzles,String fileName) throws IOException;

}
