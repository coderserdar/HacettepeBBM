
; ****************************************************************************
;
; BBM OS EXAMPLE APPLICATION
;
;   Startup Assembly Code
;
; Copyright (C) Sukru TIKVES 2006
;
;   Based on parts by GRUB, FritzOS and others, see LICENCE for information
;
; ****************************************************************************

; ****************************************************************************
;  EXTERNAL SYMBOLS
; ****************************************************************************

EXTERN main				; Startup address of C/C++ main code

; ****************************************************************************
;  APPLICATION HEADER INFORMATION
; ****************************************************************************

MAGIC		equ 0x80868086		; 'Magic number' for recognition
DATA_SIZE	equ 0x4000		; 16K data area requested
ENTRY_POINT	equ 0x4010
CHECKSUM	equ ~ (MAGIC ^ DATA_SIZE ^ ENTRY_POINT)

section .text				; CODE SECTION
align 4

AppHeader:
	dd	MAGIC
	dd	DATA_SIZE
	dd	ENTRY_POINT
	dd	CHECKSUM

AppStart:
	xor	eax, eax		; Open file
	mov	ebx, CONSOLE
	mov	ecx, 0
	int	60h

	mov	ebx, eax		; Write message
	mov	eax, 2
	mov	ecx, 12
	mov	edx, MESSAGE
	int	60h

Exit:
	loop	Exit

CONSOLE
	db	"/dev/console"

MESSAGE
	db	"Hello World\n"
