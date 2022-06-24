#include "tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

StringTokenizer* initTokenizer(char *s) {
  StringTokenizer *sTokenizer;

  sTokenizer = (StringTokenizer*) malloc(sizeof(StringTokenizer));
  sTokenizer->content = s;
  sTokenizer->crt = s;
  sTokenizer->token = (char*) malloc(strlen(s)*sizeof(char));
  return sTokenizer;
}

char* nextToken(StringTokenizer *st) {
  int i = 0;

  while ((st->crt)[i] != '\0' && (st->crt)[i] != ' ') {
    (st->token)[i] = (st->crt)[i];
    i++;
  }  
  (st->token)[i] = '\0';
  while ((st->crt)[i] != '\0' && (st->crt)[i] == ' ') 
    i++;
  st->crt = st->crt + i;
  return st->token;
}

int main(void){
	char str[]="Executable_System Design.UML.pdf .";
	char str2[]="Data-Structures.doc ";
	char path[] ="tmp/e-books/";
	FILE *indexed;
	indexed = fopen("indexedFiles.txt", "a");
	
	tokenize(str,path, indexed);
	tokenize(str2,path, indexed);
	
	
	fclose(indexed);
	return 0;
}

void tokenize(char* str ,char* path, FILE *indexed){
	int i ;
	fprintf(indexed,"%s%s\n", path, str);
	for(i = 0; i < (int)strlen(str);i++){
		if( str[i]!= 32 && str[i]!= ')' && str[i]!= '[' && str[i]!= '!'
			&& str[i]!= '+' && str[i]!= ']' && str[i]!= '#' && str[i]!= ','
			&& str[i]!= '^' && str[i]!= '$' && str[i]!= '-' && str[i]!= '_' 
			&& str[i]!= '%' && str[i]!= '.' && str[i]!= '`' && str[i]!= '&'
			&& str[i]!= ';' && str[i]!= '{' && str[i]!= '`' && str[i]!= '=' 
			&& str[i]!= '}' && str[i]!= '(' && str[i]!= '@' && str[i]!= '~' ){
			
			fprintf(indexed,"%c",str[i]);
		}
		else{
			fprintf(indexed," ");
		}
		
	}
	fprintf(indexed,"\n");
	
	
}
