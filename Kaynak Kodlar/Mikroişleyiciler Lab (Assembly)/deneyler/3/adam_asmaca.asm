ORG	200H

STR1	DB	"   DOGRU"
STR2	DB	"  YANLIS"
STR3    DB	"SAYI GIR"
STR4	DB	"  TAHMIN"
STR5	DB	"        "
STR6    DB	"HAK    "
STR7    DB	"."

	;INIT
	MOV	BX, 7
	PUSH	BX
	
	; TEMIZLE 
	MOV	DI, OFFSET STR5
	MOV	BL,3            
 	MOV	CX,8     
        MOV	AH,02H
        INT	28H

	; MESAJ: "SAYI GIR"
	MOV	DI, OFFSET STR3
	MOV	BL,3            
	MOV	CX,8     
        MOV	AH,02H
	INT	28H  

	; 4 BASAMAKLI SAYI GIR
	MOV	DI, 400H    
        MOV     BL,3
        MOV     CX,4
        MOV     AH,00H   ; oku
        INT     28H 

TAHMIN:
	; TEMIZLE 
	MOV    DI, OFFSET STR5
	MOV    BL,3            
 	MOV    CX,8     
        MOV    AH,02H
        INT    28H 

	; MESAJ TAHMIN
	MOV    DI, OFFSET STR4
	MOV    BL,3            
	MOV    CX,8     
        MOV    AH,02H
	INT    28H
 
  
	; TAHMIN AL
	MOV	DI, 500H
	MOV     BL,3
        MOV     CX,4
        MOV     AH,00H   ; oku
        INT     28H

DOGRUMU: MOV	AX, DS:400H
	 MOV	BX, DS:500H  
	
	CMP	AX,BX
	JZ	BINGO 
	 
	 ; HAK KONTROL
	 POP	BX
	 DEC	BX
	 PUSH	BX
	 CMP	BX, 0
	 JZ	YANLIS

	 ; HAK GOSTER
	 MOV    DI, OFFSET STR6
	 MOV    BL,3            
	 MOV    CX,7     
         MOV    AH,02H
	 INT    28H

	 ; HAK
	 POP	BX
	 MOV	AX, BX
	 ADD	AX, 30H
	 MOV	DS:300H, AX
	 PUSH	BX

	 MOV	DI, 300H
	 MOV	BL,3
	 MOV	CX,1
	 MOV	AH,02H
	 INT	28H

	 ; BEKLE
	 MOV    AH, 10H
         MOV    BX, 2000
         INT    28H

	JMP	TAHMIN

BINGO:  MOV	DI, OFFSET STR1
	MOV     BL,3            
	MOV     CX,8     
        MOV     AH,02H
        INT     28H
	JMP	SON

YANLIS: MOV	DI, OFFSET STR2
	MOV     BL,3            
	MOV     CX,8     
        MOV     AH,02H
        INT     28H
	JMP	SON

SON:	MOV	AH,04H
	MOV	BX,0
	INT	28H
        
        END		
     