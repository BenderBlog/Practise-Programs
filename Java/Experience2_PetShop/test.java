package Experience2_PetShop;
import java.util.ArrayList;
import java.util.Scanner;

public final class test {
	
	/*   本来想这么写的
	 *   static pet[] store = {new pet(1,"unknown"), new pet(2,"unknown"), new pet(3,"unknown")};
	 *   可是，父类不能转化为子类，除非是用子类new出来的……
	 *   所以说，只能用ArrayList了:-P
	 */
	
	static ArrayList<pet> store = new ArrayList<pet>();
	static int number = 1;
	
	static String eval(pet a) {
		if (a instanceof dog)
			return "dog";
		else if (a instanceof cat)
			return "cat";
		else if (a instanceof bird)
			return "bird";
		else
			return "pet";
	}
	
	static void printMenu() {
		System.out.println("1. 寄养宠物");
		System.out.println("2. 领走宠物");
		System.out.println("3. 投喂宠物");
		System.out.println("4. 查看宠物");
		System.out.println("5. 退出程序");
		System.out.println("你的选项是：");
	}
	
	static void printAnimals() {
		if (store.isEmpty() == true) {
			System.out.println("店里没有宠物。");
		} else {
			System.out.println("序号 登记号 名称 类型");
			for (pet i : store) {
				System.out.println(store.indexOf(i) + " " + i.number + " " + i.name + " " + eval(i));
			}
		}
	}
	
	static void printAnimals(int index) {
		if (store.isEmpty() == true) {
			System.out.println("店里没有宠物。");
		} else {
			System.out.println("登记号 名称 类型");
			int nail = 0;
			for (pet i : store) {
				nail++;
				if (i.number == index)
					break;
				if (nail == 11)
					break;
			}
			if (nail <= 10) {
				for (int i = 0; i < nail; ++i) {
					System.out.println(store.get(i).number + " " + store.get(i).name + " " + eval(store.get(i)));
				}
			} else if (nail > 10) {
				System.out.println("无法找到该宠物。");
			}
		}
	}
	
	static void printAnimals(String Type) {
		if (store.isEmpty() == true) {
			System.out.println("店里没有宠物。");
		} else {
			System.out.println("以下是"+ Type +"类型的宠物");
			System.out.println("登记号 名称");
			for (pet i : store) {
				if (eval(i) == Type)
					System.out.println(i.number + " " + i.name);
			}
		}
	}
	
	public static void main(String [] avgs) {
		Scanner input = new Scanner(System.in);
		while (true) {
			printMenu();
			int i = input.nextInt();
			if (i == 1) {
				System.out.printf("你宠物的名称：");
				String name = input.next();
				System.out.printf("你的宠物类型，狗为1，猫为2，鸟为3：");
				int type = input.nextInt();
				if (type == 1) {
					System.out.printf("你的狗是什么品种的：");
					String kind = input.next();
					store = welcome.newDoge(store,number,name,kind);
					number ++;
				} else if (type == 2) {
					System.out.printf("你的猫可爱不可爱，随便输入一个整数：");
					int cute = input.nextInt();
					store = welcome.newMeow(store,number,name,cute);
					number++;
				} else if (type == 3) {
					System.out.printf("你的鸟是不是一只鹦鹉，是请按1，否则随便输入一个数字：");
					int isParrot = input.nextInt();
					store = welcome.newBirdy(store,number,name,isParrot);
					number++;
				}
				System.out.printf("记住，你的登记号为%d。\n",number-1);
			} else if (i == 2) {
				printAnimals();
				System.out.printf("请选择需要归还宠物的登记号：");
				int toReturn = input.nextInt();
				store = takeaway.gohome(store,toReturn);
			} else if (i == 3) {
				System.out.printf("输入你的登记号：");
				int index = input.nextInt();
				int nail = 0;
				for (pet j : store) {
					nail++;
					if (j.number == index) {
						if (eval(j) == "dog") {
							dog k = (dog) j;
							System.out.println(k.feed(k));
							break;
						} else if (eval(j) == "cat") {
							cat k = (cat) j;
							System.out.println(k.feed(k));
							break;
						} else if (eval(j) == "bird") {
							bird k = (bird) j;
							System.out.println(k.feed(k));
							break;
						} else {
							System.out.println(j.feed());
							break;
						}
					}
					if (nail == 11)
						break;
				}
				if (nail > 10) {
					System.out.println("无法找到该宠物。");
				}
	
			} else if (i == 4) {
				System.out.println("1. 打印所有");
				System.out.println("2. 按时间打印");
				System.out.println("3. 打印某种类型");
				System.out.println("4. 按登记号检索");
				System.out.printf("你的选项是：");
				int anotherOption = input.nextInt();
				if (anotherOption == 1) {
					printAnimals();
				} else if (anotherOption == 2) {
					System.out.printf("输入你的登记号：");
					int index = input.nextInt();
					printAnimals(index);
				} else if (anotherOption == 3) {
					System.out.println("1.dog 2.cat 3.bird");
					System.out.println("按照你想看到的宠物类型输入序号：");
					int index = input.nextInt();
					if (index == 1) 
						printAnimals("dog");
					else if (index == 2) 
						printAnimals("cat");
					else if (index == 3) 
						printAnimals("bird");
					else 
						System.out.printf("我没时间陪你！");
				} else if (anotherOption == 4) {
					System.out.println("请输入登记号：");
					int index = input.nextInt();
					System.out.println("登记号 名称 类型");
					int nail = 0;
					for (pet j : store) {
						nail++;
						if (j.number == index) {
							System.out.println(j.number + " " + j.name + " " + eval(j));
							break;
						}
						if (nail == 11) {
							break;						
						}
					}
					if (nail > 10) {
						System.out.println("无法找到该宠物。");
					}
				}
			} else if (i == 5) {
				System.out.println("正在退出......");		
				input.close();
				return;
			}
		}

	}
}
