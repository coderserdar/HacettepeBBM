ORG 0200H

STR1 DB "SAYI GIR"
STR2 DB " TAHMIN "
STR3 DB "        "


OKU: 	
BOSLUK:
	MOV AH, 02H
        MOV BL,3
        MOV CX ,8
        MOV DI, OFFSET STR3
        INT 28H
   
SAYIISTE:	
	MOV AH, 02H
        MOV BL,3
        MOV CX ,8
        MOV DI, OFFSET STR1
        INT 28H

SAYIOKU:
	MOV AH, 00H
        MOV BL,3
        MOV CX ,4
        MOV DI, 300H
        INT 28H

BEKLE:
	MOV AH, 010H
        MOV BX, 3000
        INT 28H

	MOV CX, 0

DENEME:	MOV AX, CX
	CMP AX, 2
	JZ SON
	PUSH CX
	
TAHMINYAZ:
	MOV AH, 02H
       	MOV BL,3
        MOV CX ,8
        MOV DI, OFFSET STR2
        INT 28H

TAHMINOKU:
	MOV AH, 00H
       	MOV BL,3
       	MOV CX ,4
       	MOV DI, 500H
       	INT 28H
		
	POP CX
	INC CX

SAYITEST:	
	MOV AH, 010H
        MOV BX, 3000
        INT 28H

	JMP DENEME

        
SON:    MOV AH, 04H
        MOV BX , 0
        INT 28H   

        END