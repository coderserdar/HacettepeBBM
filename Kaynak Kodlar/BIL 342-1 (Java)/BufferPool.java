public class BufferPool {
	public int pageNumber;
	public String pageContext;	
	public int clusterId;
	public int pinCount;
	public int dirty;
	
	public int getClusterId() {
		return clusterId;
	}

	public void setClusterId(int clusterId) {
		this.clusterId = clusterId;
	}

	public int getDirty() {
		return dirty;
	}

	public void setDirty(int dirty) {
		this.dirty = dirty;
	}

	public String getPageContext() {
		return pageContext;
	}

	public void setPageContext(String pageContext) {
		this.pageContext = pageContext;
	}

	public int getPageNumber() {
		return pageNumber;
	}

	public void setPageNumber(int pageNumber) {
		this.pageNumber = pageNumber;
	}

	public int getPinCount() {
		return pinCount;
	}

	public void setPinCount(int pinCount) {
		this.pinCount = pinCount;
	}

	public BufferPool(int pageNumber, String pageContext, int clusterId, int pinCount, int dirty) {
		super();
		this.pageNumber = pageNumber;
		this.pageContext = pageContext;
		this.clusterId = clusterId;
		this.pinCount = pinCount;
		this.dirty = dirty;
	}
}
