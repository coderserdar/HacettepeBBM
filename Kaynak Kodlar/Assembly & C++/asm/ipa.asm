.586
.MODEL FLAT, C
.STACK
.DATA
.CODE

grayscale PROC

	push	ebp
	mov		ebp, esp
	push	edi
	push	ebx
	
	mov		ecx, [ebp + 12]				; size of image data in bytes
	mov		edi, [ebp + 8]				; address of image data
	
	grayscale_putpixel:
	
		mov		al, [edi + ecx - 1]		; red
		movzx	edx, al					; edx = red
		
		dec		ecx
		
		mov		eax, 0
		mov		al, [edi + ecx - 1]		; green
		shl		eax, 2
		add		edx, eax
		
		dec		ecx
		
		mov		eax, 0
		mov		al, [edi + ecx - 1]		; blue
		shl		eax, 1
		add		edx, eax
		
		mov		eax, 73
		mul		edx
		shr		eax, 9
		
		cmp		eax, 255
		jbe		setval
		
		mov		al, 255			
		
		setval:
		
		mov		[edi + ecx - 1], al
		mov		[edi + ecx], al
		mov		[edi + ecx + 1], al		
		
	loop	grayscale_putpixel
	
	pop		ebx
	pop		edi
	pop     ebp
	ret
	
grayscale ENDP

rotate PROC

	push	ebp
	mov		ebp, esp
	push	edi
	
	mov		ecx, [ebp + 12]				; size of image data in bytes
	mov		edi, [ebp + 8]				; address of image data
	
	shr		ecx, 1						; ecx = image size / 2
	mov		edx, ecx					; edx = image size / 2

	rotate_putpixel:
	
		mov		al, [edi + ecx - 1]		; red
		xchg	[edi + edx + 2], al
		mov		[edi + ecx - 1], al
		
		dec		ecx
		
		mov		al, [edi + ecx - 1]		; green
		xchg	[edi + edx + 1], al
		mov		[edi + ecx - 1], al
		
		dec		ecx
		
		mov		al, [edi + ecx - 1]		; blue
		xchg	[edi + edx], al
		mov		[edi + ecx - 1], al
		
		add		edx, 3
		
	loop	rotate_putpixel
	
	pop		edi
	pop     ebp
	ret
	
rotate ENDP

clear PROC

	push	ebp
	mov		ebp, esp
	push	edi
	
	mov		eax, [ebp + 16]				; height of image	
	mov		edx, [ebp + 12]				; width of image
	mov		edi, [ebp + 8]				; address of image data
	
	mul		edx							; width * height
	mov		edx, 3
	mul		edx							; width * height * 3
	mov		ecx, eax
	
	mov		eax, [ebp + 20]			; al = val
	
	clear_putpixel:
	
		mov		[edi + ecx - 1], al
		
	loop	clear_putpixel
	
	pop		edi
	pop     ebp
	ret
	
clear ENDP

grow PROC

	push	ebp
	mov		ebp, esp
	push	esi
	push	edi
	push	ebx
	
	mov		esi, [ebp + 8]				; address of image data
	mov		edi, [ebp + 12]				; address of new image data
	
	mov		eax, 3
	mul		DWORD PTR [ebp + 20]
	mul		DWORD PTR [ebp + 16]
	
	mov		ecx, eax					; ecx = width * height * 3
	
	shl		eax, 2						; eax = width * height * 2 * 2 * 3
	mov		ebx, [ebp + 16]				; ebx = image width	
	
	grow_putpixel:
	
		mov		dl, [esi + ecx - 1]		; red
		
		mov		[edi + eax - 1], dl
		mov		[edi + eax - 4], dl
		
		mov		dl, [esi + ecx - 2]		; green
		
		mov		[edi + eax - 2], dl
		mov		[edi + eax - 5], dl
		
		mov		dl, [esi + ecx - 3]		; blue
		
		mov		[edi + eax - 3], dl
		mov		[edi + eax - 6], dl
		
		sub		eax, [ebp + 16]
		sub		eax, [ebp + 16]
		sub		eax, [ebp + 16]
		sub		eax, [ebp + 16]
		sub		eax, [ebp + 16]
		sub		eax, [ebp + 16]			; to the lower row
		
		mov		dl, [esi + ecx - 1]		; red
		
		mov		[edi + eax - 1], dl
		mov		[edi + eax - 4], dl
		
		mov		dl, [esi + ecx - 2]		; green
		
		mov		[edi + eax - 2], dl
		mov		[edi + eax - 5], dl
		
		mov		dl, [esi + ecx - 3]		; blue
		
		mov		[edi + eax - 3], dl
		mov		[edi + eax - 6], dl
				
		add		eax, [ebp + 16]
		add		eax, [ebp + 16]
		add		eax, [ebp + 16]
		add		eax, [ebp + 16]
		add		eax, [ebp + 16]
		add		eax, [ebp + 16]			; to the upper row
		
		dec		ebx
		jnz		same_row
		
		mov		ebx, [ebp + 16]
		
		sub		eax, [ebp + 16]
		sub		eax, [ebp + 16]
		sub		eax, [ebp + 16]
		sub		eax, [ebp + 16]
		sub		eax, [ebp + 16]
		sub		eax, [ebp + 16]			; to the lower row
		
		same_row:
		
		sub		eax, 6
		sub		ecx, 3
	
	jnz		grow_putpixel
	
	pop		ebx
	pop		edi
	pop		esi
	pop     ebp
	ret
	
