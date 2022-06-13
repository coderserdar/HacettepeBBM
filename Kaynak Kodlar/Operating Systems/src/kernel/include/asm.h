#ifndef __ASM_H
#define __ASM_H

/* SOURCE CODE TAKEN FROM osfaq2 */

static __inline__ void outportb(unsigned short port, unsigned char val)
{
	asm volatile("outb %0,%1"::"a"(val), "Nd" (port));
}

static __inline__ unsigned char inportb(unsigned short port)
{
   unsigned char ret;
   asm volatile("inb %1,%0":"=a"(ret):"Nd"(port));
   return ret;
}
/*
static __inline__ unsigned long farpeekl(word sel,void *off)
{
  unsigned long ret;
  asm("push %%fs;mov %1,%%fs;"
      "mov %%fs:(%2),%0;"
      "pop %%fs":"=r"(ret):"g"(sel),"r"(off));
  return ret;
}

static __inline__ void farpokeb(word sel, void *off, byte v)
{
  asm("push %%fs; mov %0,%%fs;"
      "movb %2,%%fs:(%1);"
      "pop %%fs": :"g"(sel),"r"(off),"r"(v));
}*/

#ifdef __cplusplus
extern "C" {
#endif

unsigned GetEBP();
void UpdateGdt(unsigned int base, unsigned limit);
extern int StackLimit;
void LoadIdt();
void CPUExceptionHandler(unsigned char error_code, unsigned char interrupt_code);
void DefaultInterruptHandler(unsigned char interrupt_code);
void KeyboardHandler();
void TimerHandler();
void MouseHandler();
void RTCHandler();
int Sleep(int duration);
int GetTime();
void farCall(int offset);

void isr0();
void isr1();
void isr2();
void isr3();
void isr4();
void isr5();
void isr6();
void isr7();
void isr8();
void isr9();
void isr10();
void isr11();
void isr12();
void isr13();
void isr14();
void isr16();
void isr17();
void isr18();
void isr96();

void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();

#ifdef __cplusplus
}
#endif

#endif
