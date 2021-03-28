package experienceFirst;
import java.util.Scanner;		
public class CountPi {			
	static float Go2It (float times) {				// A name from DOOM II
		float pi = 1.0F;
		for (float i = 1; i <= times; i++) {
			float b = 1 / (2 * i + 1);
			if ( i % 2 != 0 )  pi = pi - b;
			else if ( i % 2 == 0 )  pi = pi + b;
			System.out.println("time = "+ i +" pi = "+ pi +"\n");
		}
		return 4*pi;
	}
	
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		System.out.printf("Enter a time to roundabout:");
		float a = input.nextFloat();
		System.out.printf("%.10f",Go2It(a));
		input.close();
	}
}

