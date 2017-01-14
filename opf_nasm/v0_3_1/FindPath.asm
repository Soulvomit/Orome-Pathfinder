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
[EXTERN _Node.Ctor]
[EXTERN _Node.UpdateAdjecentNode]
[EXTERN _Node.Empty]
[EXTERN _Node.Traceback]
;From _Node2D:
[EXTERN _Node2D.GetByCoordinates]
;From Data - Node
[EXTERN Node.Closed]
[EXTERN Node.Traversable]
[EXTERN Node.Size]
[EXTERN Node.PNext]
[EXTERN Node.HCost]
[EXTERN Node.FCost]
[EXTERN Node.AdjecentOffsets]
;From Data - NodeStack
[EXTERN NodeStack.Bottom]
;From Data - NodeOpenList
[EXTERN NodeOpenList.First]
[EXTERN NodeOpenList.Last]
[EXTERN NodeOpenList.Count]
;From Data - Grid
[EXTERN Grid.IncludeDiagonals]
[EXTERN Grid.TargetX]
[EXTERN Grid.TargetY]
[EXTERN Grid.StartX]
[EXTERN Grid.StartY]
[EXTERN Grid.PStartNode]
[EXTERN Grid.MapWidth]
[EXTERN Grid.MapHeight]
[EXTERN Grid.POutBuffer]
[EXTERN Grid.PMap]
;TEST
;[EXTERN TestData.PMap]
;[EXTERN TestData.POutBuffer]
[DEFAULT REL]

