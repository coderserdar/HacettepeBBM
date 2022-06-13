package sudoku20421689;

import java.io.IOException;

import sudoku20421689.provided.DummySudokuSolver;
import sudoku20421689.provided.SimpleSudokuSolverException;

public class DummySudokuSolver20421689 implements DummySudokuSolver {
	
	private CoreInterface cin = null;
	
	
	public DummySudokuSolver20421689() 
	{
		cin = new CoreOperations();
	}

	@Override
	public int[][][] solveSudoku(int[][] puzzle, int solverId)
			throws SimpleSudokuSolverException {
		// TODO Auto-generated method stub
		return cin.SolveSudoku(puzzle, solverId);
	}

	@Override
	public int[][][] solveSudoku(String puzzleFile, int solverId)
			throws SimpleSudokuSolverException {
		// TODO Auto-generated method stub
		int inputType=0;
		int[][] puzzle = new int[9][9];
		if(puzzleFile.endsWith("full"))
		{
			inputType=2;
		}
		else if(puzzleFile.endsWith("compact"))
		{
			inputType=1;
		}
		
		try {
			puzzle = cin.read(puzzleFile, inputType);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return cin.SolveSudoku(puzzle, solverId);
	}

}
