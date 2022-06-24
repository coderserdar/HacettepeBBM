import java.math.*;
import java.io.*;

public class TaylorSeries {

	public static void main(String[] args) throws IOException {
		double radian ;
		double result ;
		int term ;
		String temp ;
		InputStreamReader converter = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(converter);
		System.out.println("degree in radians: ");
		temp = in.readLine() ;
		radian = Double.parseDouble(temp);
		System.out.println("How many terms do you want (must be positive): ");
		temp = in.readLine() ;
		term = Integer.parseInt(temp);
		if(term < 0)
		{
			System.out.println("Incorrect term");
		}
		else
		{
			result = FindSeries(radian , term) ;
			System.out.println("Sine at 0.8 is " + result + " approximately for the first " + term + "  terms and");
			result = FindSeriesByMathClass(radian, term);
			System.out.println("\t\t" + result + " by Math class");
		}
	}

	private static double FindSeriesByMathClass(double radian, int term) {
		double result = radian ;
		result = Math.sin(result) ;
		return result;
	}

	private static double FindSeries(double radian, int term) {
		double result = 0.0 ;
		int control = 1 ;
		for(int i = 1 ; i < term ; i = i+2)
		{
			if(control == 1)
			{
				result = result + (Math.pow(radian, (double) (i))/factorial(i));
				control = 0 ;
			}
			else
			{
				result = result - (Math.pow(radian, (double) (i))/factorial(i));
				control = 1 ;
			}
		}
		
		return result ;		
	}

	public static int factorial(int n) {
        if (n == 0) return 1;
        return n * factorial(n-1);
    }
	
}
