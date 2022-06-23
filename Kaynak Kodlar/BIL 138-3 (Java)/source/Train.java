
package vehicle;

import vehicle.Vehicle;


public class Train extends Vehicle{
	public String name;
	private String type;
	private String cabed;
	private String caberth;
	
	public Train(String name, String speed, String age, String type, String cabed,
			String caberth) {
		super(age, speed);
		this.name = name;
		this.type = type;
		this.cabed = cabed;
		this.caberth = caberth;
	}
	
	public String getCabed() {
		return cabed;
	}
	
	public void setCabed(String cabed) {
		this.cabed = cabed;
	}
	
	public String getCaberth() {
		return caberth;
	}
	
	public void setCaberth(String caberth) {
		this.caberth = caberth;
	}
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public String getType() {
		return type;
	}
	
	public void setType(String type) {
		this.type = type;
	}
}
