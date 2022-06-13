#include <multiboot.h>
#include <video.h>
#include <memory.h>
#include <assert.h>
#include <system.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <asm.h>

//timer precision 10 msec.
//that means 100 ticks per second
#define TIMER_FREQUENCY 100

//screen size:
#define SCREEN_SIZE_X 80
#define SCREEN_SIZE_Y 25

//number of units the mouse should move to
//move the mouse cursor at the screen one unit 
#define MOUSE_SENSITIVITY 4

//mouse coordinate limits:
#define MOUSE_LIMIT_X ((MOUSE_SENSITIVITY * SCREEN_SIZE_X) - 1)
#define MOUSE_LIMIT_Y ((MOUSE_SENSITIVITY * SCREEN_SIZE_Y) - 1)

/**************************************************************
 * idt_entry, idt_ptr, gdt_entry structs, idt_set_gate,
 * gdt_set_gate functions and the keyboard character map
 * are taken from Bran's Kernel Development Tutorial.
 * SetupIDT function is based on parts of Bran's Kernel
 * Development Tutorial.
 **************************************************************/
 
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

struct keyboard_info
{
	unsigned char shift;
	unsigned char ctrl;
	unsigned char alt;
};

struct mouse_info
{
	unsigned char status;
	unsigned char clicks;
	int xpos;
	int ypos;
};

struct system_time
{
	unsigned char hours;
	unsigned char minutes;
	unsigned char seconds;
	unsigned int miliseconds;
};

struct application_header {
    unsigned long signature;
    unsigned long data_size;
    unsigned long entry_point;
    unsigned long checksum;
} __attribute__((packed));



/**************************************************************
 * GLOBAL VARIABLES
 **************************************************************/
struct idt_entry idt[256];
struct idt_ptr IDTR;

struct gdt_entry gdt[5];

struct mouse_info mouse;
struct keyboard_info keyboard = {0};
struct system_time time;

volatile unsigned int timerTicks;

extern "C" int toupper(char c);


//keyboard character map
unsigned char kbmap[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
  '9', '0', '-', '=', 8, 9, 'q', 'w', 'e', 'r',
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
 '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n',
  'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0,	0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+',
};


void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    /* The interrupt routine's base address */
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use
    *  is set here, along with any access flags */
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void SetupIDT()
{
    IDTR.limit = (sizeof (struct idt_entry) * 256) - 1;
    IDTR.base = (unsigned)&idt;

    memset(&idt, 0, sizeof(struct idt_entry) * 256);
    
    //install interrupt service routines:
    idt_set_gate(0, (unsigned)isr0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned)isr1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned)isr2, 0x08, 0x8E);
    idt_set_gate(3, (unsigned)isr3, 0x08, 0x8E);
    idt_set_gate(4, (unsigned)isr4, 0x08, 0x8E);
    idt_set_gate(5, (unsigned)isr5, 0x08, 0x8E);
    idt_set_gate(6, (unsigned)isr6, 0x08, 0x8E);
    idt_set_gate(7, (unsigned)isr7, 0x08, 0x8E);
    idt_set_gate(8, (unsigned)isr8, 0x08, 0x8E);
    idt_set_gate(9, (unsigned)isr9, 0x08, 0x8E);
    idt_set_gate(10, (unsigned)isr10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned)isr11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned)isr12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned)isr13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned)isr14, 0x08, 0x8E);
    idt_set_gate(16, (unsigned)isr16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned)isr17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned)isr18, 0x08, 0x8E);
    idt_set_gate(96, (unsigned)isr96, 0x08, 0x8E);

	//remap interrupt requests:
	outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
    
    //install interrupt requests:
    idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
    idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
    idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
    idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E);
    idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E);
    idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
    idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E);
    idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E);
    idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E);
    idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E);
    idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E);
    idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
    idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E);
    idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E);
    idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);
    idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);

	//Load Interrupt Descriptor Table:
    LoadIdt();
}

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

//a little delay is required to
//suppose the PS/2 chip data is safe.
//this is done by checking input buffer status
//and output buffer status bits of the keyboard
//controller status register.

void MouseWait(char c)
{
	int i;
	
	if(c == 'R') //wait until the mouse is ready to read 
	{
		//check the input buffer status bit (bit 0)
		for(i = 0; (inportb(0x64) & 1) != 1 && i < 100000; i++);
	}
	else if(c == 'W') //wait until the mouse is ready to write
	{
		//check the output buffer status bit (bit 1)
		for(i = 0; (inportb(0x64) & 2) != 0 && i < 100000; i++);
	}
}

