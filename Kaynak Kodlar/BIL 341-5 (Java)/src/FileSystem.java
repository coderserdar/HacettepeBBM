public class FileSystem 
{
	
	BPTree bptreeforsize ;
	BPTree bptreeforlocation ;
	public int totalsize ;
	public int totalblocks ;
	
	public FileSystem(int totalsize, int totalblocks) {
		super();
		this.totalsize = totalsize;
		this.totalblocks = totalblocks;
	}

	public int getTotalsize() {
		return totalsize;
	}

	public void setTotalsize(int totalsize) {
		this.totalsize = totalsize;
	}

	public int getTotalblocks() {
		return totalblocks;
	}

	public void setTotalblocks(int totalblocks) {
		this.totalblocks = totalblocks;
	}	
	
}
