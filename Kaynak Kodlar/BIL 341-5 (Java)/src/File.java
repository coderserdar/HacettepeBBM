public class File {
	
	public String fileName ;
	public int fileSize ;
	public int fileBlocks ;
	
	public File(String fileName, int fileSize) {
		super();
		this.fileName = fileName;
		this.fileSize = fileSize;
	}

	public String getFileName() {
		return fileName;
	}

	public void setFileName(String fileName) {
		this.fileName = fileName;
	}

	public int getFileSize() {
		return fileSize;
	}

	public void setFileSize(int fileSize) {
		this.fileSize = fileSize;
	}

	public int getFileBlocks() {
		return fileBlocks;
	}

	public void setFileBlocks(int fileBlocks) {
		this.fileBlocks = fileBlocks;
	}
	
	
}
