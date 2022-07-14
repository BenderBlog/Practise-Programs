package Experience2_PetShop;

final class bird extends pet {
	boolean isParrot;
	public bird(int number, String name, int isQuiet) {
		super(number, name);
		isParrot = true;
	}
	public bird(int number, String name) {
		super(number, name);
		isParrot = false;
	}
}
