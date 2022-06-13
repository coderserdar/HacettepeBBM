#include <system.h>
#include <assert.h>

extern "C" void __cxa_pure_call()
{
	System::Panic("Pure virtual function called.");
}


/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  assert.c - implementation of stuff in assert.h                   */
/*                                                                   */
/*********************************************************************/

int __assert(char *x, char *y, int z)
{
	System::Panic("assertion failed for statement %s in file %s on line %d\n", x, y, z);

	return 0;
}
