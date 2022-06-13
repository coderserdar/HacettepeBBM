/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  stdlib.h - stdlib header file                                    */
/*                                                                   */
/*********************************************************************/

#ifndef __STDLIB_INCLUDED
#define __STDLIB_INCLUDED

#include <stddef.h>

#ifndef __cplusplus
#ifndef __WCHAR_T_DEFINED
#define __WCHAR_T_DEFINED
typedef char wchar_t;
#endif
#endif

typedef struct { int quot; int rem; } div_t;
typedef struct { long int quot; long int rem; } ldiv_t;

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define RAND_MAX 32767

#ifdef __cplusplus
extern "C" {
#endif

void *kalloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void kfree(void *ptr);

void srand(unsigned int seed);
int rand(void);

double atof(const char *nptr);
double strtod(const char *nptr, char **endptr);
int atoi(const char *nptr);
long int atol(const char *nptr);
long int strtol(const char *nptr, char **endptr, int base);
unsigned long int strtoul(const char *nptr, char **endptr, int base);

int abs(int j);
div_t div(int numer, int denom);
long int labs(long int j);
ldiv_t ldiv(long int numer, long int denom);

void qsort(void *, size_t, size_t, int (*)(const void *, const void *));
void *bsearch(const void *key, const void *base,
              size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif
