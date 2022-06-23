#include <iostream.h>
#include <cstring>
#include <cassert>
#include "movies.h"
using namespace std;

movies :: movies(string FileId,string FileName,int FileSize,string FileType,string Director,int MovieReleaseYear)
:file(FileId,FileName,FileSize,FileType)
{
	setMovieReleaseYear(MovieReleaseYear);
	MovieDirector = Director;
	
}

void movies :: setMovieReleaseYear(int MovieReleaseYear)
{
	this->MovieReleaseYear=MovieReleaseYear;
}

int movies :: getMovieReleaseYear()const
{
	return MovieReleaseYear;
}

string movies :: getMovieDirector()const
{
	return MovieDirector;
}
