        ORG     200H

PORTCTL1 EQU    088H
PORT1    EQU    090H

        MOV     AL, 60H
        OUT     PORTCTL1, AL

DETECT: MOV     AL, 00H
        OUT     PORT1, AL

        MOV     AL, 40H
        OUT     PORT1, AL

        IN      AL, PORT1
        TEST    AL, 80H
        JZ      ALARM
        JMP     DETECT

ALARM:  MOV     AL, 00H
        OUT     PORT1, AL

        MOV     CX, 0FFH
DELY1:  LOOP    DELY1
        
        MOV     AL, 20H
        OUT     PORT1, AL
        
        MOV     CX, 0FFH
DELY2:  LOOP    DELY2

        JMP     DETECT

        END
        