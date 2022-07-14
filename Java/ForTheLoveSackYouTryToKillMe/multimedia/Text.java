package multimedia;

public class Text extends Multimedia implements Spread{
	String Language;
	String codingScheme;
	String content;
	public Text(String Name, double size, String time, 
			String Language, String codingScheme, String content) {
		super(Name, size, time);
		this.Language = Language;
		this.codingScheme = codingScheme;
		this.content =  content;
	}
	@Override
	public String show() {
		return "Text file: " + toShortString();
	}
	@Override
	public String copy() {
		return "Copied text file: " + toShortString();
	}
	@Override
	public String toString() {
		return super.toString() + "\t" + content.length() + "words\t" + Language + "\t" + codingScheme;
	}
	@Override
	public String toShortString() {
		return this.name + "." + codingScheme; 
	}
	public void setLanguage(String Language) {
		this.Language = Language;
	}
	public void setScheme(String codingScheme) {
		this.codingScheme = codingScheme;
	}
}
