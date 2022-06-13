package sudoku20421689.provided;

/**
 * A lightweight dummy interface for an existing Sudoku Solver System.
 * 
 * @author Ersin Er
 */
public interface DummySudokuSolver {
	
	/**
	 * Gets a double sized array which represents a Sudoku puzzle in the simplest sense and returns
	 * a triple sized array which represents a list of solutions to the provided puzzle.
	 * 
	 * @param puzzle Sudoku puzzle to be solved
	 * @param solverId Id of the constraint solver to be used
	 * @return A list of puzzle solutions represented as array of double sized arrays
	 * @throws SimpleSudokuSolverException When the input consists of any errors
	 */
	public int[][][] solveSudoku(int[][] puzzle, int solverId) throws SimpleSudokuSolverException;
	
	
	/**
	 * Gets name of a file which contains a definition of a Sudoku puzzle and returns
	 * a triple sized array which represents a list of solutions to the provided puzzle.
	 * 
	 * @param puzzleFile Name of a file which contains definition of a Sudoku puzzle
	 * @param solverId Id of the constraint solver to be used
	 * @return A list of puzzle solutions represented as array of double sized arrays
	 * @throws SimpleSudokuSolverException When the input consists of any errors
	 */
	public int[][][] solveSudoku(String puzzleFile, int solverId) throws SimpleSudokuSolverException;

}
