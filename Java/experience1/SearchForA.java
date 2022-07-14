package experienceFirst;

public class SearchForA {
	public static void main(String[] args) {
		char[] ready = {'J','a','v','a',' ','i','s',' ','m','y',' ',	//How to make your
						'f','a','v','o','u','r','a','t','e',' ','p',	//teachers mad:-)
						'r','o','g','r','a','m','m','i','n','g',' ',	//I don't like to
						'l','a','n','g','u','a','g'};					//use toCharArray.
		
		int times = 0;
		for (int i = 0; i < ready.length; ++i)
			if ( ready[i] == 'a') times++;
		
		System.out.println("The charactor 'a' appears "+times+" times.");
	}
}
