/*
 *  2021, Written by SuperBart@bilibili <szchen_2@stu.xidian.edu.cn>, licensed under the Unlicense
 *  Consider Subscribe Me at Bilibili!
 */

package Experience2_Student;

class person {
	//private 仅在当前类中可以访问，其他的类，包括其子类，也无法访问
	//默认为在同包中可以访问，protected加上了子类访问权限
	private String Name;
	private String Sex;
	private int Age;
	private int Height;
	private int Weight;
	private String Job;
	//构造函数
	public person(String inputName, String inputSex, 
		   int inputAge, int inputHeight, int inputWeight, String inputJob) {
		setName(inputName);
		setSex(inputSex);
		setAge(inputAge);
		setHeight(inputHeight);
		setWeight(inputWeight);
		setJob(inputJob);
	}
	//回复信息
	String toString(String type) {
		if (type == "all")
			return Name + ", " + Sex + ", " + Age + ".\n"
				+ "Height is "  + Height 
				+ " and the weight is " + Weight + ".\n"
				+ "His/Her job is " + Job + ".\n";
		else if (type == "Name")
			return Name;
		else if (type == "Sex")
			return Sex;
		else if (type == "Age")
			return Integer.toString(Age);
		else if (type == "Height")
			return Integer.toString(Height);
		else if (type == "Weight")
			return Integer.toString(Weight);
		else if (type == "Job")
			return Job;
		else 
			return "Have You Seen The Hits:-(";
		
	}
	//一系列更改变量的方法
	boolean setName(String input) {
		this.Name = input;
		return true;
	}
	void setSex(String input) {
		this.Sex = input;
	}
	void setHeight(int input) {
		this.Height = input;
	}
	void setWeight(int input) {
		this.Weight = input;
	}
	boolean setAge(int input) {
		this.Age = input;
		return true;
	}
	void setJob(String input) {
		this.Job = input;
	}

}
