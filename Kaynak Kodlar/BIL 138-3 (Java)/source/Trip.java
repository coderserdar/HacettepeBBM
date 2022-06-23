
package trip;

public class Trip {
	private String tripno;
	private String depstaname;
	private String arrstaname;
	private String deptime;
	
	public Trip(String tripno, String depstaname, String arrstaname, String deptime) {
		this.tripno = tripno;
		this.depstaname = depstaname;
		this.arrstaname = arrstaname;
		this.deptime = deptime;
	}
	
	public String getArrstaname() {
		return arrstaname;
	}
	
	public void setArrstaname(String arrstaname) {
		this.arrstaname = arrstaname;
	}
	
	public String getDepstaname() {
		return depstaname;
	}
	
	public void setDepstaname(String depstaname) {
		this.depstaname = depstaname;
	}
	
	public String getDeptime() {
		return deptime;
	}

	public void setDeptime(String deptime) {
		this.deptime = deptime;
	}
	
	public String getTripno() {
		return tripno;
	}
	
	public void setTripno(String tripno) {
		this.tripno = tripno;
	}
	
}
