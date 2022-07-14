package experienceFirst;
import java.util.Scanner;
public class CountEachBits {
	static int add(char[] a) {
		int number = 0;
		for (int i = 0; i <= a.length - 1 ; ++i)
			number += (int) a[i] - 48;
		return number;
	}
	
	public static void main(String[] args) {
		Scanner Input = new Scanner(System.in);	
		System.out.printf("Enter a number strings: ");
		String Line = Input.nextLine();
		char[] data = Line.toCharArray();
		System.out.printf("Total number are %d", add(data));
		Input.close();
	}

}
