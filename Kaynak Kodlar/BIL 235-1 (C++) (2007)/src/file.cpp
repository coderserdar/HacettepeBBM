#include <iostream.h>
#include <cstring>
#include <cassert>
#include "file.h"
using namespace std;

file :: file(string Id,string name,int size,string type)
{
	FileName = name ;
	setFileSize(size);
	FileId = Id ;
	FileType = type;
}

void file :: setFileSize(int FileSize)
{
	this->FileSize=FileSize;
}

int file :: getFileSize()const
{
	return FileSize;
}

string file :: getFileName() const
{
	return FileName;
}	

string file :: getFileId() const
{
	return FileId;
}

string file :: getFileType() const
{
	return FileType;
}