DllMain:
	;FOR TESTING: Simulates fastcall64
	;mov ecx, 0						;nStartX@0
	;mov edx, 0						;nStartY@8
	;mov r8d, 31					;nTargetX@16
	;mov r9d, 31					;nTargetX@24
	;mov rax, TestData.PMap			;pMap@32
	;mov [rsp + 32], rax	
	;mov eax, 32 					;nMapWidth@40
	;mov [rsp + 40], eax			
	;mov eax, 32  					;nMapHeight@48
	;mov [rsp + 48], eax			
	;mov rax, TestData.POutBuffer	;pOutBuffer@56
	;mov [rsp + 56], rax
	;mov eax, 1024					;nOutBufferSize@64
	;mov [rsp + 64], eax			
	;mov eax, 1						;nIncludeDiagonals@72
	;mov [rsp + 72], eax		
	;call FindPath
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
	;check if target x coord is out-of-bounds
	cmp r9d, [rsp + 56]
	jge .no_path_found
	cmp r9d, 0
	jl .no_path_found
	;initialize "per execution" tls data
	mov rbp, rsp			;save the stack ptr
	push qword 0			;Grid.PStartNode@80
	mov rax, [rbp + 40]		;Grid.PMap@72
	push rax				
	mov rax, [rbp + 64]		;Grid.POutBuffer@64
	push rax				
	mov rax, [rbp + 72]		;Grid.OutBufferSize@62
	push ax					
	mov rax, [rbp + 56]		;Grid.MapHeight@60
	push ax					
	mov rax, [rbp + 48]		;Grid.MapWidth@58
	push ax					
	push r9w				;Grid.TargetY@56
	push r8w				;Grid.TargetX@54
	push dx					;Grid.StartY@52
	push cx					;Grid.StartX@50
	mov rax, [rbp + 80]		;Grid.IncludeDiagonals@48
	cmp rax, 1
	jz .includediagonals
		mov ax, 4
		jmp .ignorediagonals
	.includediagonals:
		mov ax, 8
	.ignorediagonals:
	push word ax
	push qword 0			;NodeOpenList.Count@40
	push qword 0			;NodeOpenList.Last@32
	push qword 0			;NodeOpenList.First@24
	push qword 0			;NodeStack.Count@16
	push qword 0			;NodeStack.Bottom@8
	push qword 0			;NodeStack.Top@0
	mov rbp, rsp			;save the stack ptr to the thread local storage
	;initialize values for node creation
	mov [rbp + NodeStack.Bottom], rsp   			;set bottom node to stack pointer
	sub qword [rbp + NodeStack.Bottom], Node.Size	;add size bottom node
	xor cx, cx										;clean rcx
	xor r8, r8				 	  					;row counter
	xor r9, r9				  						;col counter
	xor r10, r10 				  					;node counter
	mov r11, [rbp + Grid.PMap]			  			;ptr to map buffer
	mov r12, [rbp + Grid.MapWidth]					;move MapWidth into r12	
	mov r13, [rbp + Grid.MapHeight]					;move MapHieght into r13
	and r12, 0xFFFF									;convert word of r12 into qword
	and r13, 0xFFFF									;convert word of r13 into qword
	imul r12, r13									;multiply r12 with MapHeight
	;create nodes on stack from grid
	.alloc:									;entry of stack alloction loop
		cmp r10, r12						;check for last node in map 
		jz .find_path						;if last node, terminate alloc loop
			cmp r9w, [rbp + Grid.MapWidth]	;check for last node in row
			jz .switch_row					;if last node in row, row switch
			mov ax, r9w						;ARG: X
			mov bx, r8w						;ARG: Y
			mov cl, [r11+r10]				;ARG: Traversable
			mov dx, 1						;ARG: Resistance
			call _Node.Ctor					;call constructor
			inc r10							;inc node counter
			inc r9							;inc row counter
			jmp .alloc						;continue alloc loop
			.switch_row:					;entry of row switch
				inc r8						;inc col counter
				xor r9, r9					;reset row counter
				jmp .alloc					;continue alloc loop
	
	.find_path:
		;store addr of target node in r15
		mov ax, [rbp + Grid.TargetX]			;store TargetX in ax
		mov bx, [rbp + Grid.TargetY]			;store TargetY in bx
		mov dx, [rbp + Grid.MapWidth]			;store MapWidth in dx
		and rax, 0xFFFF							;clear the high bits of rax
		and rbx, 0xFFFF							;clear the high bits of rbx
		and rdx, 0xFFFF							;clear the high bits of rdx
		call _Node2D.GetByCoordinates			;call GetByCoord to get the target node
		cmp word [rcx + Node.Traversable], 0	;if target node is not traversable
		jz .no_path_found_1						;no path can be found
		mov r15, rcx							;else, store the target node in r15
		;store addr of starting node as first and last on open list
		mov ax, [rbp + Grid.StartX]				;store StartX in ax
		mov bx, [rbp + Grid.StartY]				;store StartY in bx
		mov dx, [rbp + Grid.MapWidth]			;store MapWidth in dx
		;no need to clear high bits of regs, since they are still cleared
		call _Node2D.GetByCoordinates			;call GetByCoord to get the start node
		cmp word [rcx + Node.Traversable], 0	;if start node is not traversable
		jz .no_path_found_2						;no path can be found
		mov qword [rbp + Grid.PStartNode], rcx			;save a ptr to start node
		mov qword [rbp + NodeOpenList.First], rcx		;add start node as the first in open list
		;mov qword [rcx + Node.PNext], rcx				;add start node as its own PNext: SHOULD WE DO THIS?
		mov qword [rcx + Node.HCost], 0x1FFFFFFF		;add dummy value as HCost
		mov qword [rcx + Node.FCost], 0x1FFFFFFF		;add dummy value as FCost
		inc qword [rbp + NodeOpenList.Count]			;inc open list count		
		;find path sequence
		;xor r12w, r12w									;ready r12w
		;xor rdi, rdi									;ready failsafe counter
		.next_open:
			;ready current node, store
			mov r14, [rbp + NodeOpenList.First]			;get new current node
			;fail safe check, might not be necessary
			cmp qword [rbp + NodeOpenList.First], -1	;check that current node has a valid link
			jz .no_path_found_3							;jump to "no path" if it doesn't
			mov word [r14 + Node.Closed], 1				;close current node
			;ready NodeOpenList.First node, pop
			mov r11, [r14 + Node.PNext]					;get current.PNext
			mov [rbp + NodeOpenList.First], r11			;set OpenList.First to current.PNext
			mov qword [r14 + Node.PNext], -1			;current - set PNext to -1 
			;check if open list is empty
			cmp qword [rbp + NodeOpenList.Count], 0		;if open list count = 0
			jz .no_path_found_4							;jump to "no path"
			dec qword [rbp + NodeOpenList.Count]		;else, dec open list count
			;ready adjecent check proc
			xor r11, r11								;reset r11
			mov r13, Node.AdjecentOffsets				;starting adjecent offset
			;update the current node adjecent nodes
			.next_adjecent:
				xor rax, rax							;reset rax
				xor rbx, rbx							;reset rbx
				mov ax, word [r13]						;ARG: OffsetX
				mov bx, word [r13 + 8]					;ARG: OffsetY
				call _Node.UpdateAdjecentNode			;call UpdateAdjecentNode
				cmp rcx, 5								;check if target is found
				jz .path_found							;jump to "path found" if it is
				add r13, 16								;add 16 to offset
				inc r11									;inc iteration counter
				cmp r11w, [rbp + Grid.IncludeDiagonals]	;check for last offset
				jnz .next_adjecent						;if last offset, terminate adjecent loop
			;iteration failsafe
			;inc rdi									;inc iteration counter
			;cmp rdi, 3000000							;if counter is above failsafe 
			;jge .no_path_found_5						;jump to "no path" if failsafe is hit
			jmp .next_open								;else, check next open node
		.path_found:
			mov rax, r15								;store target node in rax
			mov rbx, [rbp + Grid.POutBuffer]			;store ptr to outbuffer in rbx
			xor rcx, rcx								;ready rcx
			xor rdx, rdx								;ready rdx
			xor rdi, rdi								;ready rdi
			mov rsi, [rbp + Grid.PStartNode]			;store ptr to start node in rsi
			call _Node.Traceback						;call _Node.Traceback to store the final path in outbuffer
			mov rax, rcx								;store ptr to outbuffer in rax
			jmp .pf_done								;jump to pf_done
		.no_path_found:
			mov rax, -1			;start or target is out-of-bounds of map
			ret					;return
		.no_path_found_1:
			mov rax, -2			;target node is non-traversable
			jmp .pf_done		;jump to pf_done
		.no_path_found_2:
			mov rax, -3			;start node is non-traversable
			jmp .pf_done		;jump to pf_done
		.no_path_found_3:
			mov rax, -4			;PNext is -1, failsafe
			jmp .pf_done		;jump to pf_done
		.no_path_found_4:
			mov rax, -5			;open list is empty
			jmp .pf_done		;jump to pf_done
		.no_path_found_5:
			mov rax, -6			;path is too long
			jmp .pf_done		;jump to pf_done
		.pf_done:
			mov r9, rbp			;save rbp in r9
			call _Node.Empty	;empty nodes
			ret					;return