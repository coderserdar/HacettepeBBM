#include <iostream.h>
#include <cstring>
#include <cassert>
#include "peer.h"
using namespace std;

peer :: peer(string Ip,string name,int uploadspeed,int currentdownload,int currentupload)
{
	NickName = name ;
	setCurrentUpload(currentupload);
	setCurrentDownload(currentdownload);
	setUploadSpeed(uploadspeed);
	PeerIp = Ip ;
	
}

void peer :: setUploadSpeed(int UploadSpeed)
{
	this->UploadSpeed=UploadSpeed;
}

int peer :: getUploadSpeed()const
{
	return UploadSpeed;
}


void peer :: setCurrentDownload(int CurrentDownload)
{
	this->CurrentDownload=CurrentDownload;
}

int peer :: getCurrentDownload()const
{
	return CurrentDownload;
}

void peer :: setCurrentUpload(int CurrentUpload)
{
	this->CurrentUpload=CurrentUpload;
}

int peer :: getCurrentUpload()const
{
	return CurrentUpload;
}

string peer :: getNickName() const
{
	return NickName;
}	

string peer :: getPeerIp() const
{
	return PeerIp;
}
