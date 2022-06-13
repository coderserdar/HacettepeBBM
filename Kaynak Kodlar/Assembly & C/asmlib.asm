extern	get_node

global	create_tree
global	inorder
global	calculate

;_________________________________________   create_tree   ___________________________________

create_tree:

	push	ebp						; save ebp
	mov		ebp, esp				; get current stack pointer
	push	ebx						; save ebx
	push	esi						; save esi
	
	mov		esi, [ebp + 12]			; get evaluation string
	mov		ebx, [ebp + 16]			; get evaluation string length
	dec		ebx						; get the index of the last character
	
pop_char:							; get a character from the end of the string

	movzx	edx, byte [esi + ebx]	; get the character
	
	push	edx
	call	get_node				; get a tree node for the character
	pop		edx
	
	cmp		edx, '0'				; check whether the character is a digit or an operator
	jb		operator
	cmp		edx, '9'
	ja		operator
	
digit:								; we have a digit
	
	push	eax						; push the node to the stack
	jmp		continue
	
operator:							; we have an operator

	pop		edx						; pop the first operand from the stack
	mov		[eax], edx				; make it the left child of the operator
	
	pop		edx						; pop the first operand from the stack
	mov		[eax + 8], edx			; make it the right child of the operator
	
	push	eax						; push the operator node to the stack

continue:
	
	dec		ebx
	jns		pop_char				; loop while ecx >= 0		

return_root:

	pop		edx						; get the root node
	mov		eax, [ebp + 8]			; get pointer to the top of the tree
	mov		[eax], edx				; assign the root node to the top of the tree
	
	pop		esi						; restore esi
	pop		ebx						; restore ebx
	pop		ebp						; restore ebp
	ret								; return to caller


;_________________________________________   inorder   _______________________________________

inorder:

	push	ebp						; save ebp
	mov		ebp, esp				; get current stack pointer
	push	ebx						; save ebx
	push	edx						; save edx
	push	edi						; save edi
	
	mov		edx, [ebp + 8]			; get the root node
	mov		edi, [ebp + 12]			; get offset of the destination string
	
	xor		ebx, ebx				; index for the destination string
	
	cmp		dword [edx], 0			; check if the root node has children
	jnz		put_all

put_digit:							; root node is a digit, has no children
	
	mov		eax, [edx + 4]			; put digit to the destination string
	mov		byte [edi + ebx], al
	inc		ebx
	
	jmp		return_expression

put_all:							; root node is an opeator, has two children
	
	mov		byte [edi + ebx], '('	; put left parenthesis
	inc		ebx
	
	mov		eax, edi
	add		eax, ebx
	push	eax						; push current destination offset+index
	
	push	dword [edx]				; push the left child
	call	inorder					; call self for the left child
	add		esp, 8
	
	add		ebx, eax				; update destination index
	
	mov		eax, [edx + 4]			; put operator to the destination string
	mov		byte [edi + ebx], al
	inc		ebx
	
	mov		eax, edi
	add		eax, ebx
	push	eax						; push current destination offset+index
	
	push	dword [edx + 8]			; push the right child
	call	inorder					; call self for the right child
	add		esp, 8
	
	add		ebx, eax				; update destination index
	
	mov		byte [edi + ebx], ')'	; put right parenthesis
	inc		ebx

return_expression:

	mov		byte [edi + ebx], 0		; append null at the end of the string
	mov		eax, ebx				; return current destination index
	
	pop		edi						; restore edi
	pop		edx						; restore edx
	pop		ebx						; restore ebx
	pop		ebp						; restore ebp
	ret								; return to caller


;_________________________________________   calculate   _____________________________________

calculate:

	push	ebp						; save ebp
	mov		ebp, esp				; get current stack pointer
	push	ebx						; save ebx
	push	edx						; save edx
	
	mov		edx, [ebp + 8]			; get the root node
	
	cmp		dword [edx], 0			; check if the root node has children
	jnz		do_operation

get_value:							; root node is a digit, has no children
	
	mov		eax, [edx + 4]			; get integer value of the digit
	sub		eax, 30h
	
	jmp		return_result

do_operation:						; root node is an opeator, do operation
	
	push	dword [edx + 8]			; push the right child
	call	calculate				; call self for the right child
	add		esp, 4
	
	mov		ebx, eax				; preserve the second operand
	
	push	dword [edx]				; push the left child
	call	calculate				; call self for the left child
	add		esp, 4
	
	cmp		byte [edx + 4], '+'		; determine the type of operation
	jz		addition
	cmp		byte [edx + 4], '-'
	jz		subtraction
	cmp		byte [edx + 4], '*'
	jz		multiplication
	cmp		byte [edx + 4], '/'
	jz		division
	
addition:							; add two opeands
	add		eax, ebx
	jmp		return_result
	
subtraction:						; subtract the second operand from the first operand
	sub		eax, ebx
	jmp		return_result

multiplication:						; multiplicate two operands
	imul	ebx
	jmp		return_result

division:							; divide the first operand by the second operand
	cdq								; sign-extend eax to edx:eax
	idiv	ebx

return_result:
	
	pop		edx						; restore edx
	pop		ebx						; restore ebx
	pop		ebp						; restore ebp
	ret								; return to caller
