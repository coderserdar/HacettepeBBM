import java.io.*;

public class Main {

	public static void main(String[] args) throws IOException {
		InputStreamReader converter = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(converter);

		System.out.println("Type the text and press enter: ");
		String text = in.readLine() ;
		FindTheILetterInText(text);
		FindTheNumbersInText(text);
		TheTextWithoutDigits(text);
	}

	private static void TheTextWithoutDigits(String text) {
		String result = "" ;
		if(text.length() == 0)
		{
			System.out.println("The text is incorrect.");
		}
		else
		{
			for (int i = 0; i < text.length(); i++) {
		        char c = text.charAt(i);
		        if ( c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9' || c=='0' ) {
		        	
		        }
		        else
		        {
		        	result = result + text.charAt(i);
		        }
		    }
			System.out.println("The text without digits is ") ;
			System.out.println(result) ;
		}		
	}

	private static void FindTheNumbersInText(String text) {
		int count = 0 ;
		if(text.length() == 0)
		{
			System.out.println("The text is incorrect.");
		}
		else
		{
			for (int i = 0; i < text.length(); i++) {
		        char c = text.charAt(i);
		        if ( c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9' || c=='0' ) {
		        	count++;
		        }
		    }
			System.out.println("The number of digits is " + count) ;
		}
		
	}

	private static void FindTheILetterInText(String text) {
		int count = 0 ;
		if(text.length() == 0)
		{
			System.out.println("The text is incorrect.");
		}
		else
		{
			for (int i = 0; i < text.length(); i++) {
		        char c = text.charAt(i);
		        if ( c=='i' || c=='I') {
		        	count++;
		        }
		    }
			System.out.println("The number of eyes is " + count) ;
		}
	}
	
	public static String removeChar(String s, char c) {
	    String r = "";
	    for (int i = 0; i < s.length(); i ++) {
	       if (s.charAt(i) != c)
	    	   r += s.charAt(i);
	       }
	    return r;
	}


}
