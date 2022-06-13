package sudoku20421689;

import java.io.IOException;

public class CoreOperations implements CoreInterface{

	
	ConstraintSolverInterface csin= null;
	FileInterface fi = null;
	//String[] args = null;
	
	public CoreOperations(/*String[] args*/)
	{
		//this.args =args;
	}
	
	@Override
	public int[][] read(String fileName, int inputType) throws IOException 
	{
		
		if(inputType == 1)
			fi = new CompactFile();
		else
			fi = new FullFile();
		
			return fi.readFile(fileName);
		

	}
	
	@Override
	public int[][][] SolveSudoku(int[][] puzzle, int solverId) {
		
		if(solverId == 1){
			csin = new ChocoSolver();
		}else{
			csin = new CreamSolver();
		}
		
		return csin.SolveSudoku(puzzle);
	}

	@Override
	public boolean validateSudoku(int[][][] puzzles) {
		// validate iþlemleri yap sadece her býr cozum ýcýn
		//arada hatalý cozum gorursen [i][0][0] = 0 bas
		//donustede [i][0][0] kontrol et 0 olanlarý es geçicez
		int lenght = puzzles.length;
		int i=0,j=0,k=0,toplam=0;
		boolean result = true;
		for(k=0; k< lenght; k++) //her puzzle kontrol et
		{
			toplam =0;
			result=true;
			for(i=0; i<9; i++)
			{
				for(j=0; j<9; j++)
				{
					toplam += puzzles[k][i][j];
				}
				if(toplam !=45){
					result = false;
					break;
				}
			}
			if(!result)
			{
				puzzles[k][0][0] = 0;
			}
			
		}
		
		for(k=0; k< lenght; k++) //her puzzle kontrol et
		{
			toplam =0;
			result=true;
			if(puzzles[k][0][0] != 0)
			{
				for(i=0; i<9; i++)
				{
					for(j=0; j<9; j++)
					{
						toplam += puzzles[k][j][i];
					}
					if(toplam !=45){
						result = false;
						break;
					}
				}
				if(!result)
				{
					puzzles[k][0][0] = 0;
				}
			}
			
		}
		
		
		
		
		return false;
	}

	@Override
	public void writeSolutions(int[][][] puzzles,String fileName,int outputType) throws IOException {
		//yazýlacak dosyayý dongude ac kac sonuc varsa o kadar dosya yazýlcak
		//sudoku sayýsýna gore dosyalarý solution-1.compact (mesela) numaralandýr
		
		try {
			if(outputType == 1)
				fi = new CompactFile();
			else
				fi = new FullFile();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		int lenght = puzzles.length;
		int count = 0;
		String file = "";
		System.out.println("yazdýrma içindeyim puzzle uzunlugu = " + puzzles.length);
		for(int i=0; i< lenght; i++)
		{
			if(puzzles[i][0][0] != 0)
			{
				//count tut ona gore ýsýmlendýr sudokuhard->count>.full gýbý
				count++;   //couýntu u dosya adýna ekle
				
				   ///dosya adý sudokuharsolutions.full
				//bunun donusmesý gereken seklý = sudokuhardsolutýons-1.hard
				//araya count un gýrmesý lazým
				//valýdate sýmdýlýk kapalý 0 lýyor bosu bosuna 
				file = fileName + "-"  + count; 
				fi.writeFile(file, puzzles[i]);
			}

		}
	}



}
