
package trip;

public class BusTrip extends Trip{
	private String drivercorid;
	private String busplate;
	
	public BusTrip(String tripno, String depstaname, String arrstaname,
			String deptime, String drivercorid, String busplate) {
		super(tripno, depstaname, arrstaname, deptime);
		this.drivercorid = drivercorid;
		this.busplate = busplate;
	}
	public String getBusplate() {
		return busplate;
	}
	public void setBusplate(String busplate) {
		this.busplate = busplate;
	}
	public String getDrivercorid() {
		return drivercorid;
	}
	public void setDrivercorid(String drivercorid) {
		this.drivercorid = drivercorid;
	}
}
