package Experience2_PetShop;
import java.util.ArrayList;

public class takeaway {
	static ArrayList<pet> gohome(ArrayList<pet> store, int index) {
		int nail = 0;
		for (pet j : store) {
			nail++;
			if (j.number == index) {
				store.remove(j);
				break;
			}
			if (nail == 11) {
				break;						
			}
		}
		if (nail > 10) {
			System.out.println("无法找到该宠物。");
		}
		return store; 
	}
}
