
package person;


public class Passenger extends Person{
	private String id;
	private String phone;
	

	public Passenger(String name, String age, String gender, String id, String phone) {
		super(name, age, gender);
		this.id = id;
		this.phone = phone;
	}
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public String getPhone() {
		return phone;
	}
	public void setPhone(String phone) {
		this.phone = phone;
	}
}
