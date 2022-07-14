package experienceFirst;

public class SeeSomething {
	public static void main(String [] avgs) {
		int i = 5;
		int j = 0;
		for (int times = 1; times <= 2; ++times) {
			System.out.println("i = "+i+" j = "+j+"\n");
			j += i++;
		}
		System.out.println("i = "+i+" j = "+j+"\n");
	}
}
