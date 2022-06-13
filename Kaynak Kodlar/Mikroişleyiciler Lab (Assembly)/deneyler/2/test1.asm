
OKU:	MOV	DI, 400H    
        MOV     BL,3
        MOV     CX,3
        MOV     AH,00H   ; oku
        INT     28H      

HEXCEV:	MOV	AH, 06H
	MOV	DI, 400H
	INT	28H

	MOV	CX, AX

DECCEV: MOV	AH,09H
	MOV	BX,CX
	MOV	CX,4
	MOV 	DI, 500H
	INT	28H

HEXYAZ:	MOV	DI,400H
	MOV	BL,3
	MOV	CX,4
	MOV	AH,02H
	INT	28H

DECYAZ: MOV	DI, 500H
	MOV     BL,3            
	MOV     CX,4     
        MOV     AH,02H
        INT     28H

SON:	MOV	AH,04H
	MOV	BX,0
	INT	28H
        
        END