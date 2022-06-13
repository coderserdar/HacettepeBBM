#include <fstream.h>
#include <iostream>

#include "arac.h"
#include "list.h"

using namespace std;

char menu()
{
	char secim;
	using std::cout;
	using std::cin;

	system("cls");
	cout << "\n\n****************************************" << endl;
	cout << "*  Arac Takip Programina Hosgeldiniz   *" << endl;
	cout << "****************************************" << endl;
	cout << "*  1. Kayit Girisi                     *" << endl;
	cout << "*  2. Kayit Sil                        *" << endl;
	cout << "*  3. Kayit Bul                        *" << endl;
	cout << "*  4. Kayit Sayisi                     *" << endl;
	cout << "*  5. Kayit Listeleme                  *" << endl;
	cout << "*  6. Dosyadan Yukle                   *" << endl;
	cout << "*  7. Dosyaya Kaydet                   *" << endl;
	cout << "****************************************" << endl;
	cout << "*  8. Cikis                            *" << endl;
	cout << "****************************************\n" << endl;
	cout << " Secminiz: ";
	cin >> secim;
	return secim;
}

void kayitGiris(List &list)
{
	using std::cout;
	using std::cin;

	char altSecim;
	static int i=1;
	Arac gArac;
	int gRota;
	float gHiz;
	char gKimlik[10];
	char gTip[15];
	bool kontrol;

	for (;altSecim != 'h' && altSecim != 'H' && i<=1000;i++)
	{
		system("cls");
		cout << "\n\n****************" << endl;
		cout << "* Kayit No: "<<i<<"  *" << endl;
		cout << "****************\n" << endl;
		do{
			do{
				cout << " Aracin rotasini giriniz ( 0-359 )                                    : ";
				cin >> 	gRota;
				if(gArac.setRota(gRota)==false)
				{
					cout << " ! ! ! Yanlis bir giris yaptiniz            ! ! !" << endl;
					cout << " ! ! ! Rotanin degerleri 0-360 arasi olmali ! ! !"<< endl;
				}
			}while(gArac.setRota(gRota)==false);
			
			do{
				cout << " Aracin hizini giriniz  ( 0-150 )                                     : ";
				cin >> gHiz;
				if(gArac.setHiz(gHiz)==false)
				{
					cout << " ! ! ! Yanlis bir giris yaptiniz            ! ! !"<< endl;
					cout << " ! ! ! Surat degeri 0-150 knot arasi olmali ! ! !"<<endl;
				}
			}while(gArac.setHiz(gHiz)==false);

			do{
				cout << " Aracin kimlik bilgisini giriniz (En fazla 10 harf ve rakam olabilir) : ";
				cin >> gKimlik;
				if(gArac.setKimlik(gKimlik)==false)
				{ 
					cout << " ! ! ! Yanlis bir giris yaptiniz                              ! ! !"<< endl;
					cout << " ! ! ! Kimlik bilgisi en fazla 10 tane harf ve rakam olabilir ! ! !"<<endl;
				}
			}while(gArac.setKimlik(gKimlik)==false);
			
			do{
				cout << " Aracin tipini giriniz (En fazla 15 tane harf olabilir)               : ";
				cin >> gTip;
				if(gArac.setTip(gTip)==false)
				{
					cout << " ! ! ! Yanlis bir giris yaptiniz                  ! ! !"<< endl;
					cout << " ! ! ! Tip bilgisi en fazla 15 tane harf olabilir ! ! !"<<endl;
				}
			}while(gArac.setTip(gTip)==false);
			
			kontrol=list.add(gArac);
			if(kontrol==false)
			{
				cout << " ! ! ! Kaydiniz listeye eklenirken bir sorunla karsilasildi ! ! !"<< endl;
				cout << " ! ! ! Lutfen tekrar giriniz                                ! ! !"<< endl;
			}
		}while(kontrol==false);
		cout << "\n\n Baska bir kayit girmek istyormusunuz? (E\\H) ";
		cin >> altSecim;
	}
	if(altSecim=='h' || altSecim=='H')
		system("cls");
}

void kayitSil(List &list)
{
	using std::cout;
	using std::cin;

	char gKimlik[10];
	system("cls");
	cout << "**********************************" << endl;
	cout << "* Silinmesini istediginiz aracin  " << endl;
	cout << "* Kimlik Bilgisi: ";
	cin >> gKimlik;
	cout << "**********************************\n\n" << endl;
	if(list.remove(gKimlik)==false)
		cout << " ! ! ! Kaydiniz Silinemedi ! ! ! "<< endl;
	else
		cout << " Kaydiniz Basarili Bir Sekilde Silindi " << endl;
	system("pause");
}

