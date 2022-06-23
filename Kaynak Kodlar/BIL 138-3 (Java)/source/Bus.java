
package vehicle;

public class Bus extends Vehicle{
	
	private String plate;
	private String seatcap;
	public Bus(String plate, String speed, String age, String seatcap) {
		super(age, speed);
		this.plate = plate;
		this.seatcap = seatcap;
	}

	public String getPlate() {
		return plate;
	}
	public void setPlate(String plate) {
		this.plate = plate;
	}
	public String getSeatcap() {
		return seatcap;
	}
	public void setSeatcap(String seatcap) {
		this.seatcap = seatcap;
	}
}
