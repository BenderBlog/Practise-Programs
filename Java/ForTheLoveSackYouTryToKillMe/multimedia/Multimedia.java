package multimedia;

public abstract class Multimedia {
	
	String name;
	double size;
	String time;
	
	public Multimedia(String name, double size, String time) {
		this.name = name;
		this.size = Math.abs(size);
		this.time = time;
	}
	
	public String toString() {
		return name + "\t" + String.format("%.2f", size) + " MiB \t" + time;
	}
	
	public void newName(String newname) {
		this.name = newname;
	}
}
