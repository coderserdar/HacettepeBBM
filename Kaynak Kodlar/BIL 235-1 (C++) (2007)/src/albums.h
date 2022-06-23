#ifndef ALBUMS_H_
#define ALBUMS_H_
using namespace std;

#include "file.h"

class albums : public file
{
	public:
		albums(string,string,int,string,string,int);
		string getArtist() const;
		void setAlbumReleaseYear(int);
		int getAlbumReleaseYear() const;
		string Artist;
		int AlbumReleaseYear;
};

#endif /*ALBUMS_H_*/
