/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  string.c - implementation of routines in string.h                */
/*                                                                   */
/*********************************************************************/

#include <string.h>

#ifdef memmove
#undef memmove
#endif

void *memmove(void *s1, const void *s2, size_t n)
{
	char *c1;
	const char *c2;

	if(s1 < s2)
		for(c1 = s1, c2 = s2; n; n--)
			*c1++ = *c2++;
	else
		for(c1 = (char *)s1 + n, c2 = (char *)s2 + n; (void *)c1 > s1; )
			*--c1 = *--c2;

	return s1;

/*  There was a bug with the usage of x, rewritten to fix the bug and to make 
    the code more elegant

    char *p = s1;
    const char *cs2 = s2;
    size_t x = 0;
    
    if (p <= cs2)
    {
        for (x=0; x < n; x++)
        {
            *p = *cs2;
            p++;
            cs2++;
        }
    }
    else
    {
        if (n != 0)
        {
            for (x=n-1; x > 0; x--)
            {
                *(p+x) = *(cs2+x);
            }
        }
        *(p+x) = *(cs2+x);
    }
    return (s1);
    */
}

#ifdef strcpy
#undef strcpy
#endif
char *strcpy(char *s1, const char *s2)
{
    char *p = s1;
    
    while ((*p++ = *s2++) != '\0') ;
    return (s1);
}

#ifdef strncpy
#undef strncpy
#endif
char *strncpy(char *s1, const char *s2, size_t n)
{
    char *p = s1;
    size_t x;
    
    for (x=0; x < n; x++)
    {
        *p = *s2;
        if (*s2 == '\0') break;
        p++;
        s2++;
    }
    for (; x < n; x++)
    {
        *p++ = '\0';
    }
    return (s1);
}

#ifdef strcat
#undef strcat
#endif
char *strcat(char *s1, const char *s2)
{
    char *p = s1;
    
    while (*p != '\0') p++;
    while ((*p = *s2) != '\0')
    {
        p++;
        s2++;
    }
    return (s1);
}

#ifdef strncat
#undef strncat
#endif
char *strncat(char *s1, const char *s2, size_t n)
{
    char *p = s1;
    size_t x = 0;
    
    while (*p != '\0') p++;
    while ((*s2 != '\0') && (x < n))
    {
        *p = *s2;
        p++;
        s2++;
        x++;
    }
    *p = '\0';
    return (s1);
}

#ifdef memcmp
#undef memcmp
#endif
int memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *p1;
    const unsigned char *p2;
    size_t x = 0;
    
    p1 = (const unsigned char *)s1;
    p2 = (const unsigned char *)s2;
    while (x < n)
    {
        if (p1[x] < p2[x]) return (-1);
        else if (p1[x] > p2[x]) return (1);
        x++;
    }
    return (0);
}
    
#ifdef strcmp
#undef strcmp
#endif
int strcmp(const char *s1, const char *s2)
{
    const unsigned char *p1;
    const unsigned char *p2;
    
    p1 = (const unsigned char *)s1;
    p2 = (const unsigned char *)s2;
    while (*p1 != '\0')
    {
        if (*p1 < *p2) return (-1);
        else if (*p1 > *p2) return (1);
        p1++;
        p2++;
    }
    if (*p2 == '\0') return (0);
#if defined(__MVS__) || defined(__CMS__)
    /* this is a hack that should be removed. It is to get
       around a bug in the gcc 3.2.3 MVS stage 101 optimizer. */
    else if (*p2 != '\0') return (-1);
#else
    else return (-1);
#endif
}

#ifdef strcoll
#undef strcoll
#endif
int strcoll(const char *s1, const char *s2)
{
    return (strcmp(s1, s2));
}

#ifdef strncmp
#undef strncmp
#endif
int strncmp(const char *s1, const char *s2, size_t n)
{
    const unsigned char *p1;
    const unsigned char *p2;
    size_t x = 0;
    
    p1 = (const unsigned char *)s1;
    p2 = (const unsigned char *)s2;
    while (x < n)
    {
        if (p1[x] < p2[x]) return (-1);
        else if (p1[x] > p2[x]) return (1);
        else if (p1[x] == '\0') return (0);
        x++;
    }
    return (0);
}

#ifdef strxfrm
#undef strxfrm
#endif
size_t strxfrm(char *s1, const char *s2, size_t n)
{
    size_t oldlen;
    
    oldlen = strlen(s2);
    if (oldlen < n)
    {
        memcpy(s1, s2, oldlen);
        s1[oldlen] = '\0';
    }
    return (oldlen);
}

#ifdef memchr
#undef memchr
#endif
void *memchr(const void *s, int c, size_t n)
{
    const unsigned char *p;
    size_t x = 0;
    
    p = (const unsigned char *)s;
    while (x < n)
    {
        if (*p == (unsigned char)c) return ((void *)p);
        p++;
        x++;
    }
    return (NULL);
}

#ifdef strchr
#undef strchr
#endif
char *strchr(const char *s, int c)
{
    while (*s != '\0')
    {
        if (*s == (char)c) return ((char *)s);
        s++;
    }
    if (c == '\0') return ((char *)s);
    return (NULL);
}

