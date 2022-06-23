
global rootNode
global nodeName
global nodeSurname
global grade
global print1
global print2
global print3
global space
global newline
global average
global no



section .data

rootNode 		: dd 0
print1   		: db "Tree:",0
print2   		: db "Node not found",0
print3   		: db "Tree is empty",0
space    		: db " ",0
newline  		: db 10
average  		: db "Average:",0
charBuffer 		: db " ",0
grade	 		: dd 0
no				: dd 0
nodeName		: dd 0

section .text

global addNode

addNode:
	push 			ebp
	mov 			ebp,esp
	
	mov 			edi,[ebp+8]
	mov 			eax,[ebp+12]
	cmp 			dword[rootNode],0
	jz 				createRoot
	mov 			esi,dword[rootNode]
	jmp 			placeNewNode	
		
	
createRoot:
	mov 			dword[rootNode],edi		;it creates
	jmp 			finalize				;the root
	
placeNewNode:

	cmp 			[esi+4],eax				;compare node's value with the the given parameter
	jg  			goToLeftChild			;if bigger go to left child
	jmp  			goToRightChild			;else go to right child

	
goToLeftChild:
	mov 			ecx,[esi]				;if left child is null
	cmp 			ecx,0					;add node as left child
	jz 				placeNode	
	mov 			esi,[esi]		
	jmp 			placeNewNode
	
goToRightChild:
	mov 			ecx,[esi+52]			;if left child is null
	cmp 			ecx,0					;add node as right child
	jz 				placeNode2	
	mov 			esi,[esi+52]		
	jmp 			placeNewNode
	
placeNode:
	mov 			dword[esi],edi
	jmp 			finalize
	
placeNode2:
	mov 			dword[esi+52],edi
	
	
finalize:
	pop 			ebp
	ret
	
	


global calculateAverage

calculateAverage:
	push 			ebp
	mov 			ebp,esp

	mov  			eax,0
	mov  			ecx,0
	
	cmp 			dword[rootNode],0
	jz 				averagePrintNull
	push 			dword[rootNode]
	call 			takeNodeGrade
	pop 			esi
	
	mov 			edx,0
	div 			ecx
	mov 			esi,eax
	
final:
	pop 			ebp
	ret
	
averagePrintNull:
	mov 			eax,4					;it
	mov 			ebx,1					;says
	mov 			ecx,print3				;that
	mov 			edx,13					;tree
	int 			80h						;is 
	jmp 			final					;empty
	
	
	
takeNodeGrade:
	push 			ebp
	mov 			ebp,esp
	
	mov 			esi,[ebp+8]
	cmp 			esi,0
	jz 				averageFinalResults
	add 			eax,[esi+48]
	inc 			ecx


takeChildGrade:	
	mov 			esi, [ebp+8]
	mov 			edi,esi
	
	push 			edi						;it
	push 			dword[edi]				;goes to
	call 			takeNodeGrade			;left child
	pop 			edi
	pop 			edi
		
	push 			dword[edi+52]			;it
	call 			takeNodeGrade			;goes to
	pop 			edi						;right child
	
averageFinalResults:
	pop 			ebp
	ret
	
	

global printTree

printTree:
	push 			ebp
	mov 			ebp,esp

	cmp 			dword[rootNode],0
	jz 				printNull
	
	mov 			eax,4					;it 
	mov 			ebx,1					;says
	mov 			ecx,print1				;that
	mov 			edx,5					;tree 
	int 			80h						;is empty
	
	mov 			eax,4       			;it prints
	mov 			ebx,1       			;the
	mov 			ecx,newline 			;newline
	mov 			edx,1
	int 			80h
	
	push 			dword[rootNode]	
	call 			printTreeFirst
	pop 			esi
	
printNull:
	mov 			eax,4					;it
	mov 			ebx,1					;says
	mov 			ecx,print3				;that
	add 			ecx,4					;tree
	mov 			edx,4					;is
	int 			80h						;empty
	pop 			ebp
	ret
	
printTreeFirst:
	push 			ebp
	mov 			ebp,esp
	
	mov 			esi,[ebp+8]
	cmp 			esi,0
	jz 				printFinalResults

	
printSpace:
	mov 			eax,4      				;it prints
	mov 			ebx,1      				;a
	mov 			ecx,space  				;space
	mov 			edx,1     				;student no
	int 			80h        				;and student name
	jmp 			printName
	
printSurname:
	mov 			eax,4      				;it prints
	mov 			ebx,1      				;the
	mov 			ecx,esi    				;student
	add 			ecx,28     				;surname
	mov 			edx,20
	int 			80h
	jmp 			printNewline
	
printNewline:
	mov 			eax,4     				;it prints
	mov 			ebx,1      				;the
	mov 			ecx,newline				;student
	mov 			edx,1
	int 			80h

printChilds:	
	mov 			esi, [ebp+8]
	mov 			edi,esi
	
	push 			edi						;goes
	push 			dword[edi]				;to	
	call 			printTreeFirst			;the
	pop 			edi						;left child
	pop 			edi
		
	push 			dword[edi+52]			;goes
	call 			printTreeFirst			;to
	pop 			edi						;right child
	
printFinalResults:
	pop 			ebp
	ret
	
	
printName:
	mov 			eax,4      				;it prints
	mov 			ebx,1      				;the
	mov 			ecx,esi    				;student
	add 			ecx,8     				;name
	mov 			edx,20
	int 			80h
	jmp 			printSecondSpace
	
printSecondSpace:
	mov 			eax,4      				;it prints
	mov 			ebx,1      				;a
	mov 			ecx,space  				;space	
	mov 			edx,1      				;between
	int 			80h        				;student name
	jmp 			printSurname			;and student surname
	
	
	