	ORG 0200H

STR1 DB "SAYI GIR"
STR2 DB " TAHMIN "
STR3 DB "        "

OKU: 	MOV AH, 2
        MOV BL, 3
        MOV CX, 8
        MOV DI, OFFSET STR3
        INT 28H

	MOV AH, 2
        MOV BL, 3
        MOV CX, 8
        MOV DI, OFFSET STR1
        INT 28H

SON:    MOV AH, 04H
        MOV BX , 0
        INT 28H   

        END