#include <iostream.h>
#include "operations.h"
#include <string>
#include <cctype>
#include "StringTokenizer.h"
using namespace std;

ifstream inp;
ofstream out;


void inputOperations(ifstream &,ofstream &);
void createServer(char *,string,string,int);
void shutDownServer(string);
void connectToServer(string,string,string,int);
void disconnectFromServer(string,string);
void shareMovie(string,string,int,string,int,string);
void shareAlbum(string,string,int,string,int,string);
void shareDocument(string,string,int,string,int,string);
void shareExistingFile(string,string);
void searchAndDownloadFile(string,string,string);
void searchAndDownloadFile(string,string,string,string);

int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		cout << "The parameters are wrong!";
	}
	
	else
	{
		inp.open(argv[1],ios::in);
		if(!inp.is_open()){
		cout << "Input File can not be opened! " << endl;
		return 1;
		}
				
		out.open(argv[2]);
		if(!out.is_open()){
			cout << "Output File can not be opened! " << endl;
			out.close();
			exit(EXIT_FAILURE);
		}
	}
	inputOperations(inp,out);
	return 0;
}//end of main function

void inputOperations(ifstream &inp,ofstream &out)
{
	server s("","",0);
	vector<peer> vpeer;
	vector<albums>valbums;
	vector<documents>vdocuments;
	vector<movies>vmovies;
	vector<file>vfile;
	string command,choice,time,limit,ServerIp,ServerName,PeerIp,NickName,author,artist,director,id,line,name,type,size,year,speed;
	int speed2,limit2,size2,year2,condition;
	operations operating;
	while(1)
	{
		getline(inp,line);
		if(line == "")
			break;
		else
		{
			
			StringTokenizer token(line , " ");
			time = token.nextToken();
			out << time << " ";
			line = token.remainingString();
			command = token.nextToken( "(" );
			line = token.remainingString();
			if(command == "CreateServer")
			{
				ServerIp = token.nextToken(",");
				line = token.remainingString();
				ServerName = token.nextToken(",");
				line = token.remainingString();
				limit = token.nextToken(")");
				limit2 = atoi(limit.c_str());
				s.ServerIp=ServerIp;
				s.ServerName=ServerName;
				s.UserLimit=limit2;
				condition = operating.createServer(s);
				if(condition == 1)
					out << "Server Created" << "\n";
			}//createServer yordamýna buradan gidiyor
			
			else if(command == "ShutDownServer")
			{
				ServerIp = token.nextToken(",");
				//condition = operating.shutDownServer(ServerIp,vserver);
				condition = operating.shutDownServer(ServerIp);
				if(condition == 1)
						out << "Server shut down";
			}//shutDownServer yordamýna buradan gidiyor;
			
			else if(command == "ConnectToServer")
			{
				ServerIp = token.nextToken(",");
				line = token.remainingString();
				NickName = token.nextToken(",");
				line = token.remainingString();
				PeerIp = token.nextToken(",");
				line = token.remainingString();
				speed = token.nextToken(")");
				speed2 = atoi(speed.c_str());
				peer p(PeerIp,NickName,speed2,0,0);
				condition = operating.connectToServer(ServerIp,p,&s);
				//condition = operating.connectToServer(ServerIp,NickName,PeerIp,speed2);
				if(condition == 1)
					out << "Peer(" << p.PeerIp << ")"<< " connected to " << ServerName << "\n";
				else if(condition == 2){
					out << "Peer(" << p.PeerIp << ")"<< " connected to " << ServerName << "\n";
					out << "*** ERROR! Connection refused, server reached user limit" << "\n";
				}
				else{
					out << "Peer(" << p.PeerIp << ")"<< " connected to " << ServerName << "\n";
					out << "*** ERROR! Server IP invalid" << "\n";
				}
			}//connectToServer yordamýna buradan gidiyor
			
			else if(command == "ShareMovie")
			{
				id = token.nextToken(",");
				line = token.remainingString();
				name = token.nextToken(",");
				line = token.remainingString();
				size = token.nextToken(",");
				size2 = atoi(size.c_str());
				line = token.remainingString();
				director = token.nextToken(",");
				line = token.remainingString();
				year = token.nextToken(",");
				year2 = atoi(year.c_str());
				line = token.remainingString();
				PeerIp = token.nextToken(")");
				movies m(id,name,size2,"M",director,year2);
				condition = operating.shareMovie(m,PeerIp,s);
				if(condition == 1)
				{
					vmovies.push_back(m);
					out << "Peer(" << PeerIp  << " shares movie" << name << "\n";
				}
				else
				{
					out << "Peer(" << PeerIp  << " shares movie" << name << "\n";
					out << "*** ERROR! Invalid ID" << "\n";
				}
			}//shareMovie yordamýna buradan gidiyor
			
			else if(command == "ShareDocument")
			{
				id = token.nextToken(",");
				line = token.remainingString();
				name = token.nextToken(",");
				line = token.remainingString();
				size = token.nextToken(",");
				size2 = atoi(size.c_str());
				line = token.remainingString();
				author = token.nextToken(",");
				line = token.remainingString();
				year = token.nextToken(",");
				year2 = atoi(year.c_str());
				line = token.remainingString();
				PeerIp = token.nextToken(")");
				documents d(id,name,size2,"D",author,year2);
				condition = operating.shareDocument(d,PeerIp,s);
				if(condition == 1)
				{
					vdocuments.push_back(d);
					out << "Peer(" << PeerIp  << " shares document" << name << "\n";
				}
				else
				{
					out << "Peer(" << PeerIp  << " shares movie" << name << "\n";
					out << "*** ERROR! Invalid ID" << "\n";
				}
			}//shareDocument yordamýna buradan gidiyor
			
			else if(command == "ShareAlbum")
			{
				
				id = token.nextToken(",");
				line = token.remainingString();
				name = token.nextToken(",");
				line = token.remainingString();
				size = token.nextToken(",");
				size2 = atoi(size.c_str());
				line = token.remainingString();
				artist = token.nextToken(",");
				line = token.remainingString();
				year = token.nextToken(",");
				year2 = atoi(year.c_str());
				line = token.remainingString();
				PeerIp = token.nextToken(")");
				albums a(id,name,size2,"A",artist,year2);
				condition = operating.shareAlbum(a,PeerIp,s);
				if(condition == 1)
				{
					valbums.push_back(a);
					out << "Peer(" << PeerIp  << " shares album" << name << "\n";
				}
				else
				{
					out << "Peer(" << PeerIp  << " shares album" << name << "\n";
					out << "*** ERROR! Invalid ID" << "\n";
				}
			}//shareAlbum yordamýna buradan gidiyor
			
			else if (command == "ShareExistingFile")
			{
				PeerIp = token.nextToken(",");
				line = token.remainingString();
				id = token.nextToken(")");
				condition = operating.shareExistingFile(PeerIp,id);
				if(condition == 1)
					out << "Peer(" << PeerIp << ")" << " also shares file" << id << "\n";
				else
					out << "*** ERROR! Peer not found" << "\n";
			}//shareExistingFile yordamýna buradan gidiliyor burada da ayný sorun var
			
			else if (command == "SearchAndDownloadFile")
			{
				
				PeerIp = token.nextToken(",");
				line = token.remainingString();
				choice = token.nextToken(",");
				line = token.remainingString();
				if(choice == "BYNAME")
				{
					name = token.nextToken(",");
					condition = operating.SearchAndDownloadFile(PeerIp,choice,name);
					if(condition == 1)
						out << "Peer(" << PeerIp << ")" << "starts search by name for" << name << "\n";
					else
					{
						out << "Peer(" << PeerIp << ")" << "starts search by name for" << name << "\n";
						out << "*** ERROR! File found but peer(s) not available" << "\n" ;
					}
				}
				
				else
				{
					type = token.nextToken(",");
					line = token.remainingString();
					name = token.nextToken(",");
					condition = operating.SearchAndDownloadFile(PeerIp,choice,type,name);
					if(condition == 1)
					{
						out << "Peer(" << PeerIp << ")" << "starts search by type for" << name << "\n";
					}
					else
					{
						out << "Peer(" << PeerIp << ")" << "starts search by type for" << name << "\n";
						out << "*** ERROR! File not found" << "\n" ;
					}
				}
				
				
			}//searchAndDownloadFile yordamýna buradan gidiliyor burada da ayný sorun var
			
			else if (command == "DisconnectFromServer")
			{
				PeerIp = token.nextToken(",");
				line = token.remainingString();
				ServerIp = token.nextToken(")");
				condition = operating.disconnectFromServer(PeerIp,&s);
				if(condition == 1)
					out << "Peer(" << PeerIp << ")" << "disconnected from" << ServerIp << "\n";
				else
				{
					out << "Peer(" << PeerIp << ")" << "disconnected from" << ServerIp << "\n";
					out << "*** ERROR! Peer not found" << "\n";
				}
			}//DisconnectFromServer yordamýna buradan gidiliyor burada da ayný sorun var
		}
	}

}//end of the inputOperations function
