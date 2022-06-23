#ifndef SERVER_H_
#define SERVER_H_
#include "peer.h"
#include "list.h"
#include <string>
#include <cstring>
using namespace std;
class server
{
	public:
		server(string,string,int);
		string getServerName() const;
		string getServerIp() const;
		void setUserLimit(int);
		int getUserLimit() const;
		string ServerIp;
		string ServerName;
		int UserLimit;
		list <file> StubFiles;
		list <peer> PeerList;
		
};

#endif /*SERVER_H_*/
