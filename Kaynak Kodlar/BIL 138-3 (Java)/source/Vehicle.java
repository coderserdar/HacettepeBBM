
package vehicle;


public class Vehicle {
	private String age;
	private String speed;

	public Vehicle(String age, String speed) {
		this.age = age;
		this.speed = speed;
	}
	public String getAge() {
		return age;
	}
	public void setAge(String age) {
		this.age = age;
	}
	public String getSpeed() {
		return speed;
	}
	public void setSpeed(String speed) {
		this.speed = speed;
	}
}
