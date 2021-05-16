package Experience2_PetShop;

final class cat extends pet {
	boolean cute;
	public cat(int number, String name, int a) {
		super(number, name);
		if (a == 0)
			this.cute = false;
		else
			this.cute = true;
	}
}
