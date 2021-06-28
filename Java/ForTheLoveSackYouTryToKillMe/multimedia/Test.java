package multimedia;

import java.util.Scanner;
import java.util.Random;
import java.util.Date;
import java.text.SimpleDateFormat;

public class Test {
	static Multimedia[] media = new Multimedia[10];
	static Scanner input = new Scanner(System.in);
	static Random dice = new Random();
	static SimpleDateFormat printDate = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
	
	static String godHand(int i) {
		if (i == 0)
			return "Text";
		else if (i == 1)
			return "Video";
		else if (i == 2)
			return "Picture";
		else
			return "";
	}
	static String godHand(boolean i) {
		if (i)
			return "Chinese";
		else
			return "English";
	}
	public static void main(String[] avgs) {
		for (int i = 0; i < 10; ++i) {
			String name = "File " + (i + 1);
			double size = dice.nextInt(1000) + dice.nextDouble();
			Date now = new Date();
			String time = printDate.format(now);
			String type = godHand(dice.nextInt(3));
			if ( type.equals("Text") == true ) {
				String Language = godHand(dice.nextBoolean());
				String codingScheme = "UTF-8";
				String content = "I understand the current expression is \"hotizontal jogging\", minister. ";
				media[i] = new Text(name, size, time, Language, codingScheme, content);
				Text a = (Text) media[i];
				System.out.println( a.show() );
				System.out.println( a.copy() );
			} else if ( type.equals("Video") == true ) {
				int Resolution = 720;
				String Format = "mkv";
				int Length = dice.nextInt() % 100;
				media[i] = new Video(name, size, time, Resolution, Format, Length);
				Video a = (Video) media[i];
				System.out.println( a.show() );
				System.out.println( a.copy() );
			} else if ( type.equals("Picture") == true ) {
				int x = dice.nextInt() % 1000;
				int y = dice.nextInt() % 1000;
				String Format = "jpg";
				media[i] = new Picture(name, size, time, x, y, Format);
				Picture a = (Picture) media[i];
				System.out.println( a.show() );
				System.out.println( a.copy() );
			}
			System.out.println(media[i].toString());

		}
	}
}