unsigned char MouseRead()
{
	//wait until the mouse is ready:
	MouseWait('R');
	//read data:
	return inportb(0x60);
}

void SetupMouse()
{
	//enable the device
	MouseWait('W');
	outportb(0x64, 0xA8);

	//enable mouse interrupts:
	
	//read the keyboard controller command byte
	MouseWait('R');
	outportb(0x64, 0x20);
	//set bit 1 (mouse interrupt enable bit)
	unsigned char kcc = MouseRead() | 2;
	
	//write the keyboard controller command byte
	MouseWait('W');
	outportb(0x64, 0x60);
	MouseWait('W');
	outportb(0x60, kcc);

	//set default settings for the mouse:
	//sampling rate = 100, resolution = 4 counts/mm,
	//scaling = 1:1, data reporting = disabled,
	//mode = stream mode.
	MouseWait('W');
	outportb(0x64, 0xD4);
	MouseWait('W');
	outportb(0x60, 0xF6);
	
	//acknowledge
	MouseRead();

	//enable the mouse
	MouseWait('W');
	outportb(0x64, 0xD4);
	MouseWait('W');
	outportb(0x60, 0xF4);
	
	//acknowledge
	MouseRead();
	
	//initialize mouse info:
	mouse.status = 0;
	mouse.clicks = 0;
	mouse.xpos = 0;
	mouse.ypos = 0;
}

void SetupTimer(int freq)
{
	unsigned int divisor = 1193180L / freq;
    outportb(0x43, 0x36);
    outportb(0x40, divisor & 0xFF);
    outportb(0x40, divisor >> 8);
    
    //set timer tick count to 0:
    timerTicks = 0;
}

void SetupRTC()
{
	unsigned char status;
	
	//set update-ended interrupts (will be triggered every second),
	//and binary data mode
	outportb(0x70, 0x0B);
	status = inportb(0x71);
	outportb(0x70, 0x0B);
	outportb(0x71, status | 0x14);
}

//close to prevent damage to the CMOS chip
void CloseRTC()
{
	unsigned char status;
	
	//disable interrupts
	outportb(0x70, 0x0B);
	status = inportb(0x71);
	outportb(0x70, 0x0B);
	outportb(0x71, status & ~(0x14));
}

void Wait(int duration) //wait duration (miliseconds)
{
	//interrupts must be enabled to get ticks
	asm volatile("sti");
	
	unsigned int targetTicks = timerTicks + ((duration * TIMER_FREQUENCY) / 1000);
	while(timerTicks < targetTicks);
}

void Beep(int freq, int duration) //frequency (hz) and wait duration (miliseconds)
{
	unsigned int divisor = 1193180L / freq;
	
	//set frequency for PIT channel 2 (speaker)
	outportb( 0x43, 0xB6 );
	outportb( 0x42, divisor & 0xFF ) ;
	outportb( 0x42, divisor >> 8 ) ;
	
	//enable the PC speaker
	outportb(0x61, inportb(0x61) | 0x03);
	
	//it started beeping; wait for given duration
	Wait(duration);	
	
	//stop beeping, close the PC speaker
	outportb(0x61, inportb(0x61) & ~(0x03));
}

void CPUExceptionHandler(unsigned char exception_code, unsigned char error_code)
{
    if (exception_code < 32)
    {
        printk("\nCPU exception occured!\n");
		printk("Exception code:%d\n", exception_code);
		printk("Error code:%d\n", error_code);
		System::PrintStackTrace();
		printk("System halted.\n");
        System::Halt();
    }
    else printk("Unknown exception raised! Code: %d\n", exception_code);
}

void DefaultInterruptHandler(unsigned char interrupt_code)
{
    //Don't do anything about unknown interrupts for now
    printk("Unknown interrupt raised! Code: %d\n", interrupt_code);
    
    //send EndOfInterrupt to PICs:
    if (interrupt_code >= 40) outportb(0xA0, 0x20);
    outportb(0x20, 0x20);
}

