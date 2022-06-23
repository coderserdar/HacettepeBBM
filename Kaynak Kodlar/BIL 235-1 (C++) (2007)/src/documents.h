#ifndef DOCUMENTS_H_
#define DOCUMENTS_H_
using namespace std;

#include "file.h"

class documents : public file
{
	public:
		documents(string,string,int,string,string,int);
		string getAuthor() const;
		void setPublicationYear(int);
		int getPublicationYear() const;
	protected:
		string Author;
		int PublicationYear;
};

#endif /*DOCUMENTS_H_*/
