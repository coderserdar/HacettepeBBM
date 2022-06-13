package sudoku20421689;

import jp.ac.kobe_u.cs.cream.*;
public class CreamSolver implements ConstraintSolverInterface{
	
	
	public CreamSolver()
	{
	}
	
	public int[][][] SolveSudoku(int[][] puzzle)
	{
		Network net = new Network();
    	int n = 9;
    	IntVariable[][] v = new IntVariable[n][n];
    	IntVariable[] vs = new IntVariable[n];
    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < n; j++) {
    			if (puzzle[i][j] == 0)
    				v[i][j] = new IntVariable(net, 1, n);
    			else
    				v[i][j] = new IntVariable(net, puzzle[i][j]);
    		}
    	}
    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < n; j++)
    			vs[j] = v[i][j];
    		new NotEquals(net, vs);
    	}
    	for (int j = 0; j < n; j++) {
    		for (int i = 0; i < n; i++)
    			vs[i] = v[i][j];
    		new NotEquals(net, vs);
    	}
    	for (int i0 = 0; i0 < n; i0 += 3) {
    		for (int j0 = 0; j0 < n; j0 += 3) {
    			int k = 0;
    			for (int i = i0; i < i0+3; i++)
    				for (int j = j0; j < j0+3; j++)
    					vs[k++] = v[i][j];
    			new NotEquals(net, vs);
    		}
    	}
    	
    	int result[][][] = new int [100][n][n];
    	int solutionNumber = 0;
    	
    	Solver solver = new DefaultSolver(net);
    	for (solver.start(); solver.waitNext(); solver.resume()) {
    		
    		Solution solution = solver.getSolution();
    		
    		for (int i = 0; i < n; i++) 
    		{
    			for (int j = 0; j < n; j++)
    			{		
    				result[solutionNumber][i][j] = (solution.getIntValue(v[i][j]));
    			}
    		}
    		
    		solutionNumber ++;
    		solver.stop();
    	}
    	
    	return result;
	}


}