void KeyboardHandler()
{
    unsigned char input = inportb(0x60);
    
    if (input & 0x80)
    {
        switch(input)
   		{
   			case 157:
   				keyboard.ctrl = 0;
   				break;
   			case 184:
   				keyboard.alt = 0;
   				break;
   			case 170:
   			case 182:
   				keyboard.shift = 0;
   				break;
   		}
    }
    else
    {
   		switch(input)
   		{
   			case 29:
   				keyboard.ctrl = 1;
   				break;
   			case 56:
   				keyboard.alt = 1;
   				break;
   			case 42:
   			case 54:
   				keyboard.shift = 1;
   				break;
   			default:
   			
   				if(keyboard.ctrl && keyboard.alt && input == 83)
   				{
					CloseRTC();
   					System::Reboot();
   				}
   				else if(kbmap[input] == 27) //escape
   				{
   					Beep(400, 200);
   				}
   				else if(kbmap[input] != 0) //other characters
   				{
   					if(keyboard.shift) putchar(toupper(kbmap[input]));
   					else putchar(kbmap[input]);
   				}
   				break;
   		}
   	}
   	
   	//send EndOfInterrupt to the master PIC:
    outportb(0x20, 0x20);
}

void TimerHandler()
{
	timerTicks++;
	time.miliseconds += 10;
	
	
	Video::SetCursor(0, 0);
	printk("%02d:%02d:%02d.%02d", time.hours, time.minutes, time.seconds, (time.miliseconds / 10) % 100);
	
    //send EndOfInterrupt to the master PIC:
    outportb(0x20, 0x20);
}

void RTCHandler()
{
	//clear interrupts:
	asm volatile("cli");
	
	//read system time:
	outportb(0x70, 0x00);
	time.seconds = inportb(0x71);
	outportb(0x70, 0x02);
	time.minutes = inportb(0x71);
	outportb(0x70, 0x04);
	time.hours = inportb(0x71);
	
	time.miliseconds = 0;
	
	//clear pending interrupt by reading status register 0x0C
	outportb(0x70, 0x0C);
	inportb(0x71);
	
	//send EndOfInterrupt to the slave and master PICs:
	outportb(0xA0, 0x20);
    outportb(0x20, 0x20);
}

//mouse data is sent as 3 byte packages: click info, x position and y position.
//this info is sent one byte at one interrupt, in 3 interrupts total.
//so the status variable holds the interrupt status to determine which
//information will be sent at current interrupt.
void MouseHandler()
{
	if(mouse.status == 0) //get clicks
	{
		mouse.clicks = inportb(0x60);
		mouse.status = 1;
	}
	else if(mouse.status == 1) //get x position
	{
		char xmove = inportb(0x60);
		mouse.xpos += xmove;
		
		if(mouse.xpos < 0) mouse.xpos = 0;
		else if(mouse.xpos > MOUSE_LIMIT_X) mouse.xpos = MOUSE_LIMIT_X;
		
		mouse.status = 2;
	}
	else //get y position
	{
		char ymove = inportb(0x60);
		mouse.ypos -= ymove; //y axis is inverted
		
		if(mouse.ypos < 0) mouse.ypos = 0;
		else if(mouse.ypos > MOUSE_LIMIT_Y) mouse.ypos = MOUSE_LIMIT_Y;
		
		mouse.status = 0;
	}
    
    //send EndOfInterrupt to the slave and master PICs:
    outportb(0xA0, 0x20);
    outportb(0x20, 0x20);
}

int GetTime()
{
	unsigned char years, months, days;
	
	outportb(0x70, 0x07);
	years = inportb(0x71);
	outportb(0x70, 0x08);
	months = inportb(0x71);
	outportb(0x70, 0x09);
	days = inportb(0x71);
	
	
	int leap_year = (years / 4) + 1;
	int xtime = ((years * 365) + leap_year + (months * 30) + days) * 24 * 60 * 60 * 1000;
	xtime += (((time.hours * 60 + time.minutes) * 60) + time.seconds) * 1000 + time.miliseconds;
	
	return xtime;
}

int Sleep(int duration)
{
	Wait(duration);
	return 0;
}

