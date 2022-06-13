/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  stdarg.h - stdarg header file.                                   */
/*                                                                   */
/*********************************************************************/

#ifndef __STDARG_INCLUDED
#define __STDARG_INCLUDED

typedef char * va_list;

#define va_start(ap, parmN) ap = (char *)&parmN + 4
#define va_arg(ap, type) *(type *)(ap += sizeof(type), ap - sizeof(type))
#define va_end(ap) ap = 0

#endif
