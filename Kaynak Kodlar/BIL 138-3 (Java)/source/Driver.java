
package person;

public class Driver extends Captain{
	private String license;
	public Driver(String name, String age, String gender, String corpid, String years,
			String license) {
		super(name, age, gender, corpid, years);
		this.license = license;
	}
	public String getLicense() {
		return license;
	}
	public void setLicense(String license) {
		this.license = license;
	}
}
