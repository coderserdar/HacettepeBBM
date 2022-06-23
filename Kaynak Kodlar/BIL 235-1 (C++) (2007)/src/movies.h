#ifndef MOVIES_H_
#define MOVIES_H_
#include "file.h"
using namespace std;

class movies : public file
{
	public:
		movies(string,string,int,string,string,int);
		string getMovieDirector() const;
		void setMovieReleaseYear(int);
		int getMovieReleaseYear() const;
	protected:
		string MovieDirector;
		int MovieReleaseYear;
};

#endif /*MOVIES_H_*/
