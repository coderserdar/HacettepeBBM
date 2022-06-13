#include <iostream>
#include <string>
#include <fstream>

#include "arac.h"
#include "list.h"

using namespace std;

int List::sira;

Arac List::getDataFiles(int i)
{
	Arac gArac;
	gArac.setHiz(dataFiles[i].getHiz());
	gArac.setKimlik(dataFiles[i].getKimlik());
	gArac.setRota(dataFiles[i].getRota());
	gArac.setTip(dataFiles[i].getTip());
	return gArac;
}

bool List::add(const Arac &gArac)
{
	if(dataFiles[sira].setHiz(gArac.getHiz())==false)
		return false;
	if(dataFiles[sira].setKimlik(gArac.getKimlik())==false)
		return false;
	if(dataFiles[sira].setRota(gArac.getRota())==false)
		return false;
	if(dataFiles[sira].setTip(gArac.getTip())==false)
		return false;
	sira++;
	return true;
}		

int List::size()
{
	return sira;
}

Arac* List::getFirst()
{
	return dataFiles;
}

int List::getFindSira(const char gKimlik[])
{
	for(int i=0;i<=sira;i++)
	{
		if(!strcmp(gKimlik, dataFiles[i].getKimlik()))
		{
			return i;
		}			
	}
	return -1;
}

Arac* List::getNext(Arac &gArac)
{
	int i=getFindSira(gArac.getKimlik());
	i=i+1;
	return dataFiles+i;
}

bool List::remove(const char gKimlik[ ])
{
	int j=getFindSira(gKimlik);
	if(j!=-1 && find(gKimlik)==true)
	{
		for(int i=j;i<=size();i++)
		{
			dataFiles[i]=dataFiles[i+1];
		}
		sira--;
		return true;	
	}
	else
		return false;
}

bool List::find(const char gKimlik[ ],Arac &gArac)
{
	for(int i = 0; i<=sira; i++)
	{
		if(!strcmp(gKimlik, dataFiles[i].getKimlik()))
		{
			gArac.setHiz(dataFiles[i].getHiz());
			gArac.setRota(dataFiles[i].getRota());
			gArac.setKimlik(dataFiles[i].getKimlik());
			gArac.setTip(dataFiles[i].getTip());
			return true;
		}
	}
	return false;
}

bool List::find(const char gKimlik[ ])
{
	for(int i = 0; i<=sira; i++)
	{
		if(!strcmp(gKimlik, dataFiles[i].getKimlik()))
		{
			return true;
		}
	}
	return false;
}

void List::setSira(int i)
{
	sira=i;
}

bool List::saveList(char nameOfFile[])
{
	dataFile.open(nameOfFile,ios::out);
	if(dataFile.fail()!=0)
		return false;
	else
	{
		for(int i=0;i<sira;i++)
		{
			dataFile << dataFiles[i].getHiz() << "\n";
			dataFile << dataFiles[i].getKimlik() << "\n";
			dataFile << dataFiles[i].getRota() << "\n";
			dataFile << dataFiles[i].getTip() << "\n";
		}
		dataFile.close();
		return true;
	}
}

bool List::loadList(char nameOfFile[])
{
	dataFile.open(nameOfFile,ios::in | ios::nocreate);
	if(!dataFile)
	{
		dataFile.clear();
		return false;
	}
	else
	{
		int i=0;
		do{
			int gRota;
			float gHiz;
			char gKimlik[10];
			char gTip[15];

			dataFile >> gHiz;
			dataFile >> gKimlik;
			dataFile >> gRota;
			dataFile >> gTip;
		
			dataFiles[i].setHiz(gHiz);
			dataFiles[i].setKimlik(gKimlik);
			dataFiles[i].setRota(gRota);
			dataFiles[i].setTip(gTip);
			i++;
		}while(!dataFile.eof());
		sira=i-1;
		dataFile.close();
		return true;
	}
}