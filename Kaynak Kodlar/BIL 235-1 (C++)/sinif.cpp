#include <iostream>
#include "arac.h"
using namespace std;

void Arac::yaz(int sira)
{
	cout << "\n\n****************************************" << endl;
	cout << "**  "<<sira<<". Gemi icin Girdiginiz Bilgiler  **" << endl; 
	cout << "****************************************" << endl;
	cout << " Geminin Rotasi          : ";
	cout << rota << endl; 
	cout << " Geminin Hizi            : ";
	cout << hiz << endl;
	cout << " Geminin Borda Numarasi  : ";
	cout << borda << endl;
	cout << " Geminin Tipi            : ";
	cout << tip << endl;
	cout << "\n" << endl;
}

bool Arac::setRota(int a)
{
	if (a>=0 && a<360)
	{
		rota = a;
		return true;
	}
	else 
	{
		return false;
	}
}

bool Arac::setHiz(float b)
{
	if (b>=0 && b<=150)
	{
		hiz = b;
		return true;
	}
	else 
	{
		return false;
	}
}

void Arac::setBorda(char c[10])
{
	int i=0;
	for (i=0;i<=10;i++)
	{
		borda[i] = c[i];
	}
}

void Arac::setTip(char d[15])
{
	int j=0;
	for (j=0;j<=15;j++)
	{
		tip[j]=d[j];
	}
}