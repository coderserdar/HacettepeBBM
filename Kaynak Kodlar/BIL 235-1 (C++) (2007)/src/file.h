#ifndef FILE_H_
#define FILE_H_
using namespace std;

class file
{
	public:
		file(string,string,int,string);
		string getFileId()const;
		string getFileName() const;
		void setFileSize(int);
		int getFileSize()const;
		string getFileType() const;
		string FileId;
		string FileName;
		string FileType;
		int FileSize;
};

#endif /*FILE_H_*/
