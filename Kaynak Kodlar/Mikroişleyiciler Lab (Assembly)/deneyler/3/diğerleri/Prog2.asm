
        INCLUDE PATCALLS.INC

        ORG     0100h
        
mov ah, 0h
mov bl, 3h
mov cx, 4h
mov di, ds:1000h
int 28h


DONGU:
 
mov ah, 0h
mov bl, 3h
mov cx, 4h
mov di, ds:1050h
int 28h

mov dx,0000h
push dx

mov al, byte ptr ds:1050h
cmp al, byte ptr ds:1000h
jz  BIR
pop dx
mov dx, 0ffffh
push dx
;mov byte ptr ds:1050h, 000h
BIR:

mov al, byte ptr ds:1051h
cmp al, byte ptr ds:1001h
jz  IKI
pop dx
mov dx, 0ffffh
push dx
;mov byte ptr ds:1051h, 000h
IKI:

mov al, byte ptr ds:1052h
cmp al, byte ptr ds:1002h
jz  UC
pop dx
mov dx,0ffffh
push dx
;mov byte ptr ds:1052h, 000h
UC:

mov al, byte ptr ds:1053h
cmp al, byte ptr ds:1003h

jz  DORT
pop dx
mov dx,0ffffh
push dx
;mov byte ptr ds:1053h, 000h
DORT:

mov ah, 2h
mov cx, 8h
mov bl, 3h
mov di,ds:1050h
int 28h

pop dx
cmp dx, 0ffffh

je DONGU

mov ah, 4h
mov bx,0000h
int 28h
