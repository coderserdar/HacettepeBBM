#ifndef OPERATIONS_H_
#define OPERATIONS_H_
#include <vector>
#include <iostream.h>
#include <cstring>
#include <cassert>
#include <fstream>
#include <sstream>
#include "file.h"
#include "movies.h"
#include "server.h"
#include "documents.h"
#include "albums.h"
#include "peer.h"
using namespace std;

class operations 
{
	public:
		operations();
		vector<albums> vfunction(vector <albums>);
		int createServer(server);
		int shutDownServer(string);
		int connectToServer(string,peer,server*);
		int disconnectFromServer(string,server*);
		int shareMovie(movies,string,server);
		int shareAlbum(albums,string,server);
		int shareDocument(documents,string,server);
		int shareExistingFile(string,string);
		int SearchAndDownloadFile(string,string,string);
		int SearchAndDownloadFile(string,string,string,string);
	
};



#endif /*OPERATIONS_H_*/
