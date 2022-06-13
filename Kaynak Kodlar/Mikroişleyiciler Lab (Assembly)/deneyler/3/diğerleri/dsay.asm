        ORG 0200H

UMODEREG        EQU 086H
UPORT1CTL       EQU 088H
UPORT1          EQU 090H
UPORT2          EQU 092H
                
                MOV AL, 40H
                OUT UPORT1CTL, AL
        
                MOV AL, 03H
                OUT UMODEREG, AL
                MOV AL, 40H
                OUT UPORT1, AL

                MOV CX, 0                

DETECT:         IN AL, UPORT1
                TEST AL, 80H
                JZ SAYAC
                JMP DETECT

SAYAC:          MOV AH, 010H
                MOV BX, 1000
                INT 28H

                INC CX
                MOV AL, CL
                OUT UPORT2, AL 

                OUT UPORT2, AL
                JMP DETECT

END