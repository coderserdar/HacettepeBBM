
public class DirectoryStruct {
	
	public String fileName;
	public int size;
	public int firstClusterId;
	public boolean deletedBit;
	
	public DirectoryStruct(String fileName, int size, int firstClusterId, boolean deletedBit) {
		super();
		this.fileName = fileName;
		this.size = size;
		this.firstClusterId = firstClusterId;
		this.deletedBit = deletedBit;
	}
	public boolean isDeletedBit() {
		return deletedBit;
	}
	public void setDeletedBit(boolean deletedBit) {
		this.deletedBit = deletedBit;
	}
	public String getFileName() {
		return fileName;
	}
	public void setFileName(String fileName) {
		this.fileName = fileName;
	}
	public int getFirstClusterId() {
		return firstClusterId;
	}
	public void setFirstClusterId(int firstClusterId) {
		this.firstClusterId = firstClusterId;
	}
	public int getSize() {
		return size;
	}
	public void setSize(int size) {
		this.size = size;
	}

}
