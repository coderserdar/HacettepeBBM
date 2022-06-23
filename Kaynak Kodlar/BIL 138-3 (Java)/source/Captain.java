
package person;

public class Captain extends Person{
	
	private String corpid;
	private String years;
	public Captain(String corpid, String name, String gender, String age, String years) {
		super(name, age, gender);
		this.corpid = corpid;
		this.years = years;
	}

	
	public String getCorpid() {
		return corpid;
	}
	
	public void setCorpid(String corpid) {
		this.corpid = corpid;
	}
	
	public String getYears() {
		return years;
	}
	
	public void setYears(String years) {
		this.years = years;
	}
}
