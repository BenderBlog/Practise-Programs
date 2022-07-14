/*
 *  2021, Written by SuperBart@bilibili, licensed under the Unlicense
 *  Consider Subscribe Me at Bilibili!
 */
package Experience2_Student;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class test {
	static ArrayList<student> Meatbag = new ArrayList<student>();
	static Scanner input = new Scanner(System.in);
	//在输入字符串前，一定要把Enter给吃掉，防止传到要输入的字符串
	static String eatEnter;
	
	static void printList() {
		System.out.println("1. Add Student");
		System.out.println("2. Change Name");
		System.out.println("3. Change Age");
		System.out.println("4. Set GPA");
		System.out.println("5. Order Student");
		System.out.println("6. Add Class for Student");
		System.out.println("7. Del Class for Student");
		System.out.println("8. Escape from this limbo");
		System.out.printf("Enter your option: ");
	}
	
	static void printStudent() {
		for (student i : Meatbag) {
			//System.out.println(i.toString("all"));
			System.out.println("Number Name Ages GPA");
			System.out.println(i.toString("Number") + " " + 
							   i.toString("Name")   + " " + 
							   i.toString("Age")    + " " + 
							   i.toString("GPA"));
		}
	}
	
	public static void main(String[] avgs) {
		while (true) {
			printStudent();
			printList();
			int option = input.nextInt();
			
			if (option == 1) {
				int situation = 1;
				
				eatEnter = input.nextLine();
				System.out.printf("Enter name: ");
				String inputName = input.nextLine();

				System.out.printf("Enter number: ");
				int inputNumber = input.nextInt();
				
				for (student i : Meatbag) {
					if ( inputName == i.toString("Name") ||
						Integer.parseInt(i.toString("Number")) == inputNumber) {
						System.out.println("Already got one!");
						situation = 0;break;
					}
				}
				
				if (situation == 1) {
					
					eatEnter = input.nextLine();
					System.out.printf("Enter sex: ");
					String inputSex  = input.nextLine();
										
					System.out.printf("Enter age: ");
					int inputAge = input.nextInt();
	
					System.out.printf("Enter grade: ");
					int inputGrade = input.nextInt();
					
					System.out.printf("Enter GPA: ");
					double inputGPA = input.nextDouble();
				
					Meatbag.add(new student(inputName, inputSex, inputAge, 170, 60, 
							inputNumber, inputGPA, inputGrade, "Computer Science"));
				}
			} else if (option == 2 || option == 3 || option == 4 || option == 6 || option == 7) {
				//更改类里元素的属性，考察了我们对类访问的理解
				int check = 1;
				System.out.printf("Enter number: ");
				int inputNumber = input.nextInt();
				
				for (student i : Meatbag) {
					if (Integer.parseInt(i.toString("Number")) == inputNumber) {
						boolean eval = false;
						if (option == 2) {
							eatEnter = input.nextLine();
							System.out.printf("Enter New Name: ");
							String inputName = input.nextLine();
							eval = i.setName(inputName);
						} else if (option == 3) {
							System.out.printf("Enter New Age: ");
							int inputAge = input.nextInt();
							eval = i.setAge(inputAge);
						} else if (option == 4) {
							System.out.printf("Enter New GPA: ");
							double inputGPA = input.nextDouble();
							eval = i.setGPA(inputGPA);
						} else if (option == 6) {
							eatEnter = input.nextLine();
							System.out.printf("Enter A Class: ");
							String inputClass = input.nextLine();
							eval = i.addCource(inputClass);
						} else if (option == 7) {
							eatEnter = input.nextLine();
							System.out.printf("Enter A Class: ");
							String inputClass = input.nextLine();
							eval = i.deleteCourse(inputClass);
						}
						if (eval == true) {
							System.out.println("Success!");
							System.out.println(i.toString("all"));
							check = 0; break;
						} else {
							System.out.println("Failed!");
							break;
						}
					}
				}
				
				if (check == 1)
					System.out.println("Unable to find :-(");
				
			} else if (option == 5) {
				//Comparable接口的使用
				Collections.sort(Meatbag);
				for (student i : Meatbag) {
					System.out.println(i.toString("Name") + " " + i.toString("GPA"));
				}
			} else if (option == 8) {
				printStudent();
				input.close();
				System.out.println("Memory Losing...");
				return;
			}
		}
	}
}
