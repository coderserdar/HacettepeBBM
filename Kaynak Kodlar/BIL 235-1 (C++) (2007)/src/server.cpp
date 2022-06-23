#include <iostream.h>
#include <cassert>
#include "server.h"
using namespace std;

server :: server(string Ip,string name,int userlimit)
{
	ServerName = name;
	setUserLimit(userlimit);
	ServerIp = Ip;
	
}

void server :: setUserLimit(int UserLimit)
{
	this->UserLimit=UserLimit;
}

int server :: getUserLimit()const
{
	return UserLimit;
}


string server :: getServerName() const
{
	return ServerName;
}	

string server :: getServerIp() const
{
	return ServerIp;
}

