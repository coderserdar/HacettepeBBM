;  CODE OMER AKYOL & SELCUK ERKOC  16.3.2007

	ORG 200H

STR2    DB      "        "

STR1	DB	"x       "
	DB	"xx      "
	DB	"xxx     "
	DB	" xxx    "
	DB	"   xxx  "
	DB	"     xxx"
	DB	"      xx"
	DB	"       x"
	DB	"      xx"
	DB	"     xxx"
	DB	"    xxx "
	DB	"   xxx  "
	DB	"  xxx   "
	DB	" xxx    "
	DB	"xxx     "
	DB	"xx      "
	DB	"x       "

;SZ_STR1 EQU     ($-STR1)


TEKRAR:
	MOV    DI, OFFSET STR1	
	PUSH   DI
DONGU:
	
	; TEMIZLE
	MOV	DI, OFFSET STR2
	MOV    BL,3            
 	MOV    CX,8     
        MOV    AH,02H
        INT    28H

	POP	DI 
	MOV    BL,3            
 	MOV    CX,8     
        MOV    AH,02H
        INT    28H
	PUSH   DI
	
	;ADD    DI, 4

	CMP    DI, 290H
	JZ     TEKRAR     

	;BEKLE
	MOV    AH, 10H
        MOV    BX, 200
        INT    28H

	JMP DONGU

	END