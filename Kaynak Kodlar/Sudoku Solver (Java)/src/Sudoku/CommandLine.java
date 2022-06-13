package sudoku20421689;

import java.io.IOException;



public class CommandLine implements CommandLineInterface{
	
	private CoreInterface cin = null;
	int inputType,outputType;
	
	public CommandLine(CoreOperations cor,int inputType, int outputType) 
	{
		cin = cor;
		this.inputType = inputType;
		this.outputType =outputType;
	}
	
	
	public int[][][] SolveSudoku(int[][] puzzle,int solverId)
	{
		return cin.SolveSudoku(puzzle, solverId);
	}
	
	public boolean validateSudoku(int[][][] puzzles)
	{
		return cin.validateSudoku(puzzles);
	}
	
	public void writeSolutions(int[][][] puzzles,String fileName)
	{
		try {
			cin.writeSolutions(puzzles,fileName, outputType);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		
	}


	@Override
	public int[][] read(String fileName) throws IOException {
		// TODO Auto-generated method stub
		return cin.read(fileName,inputType);
	}





}
