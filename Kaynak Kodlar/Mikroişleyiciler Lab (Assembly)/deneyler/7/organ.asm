ORG	200H

PORTCTL1	EQU	088H
PORT1		EQU	090H

	;INIT
	MOV	AL, 20H
	OUT	PORTCTL1, AL

	PUSH	BX

ANA_DONGU:
	; TUSA BAS
	MOV	DI, OFFSET KEY_CODE    
        MOV     BL,3
        MOV     CX,1
        MOV     AH,00H   	; Klavyeden tuþ oku
        INT     28H

	MOV	AX, KEY_CODE

	CMP	AX, 39H		; tuþ 39h dan büyük mü?
	JA	HARF		
	
	SUB	AX, 31H		; tuþ 39h dan küçükse
	JMP	DEVAM		; 31h çýkar ve devam et

HARF:	SUB	AX, 41H		; 39h'dan büyükse 41h çýkar
	ADD	AX, 9		; 9 ekle - indeks 0'dan baþlar

DEVAM:	
	POP	BX	
	SHL	AX,1		 ; Dizi WORD'lük olduðundan  
	MOV	DI, OFFSET NOTES ; Dizi offset'ini al	
	ADD	DI, AX		 ; Dizi offset'i üzerinde ilerle
	MOV	BX, [DI]	 ; Diziden döngü deðeri al
	PUSH	BX	       	 ; Alýnan dizi döngüsünü sakla

	MOV	BX, 0FH

PIEZO_CAL:			; PIEZO ses çaldýrma rutini
	MOV	AL, 00H		
	OUT	PORT1, AL	; piezo modül kapat
	
	POP	CX		; saklanan döngü deðerini al
	PUSH	CX		; tekrar sakla
DELY1:	LOOP	DELY1		; 1. bekleme

	MOV	AL, 20H
	OUT	PORT1, AL	; piezo modül aç
	
	POP	CX		; saklanan döngü deðerini al
	PUSH	CX		; tekrar sakla
DELY2:	LOOP	DELY2		; 2. bekleme
	
	MOV	AL, 00H		
	OUT	PORT1, AL	; piezo modül kapat

	DEC	BX		
	CMP	BX,0		; PIEZO ses çaldýrmasý bitti mi?
	JNZ	PIEZO_CAL	; bitmediyse çaldýrmaya devam

	JMP	ANA_DONGU	; bittiyse her þey en baþtan tekrar

NOTES	DW	1712, 1524, 1436, 1275, 1136, 1016, 936, 853, 766, 716, 637, 568, 507, 478, 418

KEY_CODE DB 	?

	END