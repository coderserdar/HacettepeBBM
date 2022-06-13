#ifndef __SYSTEM_H
#define __SYSTEM_H

class System
{
public:
	static void PrintStackTrace();

	static void Panic(const char *msg, ...);

	static void Halt();
	static void Reboot();
};

#endif
