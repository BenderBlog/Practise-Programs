package Experience2_PetShop;
import java.util.ArrayList;

public class welcome {
	static ArrayList<pet> newDoge(ArrayList<pet> store, int inputNumber, String inputName, String inputKind){
		if (store.size() > 10) {
			System.out.println("Full!");
			return store;
		} else {
			store.add(new dog(inputNumber, inputName, inputKind));
			return store;
		}
	}
	static ArrayList<pet> newMeow(ArrayList<pet> store, int inputNumber, String inputName, int isCute){
		if (store.size() > 10) {
			System.out.println("Full!");
			return store;
		}
		if (isCute == 0)
			store.add(new cat(inputNumber, inputName, 0));
		else
			store.add(new cat(inputNumber, inputName, 1));
		return store;
	}
	static ArrayList<pet> newBirdy(ArrayList<pet> store, int inputNumber, String inputName, int isParrot){
		if (store.size() == 10) {
			System.out.println("Full!");
			return store;
		}
		if (isParrot == 1)
			store.add(new bird(inputNumber, inputName, isParrot));
		else
			store.add(new bird(inputNumber, inputName));
		return store;
	}
	
}
