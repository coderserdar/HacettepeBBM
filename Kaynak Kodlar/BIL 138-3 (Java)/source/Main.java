
public class Main {
	private static String inputFileName;
	private static String outputFileName;
	public static void main(String []args){
		if(args.length != 2)
		{
			System.err.println("Invalid argument number");
			System.exit(1);
		}

		inputFileName = args[0];
		outputFileName = args[1];
		
		SystemInfoSystem sis=new SystemInfoSystem();
		
	}
}