grow ENDP

invert PROC

	push	ebp
	mov		ebp, esp
	push	edi
	
	mov		eax, [ebp + 16]				; height of image	
	mov		edx, [ebp + 12]				; width of image
	mov		edi, [ebp + 8]				; address of image data
	
	mul		edx							; width * height
	mov		edx, 3
	mul		edx							; width * height * 3
	mov		ecx, eax
	
	invert_putpixel:
	
		mov		al, [edi + ecx - 1]
		mov		ah, 255
		sub		ah, al
		mov		[edi + ecx - 1], ah
		
	loop	invert_putpixel
	
	pop		edi
	pop     ebp
	ret
	
invert ENDP

brightness PROC

	push	ebp
	mov		ebp, esp
	push	edi
	
	mov		eax, [ebp + 16]				; height of image	
	mov		edx, [ebp + 12]				; width of image
	mov		edi, [ebp + 8]				; address of image data
	
	mul		edx							; width * height
	mov		edx, 3
	mul		edx							; width * height * 3
	mov		ecx, eax
	
	mov		eax, [ebp + 20]				; eax = val
	
	brightness_putpixel:
	
		mov		eax, [ebp + 20]			; al = val
		movzx	edx, BYTE PTR [edi + ecx - 1]
		add		eax, edx
		js		lower_limit
		
		cmp		eax, 255
		jg		upper_limit
		jmp		putpixel
		
		lower_limit:
		mov		al, 0
		jmp		putpixel
		
		upper_limit:
		mov		al, 255		
		
		putpixel:
		mov		[edi + ecx - 1], al
		
	loop	brightness_putpixel
	
	pop		edi
	pop     ebp
	ret
	
brightness ENDP

contrast PROC

	push	ebp
	mov		ebp, esp
	push	edi
	
	mov		eax, [ebp + 16]				; height of image	
	mov		edx, [ebp + 12]				; width of image
	mov		edi, [ebp + 8]				; address of image data
	
	mul		edx							; width * height
	mov		edx, 3
	mul		edx							; width * height * 3
	mov		ecx, eax
	
	mov		eax, [ebp + 20]				; eax = val
	
	contrast_putpixel:
	
		mov		eax, [ebp + 20]			; al = val
		movzx	edx, BYTE PTR [edi + ecx - 1]
		mul		edx
		sar		eax, 6
		
		js		lower_limit
		
		cmp		eax, 255
		jg		upper_limit
		jmp		putpixel
		
		lower_limit:
		mov		al, 0
		jmp		putpixel
		
		upper_limit:
		mov		al, 255		
		
		putpixel:
		mov		[edi + ecx - 1], al
		
	loop	contrast_putpixel
	
	pop		edi
	pop     ebp
	ret
	
contrast ENDP

shrink PROC

	push	ebp
	mov		ebp, esp
	push	esi
	push	edi
	push	ebx
	
	mov		esi, [ebp + 8]				; address of image data
	mov		edi, [ebp + 12]				; address of new image data
	
	mov		eax, 3
	mul		DWORD PTR [ebp + 20]
	mul		DWORD PTR [ebp + 16]
	shr		eax, 2
	
	mov		ecx, eax					; ecx = (width * height * 3) / 4
	
	shl		eax, 2						; eax = width * height * 3
	mov		ebx, [ebp + 16]
	shr		ebx, 1						; ebx = new image width
	
	sub		eax, [ebp + 16]
	sub		eax, [ebp + 16]
	sub		eax, [ebp + 16]				; to the lower row
	
	shrink_putpixel:
		
		sub		eax, 3					; skip pixel
	
		mov		dl, [esi + eax - 1]		; red
		mov		[edi + ecx - 1], dl
		
		mov		dl, [esi + eax - 2]		; green
		mov		[edi + ecx - 2], dl
		
		mov		dl, [esi + eax - 3]		; blue
		mov		[edi + ecx - 3], dl
				
		dec		ebx
		jnz		same_row
		
		mov		ebx, [ebp + 16]
		shr		ebx, 1					; ebx = new image width
		
		sub		eax, [ebp + 16]
		sub		eax, [ebp + 16]
		sub		eax, [ebp + 16]			; to the lower row
		
		same_row:
		
		sub		eax, 3
		sub		ecx, 3
	
	jnz		shrink_putpixel
	
	pop		ebx
	pop		edi
	pop		esi
	pop     ebp
	ret
	
