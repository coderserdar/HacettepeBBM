#include "operations.h"
#include <iterator>
#include <list>
using namespace std;

operations :: operations()
{
	
}

int operations :: createServer(server s)
{
	return 1;
}

int operations :: shutDownServer(string ServerIp)
{
	return 1;
}

int operations :: connectToServer(string ServerIp,peer p,server *s)
{
	if(ServerIp.compare((*s).ServerIp)==0)
	{
		(*s).PeerList.push_back(p);
		(*s).setUserLimit((*s).UserLimit-1);
		if((*s).UserLimit<0)
		{
			(*s).PeerList.pop_back();
			return 2;
		}
		return 1;
	}
	return 0;
}
int operations :: shareMovie(movies m,string PeerIp,server s)
{
	list<peer>::const_iterator it;
	it=s.PeerList.begin(); 
	while(it!=s.PeerList.end())
	{
		if(PeerIp.compare(static_cast<peer>(*it).PeerIp)==0)
		{
			return 1;
		}
		it++;
	}
	return 0;
}

int operations :: shareDocument(documents d,string PeerIp,server s)
{
	list<peer>::const_iterator it;
	it=s.PeerList.begin(); 
	while(it!=s.PeerList.end())
	{
		if(PeerIp.compare(static_cast<peer>(*it).PeerIp)==0)
		{
			return 1;
		}
		it++;
	}
		return 0;
}

int operations :: shareAlbum(albums a,string PeerIp,server s)
{
	list<peer>::const_iterator it;
	it=s.PeerList.begin(); 
	while(it!=s.PeerList.end())
	{
		if(PeerIp.compare(static_cast<peer>(*it).PeerIp)==0)
		{
			return 1;
		}
		it++;
	}
	return 0;
}

int operations :: shareExistingFile(string PeerIp,string id)
{
	peer p(PeerIp,"",0,0,0);
	if(PeerIp == p.PeerIp)
	{
			file f(id,"",0,"");
			if(id == f.FileId)
			{
				return 1;
			}
	}
	return 0;
}

int operations :: disconnectFromServer(string PeerIp,server *s)
{
	list<peer>::const_iterator it;
	it=(*s).PeerList.begin(); 
	while(it!=(*s).PeerList.end())
	{
		if(PeerIp.compare(static_cast<peer>(*it).PeerIp)==0)
		{
			return 1;
		}
		it++;
	}
	return 0;
}

int operations :: SearchAndDownloadFile(string PeerIp,string choice,string name)
{
	return 1;
}

int operations :: SearchAndDownloadFile(string PeerIp,string choice,string type,string name)
{
	return 0;
}
