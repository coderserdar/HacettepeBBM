/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  ctype.h - ctype header file.                                     */
/*                                                                   */
/*********************************************************************/

#ifndef __CTYPE_INCLUDED
#define __CTYPE_INCLUDED

extern unsigned short *__isbuf;
extern short *__tolow;
extern short *__toup;

#define isalnum(c) (__isbuf[(c)] & 0x0001U)
#define isalpha(c) (__isbuf[(c)] & 0x0002U)
#define iscntrl(c) (__isbuf[(c)] & 0x0004U)
#define isdigit(c) (__isbuf[(c)] & 0x0008U)
#define isgraph(c) (__isbuf[(c)] & 0x0010U)
#define islower(c) (__isbuf[(c)] & 0x0020U)
#define isprint(c) (__isbuf[(c)] & 0x0040U)
#define ispunct(c) (__isbuf[(c)] & 0x0080U)
#define isspace(c) (__isbuf[(c)] & 0x0100U)
#define isupper(c) (__isbuf[(c)] & 0x0200U)
#define isxdigit(c) (__isbuf[(c)] & 0x0400U)
#define tolower(c) (__tolow[(c)])
#define toupper(c) (__toup[(c)])

#endif
