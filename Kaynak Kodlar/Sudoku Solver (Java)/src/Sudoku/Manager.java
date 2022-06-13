package sudoku20421689;

import java.io.IOException;

public class Manager {

	private static Manager manager = null;
	private static Object lock = new Object();
	
	GraphicalUserInterface gui = null;
	CommandLineInterface cli = null;
	CoreInterface cin = null;
	
	private Manager() {}
	
	
	public static Manager manager()
	{
		if(manager == null)
		{
			synchronized(lock)
			{
				if(manager == null)
				{
					manager = new Manager();
				}
					
			}
		}
		
		return manager;
	}
	
	
	
	
	public void doOperations(String[] args)
	{
		//args ye gore user ýnterface i sec baslat
		//mesela commandline ise
		//CommandLineInterface cli = new CommandLine();
		//her býrý ýcýn consctructor ýcýnde neler olacaksa yerlestýr
		//butun ýslemler bu fonksyon ýcýnden yonetýlecek
		
		if(args.length > 1){ //command lýne 
			
			int inputType = 0,outputType = 0;
			if(args[1].endsWith("compact"))
				inputType = 1;
			else
				inputType = 2;
			
			if(args[3].endsWith("compact"))
				outputType = 1;
			else
				outputType = 2;
			
			cin = new CoreOperations();
			cli = new CommandLine((CoreOperations)cin,inputType,outputType);
			int [][] puzzle = new int [9][9] ;
			try {
				puzzle = cli.read(args[1]);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			int [][][] puzzles = cli.SolveSudoku(puzzle, Integer.parseInt(args[5]));
			//cli.validateSudoku(puzzles);
			
			System.out.println("yazýlýcak" + puzzles.length);
			cli.writeSolutions(puzzles,args[3]);
		
			
		}
		else //GUI olucak
		{
			cin = new CoreOperations();
			gui = new GraphicalUser((CoreOperations)cin);
			
		}
		
		
		
		//cs yý secýlecek ona gore nesne olusturulacak user ýnterface lersen
		//sonrada buradan yonetýlecek kod. once read
		//sonra select sonra solve vs vs ne gerekýosa 
		//hepsý buradan olucak
		
		
		//ORNEK OLARAK COMMAND LINE INTERFACE OLSUN MESELA CS = 2 MESE
		
		//DENEMEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
		
		//DENEMEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
		
		


			
		
		
	}
	
	
}
