
package trip;

public class TrainTrip extends Trip{
	private String machinistcorid;
	private String trainname;
	
	public TrainTrip(String tripno, String depstaname, String arrstaname,
			String deptime, String machinistcorid, String trainname) {
		super(tripno, depstaname, arrstaname, deptime);
		this.machinistcorid = machinistcorid;
		this.trainname = trainname;
	}
	public String getMachinistcorid() {
		return machinistcorid;
	}
	public void setMachinistcorid(String machinistcorid) {
		this.machinistcorid = machinistcorid;
	}
	public String getTrainname() {
		return trainname;
	}
	public void setTrainname(String trainname) {
		this.trainname = trainname;
	}
}
