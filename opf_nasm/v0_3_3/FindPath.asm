;Author:	Jonas Brown
;Date:		27/12-2016
;File: 		FindPath.asm

[BITS 64]
[SECTION .text]
[GLOBAL DllMain]
[GLOBAL FindPath]
[EXPORT DllMain]
[EXPORT FindPath]
;From _Node:
[EXTERN _Node.CheckAdjecentNodes]
[EXTERN _Node.Empty]
[EXTERN _Node.Traceback]
;From _Node2D:
[EXTERN _Node2D.GetByCoordinates]
;From Data - Node
[EXTERN Node.Resistance]
[EXTERN Node.Closed]
[EXTERN Node.PNext]
[EXTERN Node.Size]
;From Data - NodeStack
[EXTERN NodeStack.Top]
[EXTERN NodeStack.Bottom]
[EXTERN NodeStack.Count]
;From Data - NodeOpenList
[EXTERN NodeOpenList.First]
[EXTERN NodeOpenList.Count]
;From Data - Grid
[EXTERN Grid.TargetX]
[EXTERN Grid.TargetY]
[EXTERN Grid.StartX]
[EXTERN Grid.StartY]
[EXTERN Grid.PStartNode]
[EXTERN Grid.MapWidth]
[EXTERN Grid.MapHeight]
[EXTERN Grid.POutBuffer]
[EXTERN Grid.PMap]
[DEFAULT REL]

;windows dll entry
DllMain:
    mov eax, 1
    ret