void Game()
{
	int missilex = 0, missiley = 0, remaining = 6, mxpos, i;
	
	//starting position, speed, drawing state
	int enemies[6][3] = {{2,1,0}, {48,-1,1}, {25,2,0}, {56,-3,0}, {75,-2,1}, {15,3,1}};
	
	while(remaining)
	{
		
		Video::Clear();
		Video::SetCursor(49, 0);
		printk("Hit ctrl to shoot. Remaining: %d", remaining);
		
		mxpos = mouse.xpos / MOUSE_SENSITIVITY;
		if(mxpos < 2) mxpos = 2;
		if(mxpos > SCREEN_SIZE_X - 3) mxpos = SCREEN_SIZE_X - 3;
		Video::SetCursor(mxpos - 1, SCREEN_SIZE_Y - 2);
		
		putchar('/');
		if(missiley) putchar(' ');
		else putchar('*');
		putchar('\\');
		
		Video::SetCursor(mxpos - 2, SCREEN_SIZE_Y - 1);
		
		putchar('[');
		putchar('_');
		putchar('_');
		putchar('_');
		putchar(']');
		
		if(missiley == 0)
		{
			if(keyboard.ctrl)
			{
				Beep(750, 50);
				Beep(1500, 50);
				missiley = 22;
				missilex = mxpos;
			}
		}
		else if(missiley > 0)
		{
			missiley--;
			//draw missile
			if(missiley)
			{
				Video::SetCursor(missilex, missiley);
				putchar('*');
			}
			
			if(keyboard.ctrl)
			{
				Beep(900, 50);
			}
		}
		
		//draw enemies:
		for(i = 0; i < 6; i++)
		{
			if(enemies[i][1] != 0)
			{
				enemies[i][0] += enemies[i][1];
				
				if(enemies[i][0] < 0)
				{
					enemies[i][0] = 0;
					enemies[i][1] = -enemies[i][1];
				}
				else if(enemies[i][0] > SCREEN_SIZE_X - 3)
				{
					enemies[i][0] = SCREEN_SIZE_X - 3;
					enemies[i][1] = -enemies[i][1];
				}
				
				//collision detection
				if((missilex >= enemies[i][0] && missilex <= enemies[i][0] + 2 && (missiley == (i*3) + 2 || missiley == (i*3) + 3)))
				{
					enemies[i][1] = 0; //die!
					remaining--;
					Beep(2700, 75);
					Beep(400, 150);
				}
				
				Video::SetCursor(enemies[i][0], (i*3) + 2);
				putchar('0');
				putchar('v');
				putchar('0');
				Video::SetCursor(enemies[i][0], (i*3) + 3);
				
				if(enemies[i][2])
				{
					putchar('\\');
					putchar('"');
					putchar('/');
					enemies[i][2] = 0;
				}
				else
				{
					putchar('|');
					putchar('"');
					putchar('|');
					enemies[i][2] = 1;
				}
			}
			else
			{
				Video::SetCursor(enemies[i][0], (i*3) + 2);
				putchar('*');
				putchar('_');
				putchar('*');
				Video::SetCursor(enemies[i][0], (i*3) + 3);
				putchar('\\');
				putchar('#');
				putchar('/');
			}
			
		}
		
		Video::SetCursor(mxpos, SCREEN_SIZE_Y - 3);
		
		Wait(100);
	}
	
	System::Halt();
}

int main(multiboot_info *boot_info)
{
	Video::Clear();
	Memory::Initialize(boot_info);
	SetupMouse();
	SetupIDT();
	SetupTimer(TIMER_FREQUENCY);
	SetupRTC();
	
	//enable interrupts:
	asm volatile("sti");
	
	//start the game
	Game();
	
	
	/* Module loading does not work
	
	//allocate memory for the module
	
	Module* module = &Memory::Modules[0];
	
	struct application_header *header = (struct application_header*) module->Start;
	
	printk("module size: %p  end: %p\n", module->Size(), module->End);
	printk("module addr: %p  start: %p\n", module, module->Start);
	
	Module* new_module = (Module*)kalloc(module->Size() + 0x4000 + header->data_size);	
	printk("copying to: %p  start: %p\n", new_module + 0x4000, new_module + 0x4000);
	memcpy(new_module + 0x4000, module->Start, module->Size());
	
	//set up new gdt:
	unsigned short gdtlimit = (sizeof(struct gdt_entry) * 5) - 1;
    unsigned int gdtbase = (unsigned)&gdt;

    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_set_gate(3, (unsigned)new_module + header->entry_point, module->Size()-1, 0x9A, 0xCF);
    gdt_set_gate(4, (unsigned)new_module + 0x4000 + module->Size(), header->data_size-1, 0x92, 0xCF);

    UpdateGdt(gdtbase, gdtlimit);
	
	*/
	
	
	while(1);

	return 0;
}

