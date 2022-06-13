        ORG 0200H

MODEREG  EQU    086H

PORTCTL1 EQU    088H

PORT1    EQU    090H
PORT2    EQU    092H

        MOV     AL, 40H
        OUT     PORTCTL1, AL
        
        MOV     AL, 03H
        OUT     MODEREG, AL
        MOV     AL, 40H
        OUT     PORT1, AL

        MOV     CX, 0
        PUSH    CX

DETECT: IN      AL, PORT1
        TEST    AL, 80H
        JZ      COUNTER
        JMP     DETECT

COUNTER: MOV    AH, 10H
         MOV    BX, 1000
         INT    28H

         POP    CX
         INC    CX
         PUSH   CX


        MOV  AL, CL
        OUT  PORT2, AL

        JMP  DETECT

        END
      