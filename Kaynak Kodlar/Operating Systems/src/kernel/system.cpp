#include <system.h>
#include <stdarg.h>
#include <stdio.h>
#include <asm.h>

#define BUFFER_LEN 2048

static char buffer[BUFFER_LEN];

void System::PrintStackTrace()
{
	unsigned* basePointer = (unsigned*) GetEBP();

	printk("Stack Trace:\n");

	for(int i = 0; i < 10; i++)
	{
		printk(" [ebp = %p, Return Address = %p]\n", basePointer, basePointer[1]);

		basePointer = (unsigned*) *basePointer;
	
		if(basePointer == NULL || basePointer >= (void*) &StackLimit)
			break;
	}
}

void System::Panic(const char* message, ...)
{
	va_list ap;
	va_start(ap, message);

	vsprintf(buffer, message, ap);

	printk("\nKERNEL PANIC:\n");
	puts(buffer);

	va_end(ap);

	PrintStackTrace();
	Halt();
}

void System::Reboot()
{
	outportb (0x64, 0xfe);
}

void System::Halt()
{
	printk("system halted. press ctrl+alt+del to reboot.");
	while(true)
		;
}
