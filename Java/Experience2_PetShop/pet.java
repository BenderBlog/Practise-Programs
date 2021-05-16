package Experience2_PetShop;

abstract class pet {
	String name;
	int number;
	//int day;
	public pet(int number, String name){
		this.name = name;
		this.number = number;
		//this.day = day;
	}
	String feed() {
		return "This pet called " + name + ", which number is " + number + " satisfied. Deep Dark Fantasy";
	}
	String feed(dog a) {
		return "This dog called " + name + ", which number is " + number + " satisfied. Bark.";
	}
	String feed(cat b) {
		return "This cat called " + name + ", which number is " + number + " satisfied. Meow.";
	}
	String feed(bird c) {
		return "This bird called " + name + ", which number is " + number + " satisfied. Sing.";
	}
}