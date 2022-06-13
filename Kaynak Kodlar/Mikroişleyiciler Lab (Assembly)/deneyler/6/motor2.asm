EKRAN	DB	"        "	;Ekran temizlemek i�in

ORG 200H

MODEREG		EQU	086H
PORT1CTL	EQU	088H

PORT1	EQU	090H
PORT2	EQU	092H

	MOV	BX, 0
	PUSH	BX

TEKRAR:	MOV	AL,00H
	OUT	MODEREG,AL
	MOV	AL,0AH
	OUT	PORT1CTL,AL

	MOV	AL,02H
	OUT	PORT1,AL
	MOV	AL,00H
	OUT	PORT1,AL
	MOV	AL,02H
	OUT	PORT1,AL

BEKLE:	IN	AL,PORT1
	TEST	AL,04H
	JZ	BEKLE

	MOV	AL,0F7H
	OUT	PORT1,AL
	IN	AL,PORT2
	MOV	BL,AL

	;MOTOR
	MOV	AL,01H
	OUT	PORT1CTL, AL
	MOV	AL,03H
	OUT	MODEREG,AL
	MOV	AL,00H
	OUT	PORT1,AL

	CMP	BL,40H
	JB	YAVAS
	MOV	AL,BL
	JMP	DVM

YAVAS:	MOV	AL,40H
DVM:	OUT	PORT2,AL

	MOV	CX, 0FFFFH ; X milisaniye bekle

DONGU1:

CHECK1:	DEC	CX
	CMP	CX,0
	JBE	CIK
	IN	AL, PORT1
	TEST	AL,10H
	JNZ	OUTLOW
	JMP 	CHECK1
CHECK0:	DEC	CX
	CMP	CX,0
	JBE	CIK	
	IN	AL, PORT1
	TEST	AL,10H
	JZ	OUTHIGH
	JMP	CHECK0	 
	 
OUTLOW:	POP	BX
	INC	BX
	PUSH	BX
	JMP	CHECK0

OUTHIGH:

	CMP	CX, 0
	JBE	CIK	
	JMP	DONGU1
CIK:

	; EKRAN TEMIZLE
	MOV	DI, OFFSET EKRAN
	MOV	BL,3            
 	MOV    	CX,8     
        MOV    	AH,02H
        INT    	28H
	
	; HIZ ISLEMI
	POP	BX
	PUSH	BX
	SHL	BX, 1	; 2 ye b�l
	
	; HEX E CEVIR
	MOV	DI,400H
	MOV	CX, 4
	MOV	AH, 09H
	INT	28H
	
	POP	BX
	MOV	BX, 0	; BX'i 0 l�yoruz
	PUSH	BX
	
	; SAYI EKRANA AZ
	MOV	DI, 400H
	MOV	BL,3            
 	MOV    	CX,4     
        MOV    	AH,02H
        INT    	28H	
	
	JMP	TEKRAR

	END