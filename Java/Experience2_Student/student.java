/*
 *  2021, Written by SuperBart@bilibili, licensed under the Unlicense
 *  Consider Subscribe Me at Bilibili!
 */

package Experience2_Student;
import java.util.ArrayList;

//继承自person和Comparable接口
class student extends person implements Comparable<student>{
	private int Number;
	private ArrayList<String> Class = new ArrayList<String>();
	private double GPA;
	private int Grade;
	private String College;
	
	//构造函数
	public student(String inputName, String inputSex, int inputAge, 
			int inputHeight, int inputWeight, int inputNumber,
			double inputGPA, int inputGrade, String inputCollege) {
		//调用父类的构造方法（结果还是使用了super）
		super(inputName, inputSex, inputAge, inputHeight, inputWeight, "Student");
		setNumber(inputNumber);
		setGPA(inputGPA);
		setGrade(inputGrade);
		setCollege(inputCollege);
	}
	//回复信息，重写版
	String toString(String type) {
		if (type == "all")
			return super.toString("all") +
				   "Student Number is " + Number + ", GPA is " + GPA +
				   ".\nA " + Grade + " student at " + College + ".\n" + Class + printClass();
		else if (type == "Name")
			return super.toString("Name");
		else if (type == "Sex")
			return super.toString("Sex");
		else if (type == "Age")
			return super.toString("Age");
		else if (type == "Height")
			return super.toString("Height");
		else if (type == "Weight")
			return super.toString("Weight");
		else if (type == "Job")
			return super.toString("Job");
		else if (type == "Number")
			return Integer.toString(Number);
		else if (type == "GPA")
			return Double.toString(GPA);
		else if (type == "Grade")
			return Integer.toString(Grade);
		else if (type == "College")
			return College;
		else if (type == "Class") {
			return Class + printClass();
		}
		else 
			return "Have You Seen The Hits:-(";
		
	}
	String printClass() {
		if (Class.isEmpty() == false) {
			return "\nGot " + Class.size() + " class(es).";			
		} else {
			return "He didn't Choose any Class!";
		}
	}
	//一堆修改方法
	boolean setNumber(int inputNumber) {
		this.Number = inputNumber;
		return true;
	}
	boolean setGPA(double inputGPA) {
		this.GPA = inputGPA;
		return true;
	}
	boolean setGrade(int inputGrade) {
		this.Grade = inputGrade;
		return true;
	}
	boolean setCollege(String inputCollege) {
		this.College = inputCollege;
		return true;
	}
	//加课程与删除课程
	boolean addCource (String inputClass) {
		if (Class.isEmpty()==true || Class.contains(inputClass)==false) {
			Class.add(inputClass);
			return true;
		} else {
			return false;
		}
	}
	boolean deleteCourse (String inputClass) {
		if (Class.contains(inputClass) == true) {
			Class.remove(inputClass);
			return true;
		} else {
			return false;
		}
	}
	//按GPA排序，重写Comparable接口的compareTo方法
	//详情请看 Double.class 的 compareTo 方法，能省事情就要省:-)
	public int compareTo(student o) {
		return Double.compare(o.GPA, GPA);
	}
}
