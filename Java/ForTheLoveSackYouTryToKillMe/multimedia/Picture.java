package multimedia;

public class Picture extends Multimedia implements Spread {
	int x;
	int y;
	String Format;
	public Picture(String Name, double size, String time, 
			int x, int y, String Format) {
		super(Name, size, time);
		this.x = Math.abs(x);
		this.y = Math.abs(y);
		this.Format = Format;
	}
	@Override
	public String show() {
		return "Picture file: " + toShortString();
	}
	@Override
	public String copy() {
		return "Copied picture file: " + toShortString();
	}
	@Override
	public String toString() {
		return super.toString() + "\t" + x + "\t" + y + "\t" + Format ;
	}
	@Override
	public String toShortString() {
		return this.name + "." + Format; 
	}
	public void setLanguage(int x, int y) {
		this.x = x;
		this.y = y;
	}
	public void setScheme(String Format) {
		this.Format = Format;
	}
}
