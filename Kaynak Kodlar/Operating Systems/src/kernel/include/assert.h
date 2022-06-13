/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  assert.h - assert header file.                                   */
/*                                                                   */
/*********************************************************************/

#ifndef __ASSERT_INCLUDED
#define __ASSERT_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

int __assert(char *x, char *y, int);

#ifdef __cplusplus
}
#endif

#ifdef NDEBUG
#define assert(ignore) { }
#else
#define assert(x) { if(!(x)) __assert(#x, __FILE__, __LINE__); }
#endif    

#endif
