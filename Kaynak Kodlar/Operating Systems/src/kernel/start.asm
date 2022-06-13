
; ****************************************************************************
;
; BBM OS KERNEL
;
;   Startup Assembly Routines
;
; Copyright (C) Sukru TIKVES 2006
;
;   Based on parts by GRUB, FritzOS and others, see LICENCE for information
;
; ****************************************************************************

; ****************************************************************************
;  GLOBAL SYMBOLS
; ****************************************************************************

GLOBAL KernelStart			; Start address for use by the linker

GLOBAL UpdateGdt			; To change GDTR from C/C++ code

GLOBAL GetEBP				; Returns EBP register
GLOBAL StackLimit			; Upper limit of stack
					; NOTE: stack grows in reverse
					;   direction, this is the initial
					;   value.
					
GLOBAL LoadIdt		; Loads the Interrupt Descriptor Table from C++

GLOBAL isr0
GLOBAL isr1
GLOBAL isr2
GLOBAL isr3
GLOBAL isr4
GLOBAL isr5
GLOBAL isr6
GLOBAL isr7
GLOBAL isr8
GLOBAL isr9
GLOBAL isr10
GLOBAL isr11
GLOBAL isr12
GLOBAL isr13
GLOBAL isr14
GLOBAL isr16
GLOBAL isr17
GLOBAL isr18
GLOBAL isr96

GLOBAL irq0
GLOBAL irq1
GLOBAL irq2
GLOBAL irq3
GLOBAL irq4
GLOBAL irq5
GLOBAL irq6
GLOBAL irq7
GLOBAL irq8
GLOBAL irq9
GLOBAL irq10
GLOBAL irq11
GLOBAL irq12
GLOBAL irq13
GLOBAL irq14
GLOBAL irq15


; ****************************************************************************
;  EXTERNAL SYMBOLS
; ****************************************************************************

EXTERN main							; Startup address of C/C++ main code
EXTERN IDTR							; pointer to the Interrupt Descriptor Table
EXTERN CPUExceptionHandler
EXTERN DefaultInterruptHandler
EXTERN KeyboardHandler
EXTERN TimerHandler
EXTERN RTCHandler
EXTERN MouseHandler
EXTERN GetTime
EXTERN Sleep

; ****************************************************************************
;  MULTI BOOT HEADER INFORMATION
; ****************************************************************************

MODULE_ALIGN equ  01h			; Align modules on page boundaries
MEMINFO      equ  02h			; Provide memory map
FLAGS        equ  MODULE_ALIGN | MEMINFO; Our flag settings
MAGIC        equ  0x1BADB002		; 'Magic number' for recognition
CHECKSUM     equ -(MAGIC + FLAGS)	; Checksum (required by bootleader)

section .text				; CODE SECTION
align 4

MultiBootHeader:
	dd	MAGIC
	dd	FLAGS
	dd	CHECKSUM

KernelStart:
	lgdt	[ GDTR ]

	mov	ax, DATA_SEGMENT	; Initialize segment registers
	mov	ds, ax			;   by setting to new data selector
	mov	es, ax
	mov	fs, ax
	mov	gs, ax

	mov	ss, ax			; Initialize kernel stack
	mov	eax, StackLimit		; End of stack (moves backwards)
	mov	esp, eax

	xor	ebp, ebp

	jmp	CODE_SEGMENT:Continue	; Load new selector in CS

Continue:
	push	ebx			; Save address of multiboot info
	call	main

Halt:
	jmp	Halt			; Main should not return

UpdateGdt
	mov		eax, [esp+4]
	mov		[GDTR+2], eax
	mov		ax, [esp+8]
	mov		[GDTR], ax
	lgdt	[GDTR]
    
    ret
    
GLOBAL farCall
farCall:
        jmp [esp+4]
        ret

LoadIdt:
    lidt [IDTR]
    ret

GetEBP
	mov	eax, ebp
	ret

; ****************************************************************************
;  INTERRUPT SERVICE ROUTINES (CPU EXCEPTIONS)
; ****************************************************************************

; Textual descriptions are taken from
; Bran's Kernel Development Tutorial

;  0: Divide By Zero Exception
isr0:
    cli
    push byte 0
    push byte 0
    call CPUExceptionHandler
    add esp, 8
    iret

;  1: Debug Exception
isr1:
    cli
    push byte 0
    push byte 1
    call CPUExceptionHandler
    add esp, 8
    iret

;  2: Non Maskable Interrupt Exception
isr2:
    cli
    push byte 0
    push byte 2
    call CPUExceptionHandler
    add esp, 8
    iret

;  3: Int 3 Exception
isr3:
    cli
    push byte 0
    push byte 3
    call CPUExceptionHandler
    add esp, 8
    iret

;  4: INTO Exception
isr4:
    cli
    push byte 0
    push byte 4
    call CPUExceptionHandler
    add esp, 8
    iret

;  5: Out of Bounds Exception
isr5:
    cli
    push byte 0
    push byte 5
    call CPUExceptionHandler
    add esp, 8
    iret

;  6: Invalid Opcode Exception
isr6:
    cli
    push byte 0
    push byte 6
    call CPUExceptionHandler
    add esp, 8
    iret

;  7: Coprocessor Not Available Exception
isr7:
    cli
    push byte 0
    push byte 7
    call CPUExceptionHandler
    add esp, 8
    iret

