/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  stdio.h - stdio header file                                      */
/*                                                                   */
/*********************************************************************/

#ifndef __STDIO_INCLUDED
#define __STDIO_INCLUDED

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int printk(const char *format, ...);
int sprintf(char *s, const char *format, ...);
int vsprintf(char *s, const char *format, char *arg);
int putchar(int c);
int puts(const char *s);

#ifdef __cplusplus
}
#endif

#endif
