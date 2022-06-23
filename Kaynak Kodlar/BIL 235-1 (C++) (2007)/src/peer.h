#ifndef PEER_H_
#define PEER_H_
#include "file.h"
#include "list.h"
using namespace std;

class peer
{
	public:
		peer(string,string,int,int,int);
		string getNickName() const;
		string getPeerIp() const;
		void setUploadSpeed(int);
		int getUploadSpeed() const;
		void setCurrentDownload(int);
		int getCurrentDownload() const;
		void setCurrentUpload(int);
		int getCurrentUpload() const;
		string PeerIp;
		string NickName;
		int UploadSpeed;
		int CurrentDownload;
		int CurrentUpload;
		list <file> filelist;
		
	
};

#endif /*PEER_H_*/
