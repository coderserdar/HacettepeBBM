#include <iostream>
#include <cctype>
#include "arac.h"
#include "list.h"

using namespace std;

Arac::Arac()
{
	hiz=0;
	rota=0;
	kimlik = "UNDEFINED";
	tip = "UNDEFINED";
}

Arac::Arac(const Arac &gArac)
{
	hiz=gArac.hiz;
	rota=gArac.rota;
	kimlik = new char[checkLenght(gArac.getKimlik())];
	tip = new char[checkLenght(gArac.getTip())];
	strcpy(kimlik, gArac.kimlik);
	strcpy(tip, gArac.tip);
}

void Arac::yaz()const
{
	cout << "Rotasi: ";
	cout << rota; 
	cout << "   Hizi: ";
	cout << hiz;
	cout << "   Kimlik Bilgisi: ";
	cout << kimlik;
	cout << "   Tipi: ";
	cout << tip;
	cout << "\n" << endl;
}

bool Arac::setRota(int gRota)
{
	if (gRota >=0 && gRota<360)
	{
		rota = gRota;
		return true;
	}
	else 
		return false;
}

bool Arac::setHiz(float gHiz)
{
	if (gHiz>=0 && gHiz<=150)
	{
		hiz=gHiz;
		return true;
	}
	else 
		return false;
}

bool Arac::setKimlik(char *gKimlik)
{
	kimlik=new char[11];

	if(checkKimlik(gKimlik)==false)
		return false;
	else
	{
		for(int i=0; i<=10; i++)
		{
			kimlik[i]=gKimlik[i];
		}
		return true;
	}
}

bool Arac::setTip(char *gTip)
{
	tip=new char[16];

	if(checkTip(gTip)==false)
		return false;
	else
	{
		for(int i=0; i<=15; i++)
		{
			tip[i]=gTip[i];
		}
		return true;
	}
}

bool Arac::checkTip(char *tip)
{
	int lenght=checkLenght(tip);
	if( lenght>16 )
		return false;
	for (int i=0;i<(lenght-1);i++)
	{
		if(!isalpha(tip[i]))
			return false;
	}
	return true;
}

bool Arac::checkKimlik(char *kimlik)
{
	int lenght=checkLenght(kimlik);
	if( lenght>11 )
		return false;
	for (int i=0;i<(lenght-1);i++)
	{
		if(!isalnum(kimlik[i]))
			return false;
	}
	return true;
}

int Arac::checkLenght(char *dizi)
{
	int index=0;
	while(dizi[index++]!='\0' && index < 20){}
	return index;
}

float Arac::getHiz()const
{
	return hiz;
}

int Arac::getRota()const
{
	return rota;
}

char* Arac::getKimlik()const
{
	return kimlik;
}

char* Arac::getTip()const
{
	return tip;
}