shrink ENDP


blur PROC

	push	ebp
	mov		ebp, esp
	push	esi
	push	edi
	push	ebx
	
	mov		esi, [ebp + 8]				; address of image data
	
	mov		eax, 3
	mul		DWORD PTR [ebp + 12]
	mul		DWORD PTR [ebp + 16]
	
	mov		ecx, eax					; ecx = width * height * 3
	
	mov		eax, 3
	mul		DWORD PTR [ebp + 12]		; eax = width * 3
	
	mov		ebx, [ebp + 12]				; ebx = image width	
	
	blur_putpixel:
	
		movzx	edx, BYTE PTR [esi + ecx - 1]		; red
		movzx	edi, BYTE PTR [esi + ecx - 4]
		add		edx, edi
		
		sub		ecx, eax				; to the lower row
		
		movzx	edi, BYTE PTR [esi + ecx - 1]
		add		edx, edi
		movzx	edi, BYTE PTR [esi + ecx - 4]
		add		edx, edi
		
		shr		edx, 2
		
		mov		[esi + ecx - 1], dl
		mov		[esi + ecx - 4], dl
		
		add		ecx, eax				; to the upper row
		
		mov		[esi + ecx - 1], dl
		mov		[esi + ecx - 4], dl
		
		movzx	edx, BYTE PTR [esi + ecx - 2]		; green
		movzx	edi, BYTE PTR [esi + ecx - 5]
		add		edx, edi
		
		sub		ecx, eax				; to the lower row
		
		movzx	edi, BYTE PTR [esi + ecx - 2]
		add		edx, edi
		movzx	edi, BYTE PTR [esi + ecx - 5]
		add		edx, edi
		
		shr		edx, 2
		
		mov		[esi + ecx - 2], dl
		mov		[esi + ecx - 5], dl
		
		add		ecx, eax				; to the upper row
		
		mov		[esi + ecx - 2], dl
		mov		[esi + ecx - 5], dl
		
		movzx	edx, BYTE PTR [esi + ecx - 3]		; blue
		movzx	edi, BYTE PTR [esi + ecx - 6]
		add		edx, edi
		
		sub		ecx, eax				; to the lower row
		
		movzx	edi, BYTE PTR [esi + ecx - 3]
		add		edx, edi
		movzx	edi, BYTE PTR [esi + ecx - 6]
		add		edx, edi
		
		shr		edx, 2
		
		mov		[esi + ecx - 3], dl
		mov		[esi + ecx - 6], dl
		
		add		ecx, eax				; to the upper row
		
		mov		[esi + ecx - 3], dl
		mov		[esi + ecx - 6], dl
		
		sub		ebx, 2
		jnz		same_row
		
		mov		ebx, [ebp + 12]
		sub		ecx, eax				; to the lower row
		
		same_row:
		
		sub		ecx, 6
	
	jnz		blur_putpixel
	
	pop		ebx
	pop		edi
	pop		esi
	pop     ebp
	ret
	
blur ENDP

atleast PROC

	push	ebp
	mov		ebp, esp
	push	edi
	
	mov		eax, [ebp + 16]				; height of image	
	mov		edx, [ebp + 12]				; width of image
	mov		edi, [ebp + 8]				; address of image data
	
	mul		edx							; width * height
	mov		edx, 3
	mul		edx							; width * height * 3
	mov		ecx, eax
	
	mov		eax, [ebp + 20]				; al = val
	mov		edx, 0
	
	atleast_pixel:
	
		mov		ah, [edi + ecx - 1]
		
		cmp		ah, al
		jb		red_below
		inc		edx
		jmp		end_pixel
		
		red_below:
		cmp		ah, al
		jb		green_below
		inc		edx
		jmp		end_pixel
		
		green_below:
		cmp		ah, al
		jb		blue_below
		inc		edx
		jmp		end_pixel
		
		blue_below:
		cmp		ah, al
		jb		end_pixel
		inc		edx
		
		end_pixel:
		
	loop	atleast_pixel
	
	mov		eax, edx					; return value in eax
	
	pop		edi
	pop     ebp
	ret
	
atleast ENDP

END
