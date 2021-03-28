package experienceFirst;
import java.util.Scanner;

public class TheCalender {

	//The two methods below are just eye candy.
	static String nameOfTheMonth(int month) {
		switch (month) {
		case 1: return "January";
		case 2: return "February";
		case 3: return "March";
		case 4: return "April";
		case 5: return "May";
		case 6: return "June";
		case 7: return "July";
		case 8: return "August";
		case 9: return "September";
		case 10: return "October";
		case 11: return "November";
		case 12: return "December";
		}
		//Note that every method without 'void' needs a return in any time.
		return "";
	}
	static String nameOfTheWeek(int week) {
		switch (week) {
		case 1: return "Monday";
		case 2: return "Tuesday";
		case 3: return "Wednesday";
		case 4: return "Thursday";
		case 5: return "Friday";
		case 6: return "Saturday";
		case 0: return "Sunday";
		}
		return "";
	}
	
	//This method is used to judge the year with 356 days.
	static boolean evalSpecialYear(int year) {
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			return true;
		else
			return false;
	}

	//This method is used to answer how many days in a month.
	static int dayOfTheMonth(int month, boolean special) {
		if (month == 2 && special == true)  return 29;
		else if (month == 2 && special == false)  return 28;
		else if (month == 1 || month == 3 || month == 5 || 
				 month == 7 || month == 8 || month == 10 || month == 12) return 31;
		else return 30;
	}
	
	//This method is important, find the week of the first day of a new year.
	static int startWeek(int year) {
		int levelWeek = 5, totalDay = 0;	//The standard is 2021-1-1 Friday
		int delta = year - 2021;			//See the input year is before 2021 or not

		//Calculate the day between the first day of the input year and
		//the first day of the 2021, then store the number into 'totalDay'
		if (delta < 0) {
			for (int i = year; i < 2021; ++i)
				if (evalSpecialYear(i) == true)
					totalDay += 366;
				else if (evalSpecialYear(i) == false)
					totalDay += 365;
		} else if (delta >= 0) {
			for (int i = year; i > 2021; --i)
				if (evalSpecialYear(i) == true)
					totalDay += 366;
				else if (evalSpecialYear(i) == false)
					totalDay += 365;
		}

		//Minus 'totalDay' with 7, till it is between 0 and 7
		//Then compare it with the levelWeek, to see the week of the first day of the input year.
		while (totalDay - 7 >= 0)
			totalDay -= 7;
		return Math.abs(levelWeek - totalDay);
	}

	//This method is used to print the calendar.
	//This method is used to print the freaking calendar.
	static void printCalender(int year) {
		int startWeek = startWeek(year);
		
		//Count is used for enter before reached into Sunday,
		//which is the first day of the week.
		int count = 0;
		
		//There are 12 months in a year, right?
		for (int currentMonth = 1; currentMonth <= 12; ++currentMonth) {
			
			//Set the week of the first day of a new year into count.
			if (currentMonth == 1) count = startWeek;
			
			System.out.printf("%s", nameOfTheMonth(currentMonth));
			System.out.println('\n' + "Sun Mon Tue Wed Thu Fri Sat");
			
			//Also, there may have some space before the first day of the month,
			//So just space them!
			for (int j = 1; j <= count; j++) {
				System.out.printf("    ");
			}
			
			//There are certain days in a month, right :-P
			for (int j = 1; j <= dayOfTheMonth(currentMonth, evalSpecialYear(year)); ++j) {
				
				//Again, these judgment is just eye candy.
				if (j >= 1 && j <= 9) {
					System.out.printf("%d   ", j);
					count++;
				}
				if (j >= 10) {
					System.out.printf("%d  ", j);
					count++;
				}
				
				//I mentioned what 'count' is used for before.
				if (count == 7) {
					System.out.printf("\n");
					count = 0;
				}
			}
			System.out.printf("\n\n");
		}
	}

	//This method is used to print the week of the day.
	
	//This method is used to print the week of that day.
	static void tellMeTheWeek(int year, int month, int day) {
		int startWeek = startWeek(year);
		
		//This count is the same as the 'count' in the method 'printCalender'
		int count = 0;
		for (int currentMonth = 1; currentMonth <= 12; ++currentMonth) {
			if (currentMonth == 1) count = startWeek;
			for (int j = 1; j <= dayOfTheMonth(currentMonth, evalSpecialYear(year)); ++j) {
				
				//If reached the day the user inputed, print 'count' and exit.
				//Else, jump into next day.
				if (currentMonth == month && j == day) {
					System.out.println(nameOfTheWeek(count));
					break;
				}
				else count++;
				
				//Still, if next day is Sunday, set it into zero.
				if (count == 7) count = 0;
				
			}
		}
	}

	
	//The main gateway of the program, nothing much to say.
	public static void main(String[] avgs) {
		Scanner input = new Scanner(System.in);
		System.out.printf("A Program related to the calender.\n");
		System.out.printf("Usage:\n");
		System.out.printf("	  1.Tell me a year, and I will print the calender of that year\n");
		System.out.printf("   2.Tell me a detailed day, and I will print the week of that day\n");
		System.out.printf("	  3.Exit the program\n");
		while (true) {
			System.out.printf("Now enter your option: ");
			int choose = input.nextInt();
			if (choose == 1) {
				System.out.printf("Enter a year: ");
				int year = input.nextInt();
				printCalender(year);
				System.out.println();
			} else if (choose == 2) {
				System.out.printf("Enter a year: ");
				int year = input.nextInt();
				System.out.printf("Enter a month: ");
				int month = input.nextInt();
				System.out.printf("Enter a day: ");
				int day = input.nextInt();
				tellMeTheWeek(year, month, day);
				System.out.println();
			} else if (choose == 3) {
				System.out.println("Goodbye :-)");
				System.out.println("Use Linux Now!");
				input.close();
				break;
			} else
				System.out.println("Wrong input :-(");
		}
	}

}
