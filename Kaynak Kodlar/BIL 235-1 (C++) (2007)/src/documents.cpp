#include <iostream.h>
#include <cstring>
#include <cassert>
#include "documents.h"
using namespace std;

documents :: documents(string FileId,string FileName,int FileSize,string FileType,string author,int PublicationYear)
:file(FileId,FileName,FileSize,FileType)
{
	setPublicationYear(PublicationYear);
	Author = author ;
	
}

void documents :: setPublicationYear(int PublicationYear)
{
	this->PublicationYear=PublicationYear;
}

int documents :: getPublicationYear()const
{
	return PublicationYear;
}

string documents :: getAuthor()const
{
	return Author;
}