#ifdef strcspn
#undef strcspn
#endif
size_t strcspn(const char *s1, const char *s2)
{
    const char *p1;
    const char *p2;
    
    p1 = s1;
    while (*p1 != '\0')
    {
        p2 = s2;
        while (*p2 != '\0')
        {
            if (*p1 == *p2) return ((size_t)(p1 - s1));
            p2++;
        }
        p1++;
    }
    return ((size_t)(p1 - s1));
}

#ifdef strpbrk
#undef strpbrk
#endif
char *strpbrk(const char *s1, const char *s2)
{
    const char *p1;
    const char *p2;
    
    p1 = s1;
    while (*p1 != '\0')
    {
        p2 = s2;
        while (*p2 != '\0')
        {
            if (*p1 == *p2) return ((char *)p1);
            p2++;
        }
        p1++;
    }
    return (NULL);
}

#ifdef strrchr
#undef strrchr
#endif
char *strrchr(const char *s, int c)
{
    const char *p;
    
    p = s + strlen(s);
    while (p >= s)
    {
        if (*p == (char)c) return ((char *)p);
        p--;
    }
    return (NULL);
}

#ifdef strspn
#undef strspn
#endif
size_t strspn(const char *s1, const char *s2)
{
    const char *p1;
    const char *p2;
    
    p1 = s1;
    while (*p1 != '\0')
    {
        p2 = s2;
        while (*p2 != '\0')
        {
            if (*p1 == *p2) break;
            p2++;
        }
        if (*p2 == '\0') return ((size_t)(p1 - s1));
        p1++;
    }
    return ((size_t)(p1 - s1));
}


/* strstr by Frank Adam */
/* modified by Paul Edwards */

#ifdef strstr
#undef strstr
#endif
char *strstr(const char *s1, const char *s2)
{
    const char *p = s1, *p1, *p2 = s2;

    while (*p)
    {
        if (*p == *s2)
        {
            p1 = p;
            p2 = s2;
            while ((*p2 != '\0') && (*p1++ == *p2++)) ;
            if (*p2 == '\0')
            {
                return (char *)p;
            }
        }
        p++;
    }
    return NULL;
}

#ifdef strtok
#undef strtok
#endif
char *strtok(char *s1, const char *s2)
{
    static char *old = NULL;
    char *p;
    size_t len;
    size_t remain;
    
    if (s1 != NULL) old = s1;
    if (old == NULL) return (NULL);
    p = old;
    len = strspn(p, s2);
    remain = strlen(p);
    if (remain <= len) { old = NULL; return (NULL); }
    p += len;
    len = strcspn(p, s2);
    remain = strlen(p);
    if (remain <= len) { old = NULL; return (p); }
    *(p + len) = '\0';
    old = p + len + 1;
    return (p);
}

#ifdef memset
#undef memset
#endif
void *memset(void *s, int c, size_t n)
{
    size_t x = 0;
    
    for (x = 0; x < n; x++)
    {
        *((char *)s + x) = (unsigned char)c;
    }
    return (s);
}

#ifdef strerror
#undef strerror
#endif
char *strerror(int errnum)
{
    if (errnum == 0) return ("No error has occurred\n");
    else return ("An error has occurred\n");
}
                
#ifdef strlen
#undef strlen
#endif
size_t strlen(const char *s)
{
    const char *p;
    
    p = s;
    while (*p != '\0') p++;
    return ((size_t)(p - s));
}

#ifndef USE_ASSEMBLER
#ifdef memcpy
#undef memcpy
#endif
#ifndef __32BIT__
void *memcpy(void *s1, const void *s2, size_t n)
{
    register const unsigned char *f = s2;
    register const unsigned char *fe;
    register unsigned char *t = s1;
    
    fe = f + n;
    while (f != fe)
    {
        *t++ = *f++;
    }
    return (s1);
}
#else
void *memcpy(void *s1, const void *s2, size_t n)
{
    register unsigned int *p = (unsigned int *)s1;
    register unsigned int *cs2 = (unsigned int *)s2;
    register unsigned int *endi;
    
    endi = (unsigned int *)((char *)p + (n & ~0x03));
    while (p != endi)
    {
        *p++ = *cs2++;
    }
    switch (n & 0x03)
    {
        case 0:
            break;
        case 1:
            *(char *)p = *(char *)cs2;
            break;
        case 2:
            *(char *)p = *(char *)cs2;
            p = (unsigned int *)((char *)p + 1);
            cs2 = (unsigned int *)((char *)cs2 + 1);
            *(char *)p = *(char *)cs2;
            break;
        case 3:
            *(char *)p = *(char *)cs2;
            p = (unsigned int *)((char *)p + 1);
            cs2 = (unsigned int *)((char *)cs2 + 1);
            *(char *)p = *(char *)cs2;
            p = (unsigned int *)((char *)p + 1);
            cs2 = (unsigned int *)((char *)cs2 + 1);
            *(char *)p = *(char *)cs2;
            break;
    }
    return (s1);
}
#endif /* 32BIT */
#endif /* USE_ASSEMBLER */
