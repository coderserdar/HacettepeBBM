#ifndef _LIST_H_
#define _LIST_H_

#include <fstream.h>
#include "arac.h"

class List
{
private:
	fstream dataFile;
	Arac dataFiles[1000];
	static int sira;
	int getFindSira(const char gKimlik[ ]);		
	bool find(const char gKimlik[]);
public:
	Arac getDataFiles(int);						
	bool add(const Arac &);						
	bool find(const char gKimlik[ ],Arac &);
	bool remove(const char gKimlik[ ]);			
	int size();	
	Arac* getFirst();							
	Arac* getNext(Arac &);
	static void setSira(){sira=0;};
	void setSira(int);
	bool saveList(char nameOfFile[]);
	bool loadList(char nameOfFile[]);
};
#endif