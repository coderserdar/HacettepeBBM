#include <iostream>
#include "sinif.h"

using namespace std;

void main(void)
{
	int gRota;
	float gHiz;
	char gBorda[10];
	char gTip[15];
	int secim,a,j,i,kayit_no;
	char alt_secim;
	Arac gemi[1000];



	do{
		cout << "\n\n****************************************" << endl;
		cout << "*  Gemi Takip Programina Hosgeldiniz   *" << endl;
		cout << "****************************************" << endl;
		cout << "*  1. Kayit Girisi                     *" << endl;
		cout << "*  2. Kayit Listeleme                  *" << endl;
		cout << "****************************************" << endl;
		cout << "*  3. Cikis                            *" << endl;
		cout << "****************************************\n" << endl;
		cout << " Secminiz: ";
		cin >> secim;



		switch(secim)
		{

		case 1:
			{
				for (i=1;alt_secim != 'h' && alt_secim != 'H' && i<=1000;i++)
				{
					cout << "\n\n****************" << endl;
					cout << "* Kayit No: "<<i<<"  *" << endl;
					cout << "****************\n" << endl;

					do{
						cout << " Geminin rotasini giriniz ( 0-359 )                  : ";
						cin >> 	gRota;
						if(gemi[i].setRota(gRota)==false)
						{
							cout << " ! ! ! Yanlis bir giris yaptiniz            ! ! !" << endl;
							cout << " ! ! ! Rotanin degerleri 0-360 arasi olmali ! ! !"<< endl;
						}
					}while(gemi[i].setRota(gRota)==false);

					do{
						cout << " Geminin hizini giriniz  ( 0-150 )                   : ";
						cin >> gHiz;
						if(gemi[i].setHiz(gHiz)==false)
						{
							cout << " ! ! ! Yanlis bir giris yaptiniz            ! ! !"<< endl;
							cout << " ! ! ! Surat degeri 0-150 knot arasi olmali ! ! !"<< endl;
						}
					}while(gemi[i].setHiz(gHiz)==false);

					cout << " Geminin borda numarasini giriniz ( F242 gibi )      : ";
					cin >> gBorda;
					gemi[i].setBorda(gBorda);
					
					cout << " Geminin tipini giriniz ( Firkateyn gibi )           : ";
					cin >> gTip;
					gemi[i].setTip(gTip);
					cout << "\n\n Baska bir kayit girmek istyormusunuz? (E\\H) ";
					cin >> alt_secim;
				}
			}

		case 2:
			{
				cout << "\n\n****************************************" << endl;
				cout << "*         Kayit  Listeleme             *" << endl;
				cout << "****************************************" << endl;
				cout << "*  1. Tum Kayitlari Listele            *" << endl;
				cout << "*  2. Secili Kayit Listele             *" << endl;
				cout << "****************************************" << endl;
				cout << " Seciminiz: ";
				cin >> a;
				
				switch (a)
				{
				case 1:
					{
						for(j=1;j<=i-1;j++)
						{
							gemi[j].yaz(j);
						}
					}

				case 2:
				{
					cout << "\n\n****************************************" << endl;
					cout << "**   Kayit Numarasini Giriniz: ";
					cin >> kayit_no;
					cout << "****************************************" << endl;
					
					gemi[kayit_no].yaz(kayit_no);
				}
			}

		case 3:
		{
			cout << "\n\n***************************************************************" << endl;
			cout << "*                        Gule Gule                            *" << endl;
			cout << "* Gemi Takip Programini Kullandiginiz icin Tesekkur Ederiz... *" << endl;
			cout << "***************************************************************\n\n" << endl;
			break;
		}

		default:
		{
			cout << "\n ! ! ! Yanlis bir secim yaptiniz... ! ! !\n" << endl;
		}
		alt_secim = 'e';
			}
		}
	}while(secim=3);

}