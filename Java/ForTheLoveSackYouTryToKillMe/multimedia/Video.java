package multimedia;

public class Video extends Multimedia implements Spread {
	int Resolution;
	String Format;
	int Length;
	public Video(String Name, double size, String time, 
			int Resolution, String Format, int Length) {
		super(Name, size, time);
		this.Resolution = Math.abs(Resolution);
		this.Format = Format;
		this.Length =  Math.abs(Length);
	}
	@Override
	public String show() {
		return "Video file: " + toShortString();
	}
	@Override
	public String copy() {
		return "Copied video file: " + toShortString();
	}
	@Override
	public String toString() {
		return super.toString() + "\t" + Resolution + "P\t" + Length + " min\t" + Format + "\t";
	}
	@Override
	public String toShortString() {
		return this.name + "." + Format; 
	}
	public void setLanguage(int Resolution) {
		this.Resolution = Resolution;
	}
	public void setScheme(String Format) {
		this.Format = Format;
	}
}
