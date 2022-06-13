ORG 200H

INCLUDE PATCALLS.INC

INT25V          EQU     0094H
MODEREG         EQU     086H
PORT1CTL        EQU     088H
PORT1           EQU     090H
PORT2           EQU     092H
        
        
        CLI
        MOV     DX, DS
        MOV     AX, 0000H
        MOV     DS, AX

        MOV     WORD PTR DS:INT25V, 0500H
        MOV     WORD PTR DS:INT25V + 2, 080H
        MOV     DS, DX

        MOV     AL, 03H
        OUT     UCRREG1, AL
        
        MOV     AL, 40H         
        OUT     UMODEREG, AL
        CALL    TIMINT
        STI

        MOV     DX, 0

TEKRAR: 
        MOV     AL,00H
        OUT     MODEREG,AL
        MOV     AL,0AH
        OUT     PORT1CTL,AL

        MOV     AL,02H
        OUT     PORT1,AL
        MOV     AL,00H
        OUT     PORT1,AL
        MOV     AL,02H
        OUT     PORT1,AL

BEKLE:  IN      AL,PORT1
        TEST    AL,04H
        JZ      BEKLE

        MOV     AL,0F7H
        OUT     PORT1,AL
        IN      AL,PORT2
        MOV     BL,AL

        ;MOTOR
        MOV     AL,01H
        OUT     PORT1CTL, AL
        MOV     AL,03H
        OUT     MODEREG,AL
        MOV     AL,00H
        OUT     PORT1,AL

        MOV     AL,BL
        OUT     PORT2,AL


CHECK1: IN      AL, PORT1
        TEST    AL,10H
        JNZ     OUTLOW
        JMP     CHECK1

CHECK0: IN      AL, PORT1
        TEST    AL,10H
        JZ      OUTHIGH
        JMP     CHECK0   
         
OUTLOW: 
	INC	DX
        JMP     CHECK0

OUTHIGH:        
	
	JMP     TEKRAR

YAZ:
        PUSHA
        ; EKRAN TEMIZLE
      ;  MOV     DI, OFFSET EKRAN
      ;  MOV     BL,3            
      ;  MOV     CX,8     
      ;  MOV     AH,02H
      ;  INT     28H
        
       POPA

;	MOV CX, 0FFFH
;DON1:   LOOP DON1
	;MOV    DS:SAYI, 0 ; sayi sifirla
        RET

TIMINT: 
        PUSHA
        MOV     AL, 03H
        OUT     UTIMER4, AL
        MOV     AL, 0E8H
        OUT     UTIMER2, AL
        MOV     AL, 40H
        OUT     UIRQEN, AL
        POPA
        RET

        ; SERVIS RUTIN
        ORG     500H
        PUSHA
        IN      AL, UIRQADR
        CALL    TIMINT
        ;CALL    YAZ
	
	; HIZ ISLEMI
        MOV     BX, DX
	MOV	DS:900H, BX
        SHR     BX, 1
        
        ;ASCII E CEVIR
        MOV     DI, 700H
        MOV     CX, 4
        MOV     AH, 09H
        INT     28H
        
        ; SAYI EKRANA AZ
        MOV     DI, 700H
        MOV     BL,3            
        MOV     CX,8     
        MOV     AH,02H
        INT     28H

	MOV	DX, 0000H

        MOV     AL, 20H
        OUT     40H, AL
        POPA
        IRET

;EKRAN   DB      "        "
;SAYI    DW      0000H
        
END