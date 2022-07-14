package atomCalculate;
import java.util.Scanner;

public class atomCalculate {
	

	static boolean isdigit(char a) {
		if ( a - '0' >= 0 && a - '0' <= 9 ) 
			return true;
		else
			return false;
	}
	
	static int todigit(char a) {
		if ( isdigit(a) == true ) 
			return a - '0';
		else
			return -1;
	}
	
	static int pow_int (int toReturn, int times){
	    for (int i = 1; i <= times; ++i)
	        toReturn *= 10;
	    return toReturn;
	}
	
	static double eval(char a) {
		switch (a) {
		case 'C': return 12.010;
		case 'H': return 01.008;
		case 'O': return 16.000;
		case 'N': return 14.010;
		default:  return 0.0;
		}
	}
	
	static double mass(String a) {
	    double toReturn = 0;
	    int temp = 0, time = 0;
	    for (int i = a.length() - 1; i >= 0; i--){
	    	//System.out.println("i = " + i);
	    	try {
		        if ( isdigit(a.charAt(i)) == false && isdigit(a.charAt(i+1)) == false ){
		            //System.out.println("Way 1");
		        	toReturn += eval(a.charAt(i));
		            continue;
		        } else if ( isdigit(a.charAt(i)) == false && isdigit(a.charAt(i+1)) == true ){
		        	//System.out.println("Way 2");
		            toReturn += eval(a.charAt(i)) * temp;
		            time = 0;
		            temp = 0;
		            continue;
		        } else {
		        	//System.out.println("Way 3");
		            temp += pow_int(todigit(a.charAt(i)),time);
		            //System.out.println("temp = " + temp);
		            time ++;
		        }
	    	} catch (StringIndexOutOfBoundsException e) {
	    		if ( isdigit(a.charAt(i)) == false ){
	    			//System.out.println("Way 4");
		            toReturn += eval(a.charAt(i));
		            continue;
	    		} else {
	    			//System.out.println("Way 5");
		            temp += pow_int(todigit(a.charAt(i)),time);
		            time ++;
		        }
	    	} finally {
	    		//System.out.println("toRuturn = " + toReturn + " time = " + time + " temp = " + temp +
	    		//					" eval(a.charAt(i)) = " + eval(a.charAt(i)) + " todigit(a.charAt(i)) = " + todigit(a.charAt(i)) + "\n");
	    	}
	    }
	    return toReturn;
	}
	
	public static void main(String[] avgs) {
		Scanner input = new Scanner(System.in);
		
	    int time = input.nextInt();
		for (int i = 0; i < time; ++i)
	        System.out.printf("%.3f\n", mass(input.next()));
		input.close();
	}
}