void kayitBul(List &list)
{
	using std::cout;
	using std::cin;

	char gKimlik[10];
	Arac gArac;
	system("cls");
	cout << "\n\n*******************************************************" << endl;
	cout << "* Aramak istediginiz Aracin Kimlik Bilgisi: " ;
	cin >> gKimlik;
	cout << "*******************************************************\n\n" << endl;
	if(list.find(gKimlik,gArac)==true)
	{
		cout << " Bulunan Aracin " << endl;
		cout << "----------------" << endl;
		cout <<	" Kimlik Bilgisi " << gArac.getKimlik() << endl;
		cout << " Tip Bilgisi    " << gArac.getTip() << endl;
		cout << " Rota Bilgisi   " << gArac.getRota() << endl;
		cout << " Hiz Bilgisi    " << gArac.getHiz() << endl;
		system("pause");
	}
	else
	{			
		cout << " ! ! ! Aradiginiz Kayit Bulunamadi ! ! !" << endl;
		system("pause");
	}
}

void kayitSayisi(List &list)
{
	using std::cout;
	cout << " Listede Kayitli Arac Sayisi " << list.size() << " dir " << endl;
	system("pause");
}

void kayitListeleme(List &list)
{
	system("cls");
	using std::cout;
	using std::cin;
	int gSize=list.size();
	if(gSize==0)
		cout << "\n\n\n ! ! ! Listede Kayitli Bir Arac Yoktur ! ! !\n" << endl;
	else if(gSize>0)
	{
		for(int j=0;j<=gSize-1;j++)
		{
			cout << "\n\n****************************************" << endl;
			cout << "**  "<<j+1<<". Arac icin Girdiginiz Bilgiler  **" << endl; 
			cout << "****************************************" << endl;
			list.getDataFiles(j).yaz();
		}
	}
	else
		cout << "\n\n\n ! ! ! Kayitlar Listelenirken Bir Hata Olustu ! ! !\n" << endl;
	system("pause");
}

void exit()
{
	using std::cout;
	system("cls");
	cout << "\n\n***************************************************************" << endl;
	cout << "*                        Gule Gule                            *" << endl;
	cout << "* Arac Takip Programini Kullandiginiz icin Tesekkur Ederiz... *" << endl;
	cout << "***************************************************************\n" << endl;
	system("pause");
}

void fault()
{
	using std::cout;
	cout << "\n ! ! ! Yanlis bir secim yaptiniz... ! ! !\n" << endl;
	system("pause");
}

void saveList(List &list)
{
	using std::cout;
	using std::cin;
	char nameOfFile[80];

	cout << " Lutfen kaydetmek istediginiz \n dosyanin ismini giriniz: ";
	cin >> nameOfFile;
	if(list.saveList(nameOfFile)==false)
		cout << " Dosyaya kaydederken bir hatayla karsilasildi" << endl;
	else
		cout << " Kayit basarili sekilde " << nameOfFile << " dosyasina kaydedildi " << endl;
	system("pause");
}

void loadList(List &list)
{
	using std::cout;
	using std::cin;
	char nameOfFile[80];

	cout << " Lutfen yuklemek istediginiz \n dosyanin ismini giriniz: ";
	cin >> nameOfFile;
	if(list.loadList(nameOfFile)==false)
		cout << " Dosya acilirken\\yuklenirken bir hata ile karslasildi " << endl;
	else
		cout << " Dosya basarili bir sekilde yuklendi " << endl;
	system("pause");
}

int main()
{
	List::setSira();

	char altSecim,secim;
	List list;
	
	do{
		secim=menu();
		switch (secim)
		{
		case '1':
			kayitGiris(list);
			break;
		case '2':
			kayitSil(list);
			break;
		case '3':
			kayitBul(list);
			break;
		case '4':
			kayitSayisi(list);
			break;
		case '5':
			kayitListeleme(list);
			break;
		case '6':
			loadList(list);
			break;
		case '7':
			saveList(list);
			break;
		case '8':
			exit();
			break;
		default:
			fault();
			break;	
		}

		altSecim = 'e';
	}while(secim != '8');
	return 0;
}