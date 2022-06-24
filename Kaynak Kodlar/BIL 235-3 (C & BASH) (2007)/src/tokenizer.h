#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef _ST
#define _ST

typedef struct _StringTokenizer {
  char *content;
  char *crt;
  char *token;
} StringTokenizer;

extern StringTokenizer* initTokenizer(char *s);
extern char* nextToken(StringTokenizer *st);
void tokenize(char* str ,char* path, FILE *index);


#endif