;INTERFACE: fastcall64
;typedef int(*ASM_INTERFACE)(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, 
;const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize) 
FindPath:

	;check if start x coord is out-of-bounds
	cmp ecx, [rsp + 48]
	jge .no_path_found
	cmp ecx, 0
	jl .no_path_found
	;check if start y coord is out-of-bounds
	cmp edx, [rsp + 56]
	jge .no_path_found
	cmp edx, 0
	jl .no_path_found
	;check if target x coord is out-of-bounds
	cmp r8d, [rsp + 48]
	jge .no_path_found
	cmp r8d, 0
	jl .no_path_found
	;check if target y coord is out-of-bounds
	cmp r9d, [rsp + 56]
	jge .no_path_found
	cmp r9d, 0
	jl .no_path_found
	
	;initialize "per execution" tls data
	mov rbp, rsp			;save the stack ptr
	push qword 0			;push Grid.PStartNode@80 as qword
	mov rax, [rbp + 40]		;intercept arg Grid.PMap@72
	push rax				;push arg as qword				
	mov rax, [rbp + 64]		;intercept arg Grid.POutBuffer@64
	push rax				;push arg as qword
	mov rax, [rbp + 72]		;intercept arg Grid.OutBufferSize@62
	push ax					;push arg as word
	mov rax, [rbp + 56]		;intercept arg Grid.MapHeight@60
	push ax					;push arg as word
	mov rax, [rbp + 48]		;intercept arg Grid.MapWidth@58
	push ax					;push arg as word
	push r9w				;intercept arg Grid.TargetY@56
	push r8w				;intercept arg Grid.TargetX@54
	push dx					;intercept arg Grid.StartY@52
	push cx					;intercept arg Grid.StartX@50
	mov rax, [rbp + 80]		;intercept arg Grid.IncludeDiagonals@48
	cmp rax, 1				;if IncludeDiagonals == false
	jnz .ignore_diagonals	;jump to ignore digonals
	mov ax, 8				;else, include diagonals, mov ax, 8
	jmp .include_diagonals	;jump over ignore diagonals
	.ignore_diagonals:		
	mov ax, 4				;mov ax, 4 
	.include_diagonals:
	push word ax			;Grid.IncludeDiagonals@48
	push qword 1			;NodeOpenList.Count@40
	push qword 0			;NodeOpenList.Last@32
	push qword 0			;NodeOpenList.First@24
	push qword 0			;NodeStack.Count@16
	push qword 0			;NodeStack.Bottom@8
	push qword 0			;NodeStack.Top@0
	mov rbp, rsp			;save the stack ptr to the thread local storage
	
	;initialize values for node construction
	mov [rbp + NodeStack.Bottom], rsp   			;set bottom node to stack pointer
	sub qword [rbp + NodeStack.Bottom], Node.Size	;add size bottom node
	xor cx, cx										;clear resistance word, cx
	xor r8, r8				 	  					;clear row counter
	xor r9, r9				  						;clear col counter
	xor r10, r10 				  					;clear node counter
	mov r11, [rbp + Grid.PMap]			  			;ptr to map buffer
	mov r12, [rbp + Grid.MapWidth]					;store MapWidth into r12	
	mov r13, [rbp + Grid.MapHeight]					;store MapHieght into r13
	and r12, 0xFFFF									;clear the highest 12 bytes of r12
	and r13, 0xFFFF									;clear the highest 12 bytes of r13
	imul r12, r13									;multiply r12 with MapHeight
	;construct nodes on stack from PMap
	.alloc:									;entry point of stack alloction loop
		cmp r10, r12						;check for last node in map 
		jz .find_path						;if last node, terminate alloc loop
			cmp r9w, [rbp + Grid.MapWidth]	;check for last node in row
			jz .switch_row					;if last node in row, row switch
			;construct node
			push r8w						;Node.Position.Y: 	offset = 8*6+6	= 56
			push r9w						;Node.Position.X: 	offset = 8*6+4 	= 54
			mov cl, byte [r11+r10]			;store resistance as byte
			push cx 						;Node.Resistance: 	offset = 8*6+2 	= 52
			push word  0					;Node.Closed: 		offset = 8*6 	= 48
			push qword 0					;Node.GCost: 		offset = 8*5	= 40
			push qword 0					;Node.HCost: 		offset = 8*4	= 32
			push qword 0					;Node.FCost: 		offset = 8*3	= 24
			push qword r10					;Node.ID: 			offset = 8*2	= 16
			push qword -1					;Node.PParent: 		offset = 8*1	= 8
			push qword -1					;Node.PNext: 		offset = 8*0	= 0
			inc r10							;inc node counter
			inc r9							;inc row counter
			jmp .alloc						;continue alloc loop
			.switch_row:					;entry of row switch
				inc r8						;inc col counter
				xor r9, r9					;reset row counter
				jmp .alloc					;continue alloc loop
	
	.find_path:
		;save node counter
		mov qword [rbp + NodeStack.Count], r10
		;save top ptr
		mov qword [rbp + NodeStack.Top], rsp
		;store addr of target node in r15
		mov ax, [rbp + Grid.TargetX]			;store TargetX in ax
		mov bx, [rbp + Grid.TargetY]			;store TargetY in bx
		mov dx, [rbp + Grid.MapWidth]			;store MapWidth in dx
		and rax, 0xFFFF							;clear the highest 12 bytes of rax
		and rbx, 0xFFFF							;clear the highest 12 bytes of rbx
		and rdx, 0xFFFF							;clear the highest 12 bytes of rdx
		call _Node2D.GetByCoordinates			;call GetByCoord to get the target node
		cmp word [rcx + Node.Resistance], 0		;if target node is not traversable
		jz .no_path_found_1						;no path can be found
		mov r15, rcx							;else, store the target node in r15
		mov ax, [rbp + Grid.StartX]				;store StartX in ax
		mov bx, [rbp + Grid.StartY]				;store StartY in bx
		mov dx, [rbp + Grid.MapWidth]			;store MapWidth in dx
		call _Node2D.GetByCoordinates			;call GetByCoord to get the start node
		cmp word [rcx + Node.Resistance], 0		;if start node is not traversable
		jz .no_path_found_2						;no path can be found
		mov qword [rbp + Grid.PStartNode], rcx			;save a ptr to start node
		mov qword [rbp + NodeOpenList.First], rcx		;set first open to start node	
		;find path sequence
		.next_open:
			;ready current node, store
			mov r14, [rbp + NodeOpenList.First]			;set current node to first open
			;ready NodeOpenList.First node, pop
			mov word [r14 + Node.Closed], 1				;close current node
			mov r12, [r14 + Node.PNext]					;get current.next
			mov [rbp + NodeOpenList.First], r12			;set first open to current.next
			mov qword [r14 + Node.PNext], -1			;current - set PNext to null
			dec qword [rbp + NodeOpenList.Count]		;dec open list count
			;check adjecent nodes
			call _Node.CheckAdjecentNodes			;call proc
			cmp rcx, 5								;if target is found, return = 5
			jz .path_found							;jump to "path found" if it is
			cmp qword [rbp + NodeOpenList.Count], 0	;check if open list is empty
			jle .no_path_found_3					;if it is, no path found
			jmp .next_open							;check next open node
		
	;pathing done
	.path_found:
		mov rax, r15								;store target node in rax
		mov rbx, [rbp + Grid.POutBuffer]			;store ptr to outbuffer in rbx
		mov rsi, [rbp + Grid.PStartNode]			;store ptr to start node in rsi
		xor rcx, rcx								;ready rcx
		xor rdx, rdx								;ready rdx
		xor rdi, rdi								;ready rdi
		call _Node.Traceback						;call _Node.Traceback to store the final path in outbuffer
		mov rax, rcx								;store ptr to outbuffer in rax
		jmp .pf_done								;jump to pf_done
	.no_path_found:
		mov rax, -1			;ret val: start or target is out-of-bounds of map
		ret					;return
	.no_path_found_1:
		mov rax, -2			;ret val: target node is non-traversable
		jmp .pf_done		;jump to pf_done
	.no_path_found_2:
		mov rax, -3			;ret val: start node is non-traversable
		jmp .pf_done		;jump to pf_done
	.no_path_found_3:
		mov rax, -4			;ret val: open list is empty
		jmp .pf_done		;jump to pf_done
	.pf_done:
		mov r9, rbp			;save rbp in r9
		call _Node.Empty	;empty nodes
		ret					;return