;  8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push byte 8
    call CPUExceptionHandler
    add esp, 8
    iret

;  9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push byte 0
    push byte 9
    call CPUExceptionHandler
    add esp, 8
    iret

; 10: Bad TSS Exception (With Error Code!)
isr10:
    cli
    push byte 10
    call CPUExceptionHandler
    add esp, 8
    iret

; 11: Segment Not Present Exception (With Error Code!)
isr11:
    cli
    push byte 11
    call CPUExceptionHandler
    add esp, 8
    iret

; 12: Stack Fault Exception (With Error Code!)
isr12:
    cli
    push byte 12
    call CPUExceptionHandler
    add esp, 8
    iret

; 13: General Protection Fault Exception (With Error Code!)
isr13:
    cli
    push byte 13
    call CPUExceptionHandler
    add esp, 8
    iret

; 14: Page Fault Exception (With Error Code!)
isr14:
    cli
    push byte 14
    call CPUExceptionHandler
    add esp, 8
    iret

; 16: Floating Point Exception
isr16:
    cli
    push byte 0
    push byte 16
    call CPUExceptionHandler
    add esp, 8
    iret

; 17: Alignment Check Exception
isr17:
    cli
    push byte 0
    push byte 17
    call CPUExceptionHandler
    add esp, 8
    iret

; 18: Machine Check Exception
isr18:
    cli
    push byte 0
    push byte 18
    call CPUExceptionHandler
    add esp, 8
    iret
    
; 96: System Call API
isr96:
    cli
    
    cmp eax,0
    je open
    cmp eax,1
    je read
    cmp eax,2
    je write
    cmp eax,3
    je gettime
    cmp eax,4
    je sleep
    jmp end
    
  open:
  	jmp end
  read:
  	jmp end
  write:
  	jmp end
  gettime:
  	call GetTime
  	jmp end
  sleep:
  	push ebx
  	call Sleep
  	jmp end  	  	 
    
  end:
    iret
    
; ****************************************************************************
;  INTERRUPT REQUESTS
; ****************************************************************************
    
; There are 3 Interrupts that should be handled separately:
; timer, RTC, keyboard and mouse interrupts.
; Other interrupts are handled by a default interrupt handler.

; 32: IRQ0 - Timer Interrupt
irq0:
	cli
    pushad
    call TimerHandler
    popad
    iret

; 33: IRQ1 - Keyboard Interrupt
irq1:
    cli
    pushad
    call KeyboardHandler
    popad
    iret

; 34: IRQ2
irq2:
    cli
    pushad
    push byte 34
    call DefaultInterruptHandler
    add esp, 4
    popad
    iret

; 35: IRQ3
irq3:
    cli
    pushad
    push byte 35
    call DefaultInterruptHandler
    add esp, 4
    popad
    iret

; 36: IRQ4
irq4:
    cli
    pushad
    push byte 36
    call DefaultInterruptHandler
    add esp, 4
    popad
    iret

; 37: IRQ5
irq5:
    cli
    pushad
    push byte 37
    call DefaultInterruptHandler
    add esp, 4
    popad
    iret

; 38: IRQ6
irq6:
    cli
    pushad
    push byte 38
    call DefaultInterruptHandler
    add esp, 4
    popad
    iret

; 39: IRQ7
irq7:
    cli
    pushad
    push byte 39
    call DefaultInterruptHandler
    add esp, 4
    popad
    iret

; 40: IRQ8 - Real Time Clock
irq8:
    cli
    pushad
    call RTCHandler
    popad
    iret

; 41: IRQ9
irq9:
    cli
    pushad
    push byte 41
    call DefaultInterruptHandler
    add esp, 4
    popad
    iret

; 42: IRQ10
irq10:
    cli
    pushad
    push byte 42
    call DefaultInterruptHandler
    add esp, 4
    popad
    iret

; 43: IRQ11
irq11:
    cli
    pushad
    push byte 43
    call DefaultInterruptHandler
    add esp, 4
    popad
    iret

; 44: IRQ12 - PS/2 Mouse Interrupt
irq12:
    cli
    pushad
    call MouseHandler
    popad
    iret

; 45: IRQ13
irq13:
    cli
    pushad
    push byte 45
    call DefaultInterruptHandler
    add esp, 4
    popad
    iret

; 46: IRQ14
irq14:
    cli
    pushad
    push byte 46
    call DefaultInterruptHandler
    add esp, 4
    popad
    iret

; 47: IRQ15
irq15:
    cli
    pushad
    push byte 47
    call DefaultInterruptHandler
    add esp, 4
    popad
    iret

; ****************************************************************************
;  GLOBAL DESCRIPTOR TABLE
; ****************************************************************************
section .data

GDTR
	dw	01fh
	dd	GDT

GDT
NULL_SEGMENT	equ 0
	dd 	0
	dd	0
CODE_SEGMENT	equ 8
	dw 0ffffh
	dw 0
	db 0
	db 09ah
	db 0cfh
	db 0h
DATA_SEGMENT	equ 010h
	dw 0ffffh
	dw 0h
	db 0
	db 092h
	db 0cfh
	db 0

; ****************************************************************************
;  KERNEL STACK
; ****************************************************************************

STACK_SIZE equ 0x4000			; 16K stack size

section .bss

stack
	resb STACK_SIZE
StackLimit:

