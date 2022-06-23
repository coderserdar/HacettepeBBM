#include <iostream.h>
#include <cstring>
#include <cassert>
#include "albums.h"
using namespace std;

albums :: albums(string FileId,string FileName,int FileSize,string FileType,string artist,int AlbumReleaseYear)
:file(FileId,FileName,FileSize,FileType)
{
	setAlbumReleaseYear(AlbumReleaseYear);
	Artist = artist ;
	
}

void albums :: setAlbumReleaseYear(int AlbumReleaseYear)
{
	this->AlbumReleaseYear=AlbumReleaseYear;
}

int albums :: getAlbumReleaseYear()const
{
	return AlbumReleaseYear;
}

string albums :: getArtist()const
{
	return Artist;
}
