#ifndef _ARAC_H_
#define _ARAC_H_

class Arac
{
private:
	int rota;
	float hiz;
	char *kimlik;
	char *tip;
	int checkLenght(char *dizi);
	bool checkTip(char *tip);
	bool checkKimlik(char *kimlik);
public:
	void yaz()const;
	bool setRota(int gRota);
	bool setHiz(float gHiz);
	bool setKimlik(char *gKimlik);
	bool setTip(char *gTip);
	float getHiz()const;
	int getRota()const;
	char* getKimlik()const;
	char* getTip()const;
	Arac(const Arac &);	
	Arac();					
};

#endif