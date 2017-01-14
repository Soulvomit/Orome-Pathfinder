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
[EXTERN Node.Size]
[EXTERN Node.PNext]
[EXTERN Node.AdjecentOffsets]
;From Data - NodeStack
[EXTERN NodeStack.Bottom]
[EXTERN NodeStack.Count]
;From Data - NodeOpenList
[EXTERN NodeOpenList.First]
[EXTERN NodeOpenList.Last]
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
[EXTERN Grid.OutBufferSize]
[EXTERN Grid.PMap]
[DEFAULT REL]

DllMain:
	;mov	ecx, 0						;nStartX@0
	;mov edx, 0						;nStartY@8
	;mov r8d, 31						;nTargetX@16
	;mov r9d, 31						;nTargetX@24
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

	;call FindPath
    mov eax, 1
    ret

FindPath:
	;varify grid values
	cmp ecx, [rsp + 48]
	jge .no_path_found
	cmp ecx, 0
	jl .no_path_found
	cmp edx, [rsp + 56]
	jge .no_path_found
	cmp edx, 0
	jl .no_path_found
	cmp r8d, [rsp + 48]
	jge .no_path_found
	cmp r8d, 0
	jl .no_path_found
	cmp r9d, [rsp + 56]
	jge .no_path_found
	cmp r9d, 0
	jl .no_path_found
	;initialize grid
	mov dword[Grid.StartX], ecx
	mov dword[Grid.StartY], edx
	mov dword[Grid.TargetX], r8d
	mov dword[Grid.TargetY], r9d
	mov rax, [rsp + 40]
	mov qword[Grid.PMap], rax
	mov rax, [rsp + 48]
	mov dword[Grid.MapWidth], eax
	mov rax, [rsp + 56]
	mov dword[Grid.MapHeight], eax
	mov rax, [rsp + 64]
	mov qword[Grid.POutBuffer], rax
	mov rax, [rsp + 72]
	mov dword[Grid.OutBufferSize], eax
	;initialize values for node creation
	mov [NodeStack.Bottom], rsp   				;Set bottom node to stack pointer
	sub qword [NodeStack.Bottom], Node.Size		;Add size bottom node
	xor rcx, rcx								;Clean rcx
	xor r8, r8				 	  				;Row Counter
	xor r9, r9				  					;Col Counter
	xor r10, r10 				  				;Node Counter
	mov r11, [Grid.PMap]			  			;Pointer to map buffer
	mov r12, [Grid.MapWidth]
	imul r12, [Grid.MapHeight]
	;create nodes on stack from grid
	.alloc:								;Entry of stack alloction loop
		cmp r10, r12					;Check for last node in map 
		jz .find_path					;If last node, terminate alloc loop
			cmp r9, [Grid.MapWidth] 	;Check for last node in row
			jz .switch_row				;If last node in row, row switch
			mov rax, r9				;ARG: X
			mov rbx, r8				;ARG: Y
			mov cl, [r11+r10]		;ARG: Traversable
			mov rdx, 1				;ARG: Resistance
			call _Node.Ctor			;Call Constructor
			inc r10					;Inc Node Counter
			inc r9					;Inc Row Counter
			jmp .alloc				;Continue alloc loop
			.switch_row:				;Entry of row switch
				inc r8					;Inc Column Counter
				xor r9, r9				;Reset Row Counter
				jmp .alloc				;Continue alloc loop
	
	.find_path:
		;store addr of target node in r15
		mov rax, [Grid.TargetX]
		mov rbx, [Grid.TargetY]
		mov rdx, [Grid.MapWidth]
		call _Node2D.GetByCoordinates
		mov r15, rcx
		;store addr of starting node as first and last on open list
		mov rax, [Grid.StartX]
		mov rbx, [Grid.StartY]
		mov rdx, [Grid.MapWidth]
		call _Node2D.GetByCoordinates
		mov qword [Grid.PStartNode], rcx
		mov qword [NodeOpenList.First], rcx
		mov qword [NodeOpenList.Last], rcx
		;inc open list count
		inc qword [NodeOpenList.Count]			
		;find path sequence
		xor r12, r12
		.next_open:
			mov r14, [NodeOpenList.First]		;Get current node
			xor r11, r11						;Reset r11
			mov r13, Node.AdjecentOffsets		;Starting Adjecent Offset
			;update the current node adjecent nodes
			.next_adjecent:
				mov rax, [r13]					;ARG: OffsetX
				mov rbx, [r13 + 8]				;ARG: OffsetY
				mov rdi, r14					;ARG: CurrentNode
				mov rsi, r15					;ARG: TargetNode
				call _Node.UpdateAdjecentNode	;Call UpdateAdjecentNode
				cmp rcx, 5						;Check if target is found
				jz .path_found					;Jump to "path found" if it is
				add r13, 16						;Add 16 to offset
				inc r11							;Inc Iteration Counter
				cmp r11, 8						;Check for last offset
			jnz .next_adjecent					;If last offset, terminate adjecent loop
			;update the current node
			mov r11, [r14 + Node.PNext]			;Get next node in open list
			mov qword [r14 + Node.PNext], -1	;Remove current node from open list
			mov [NodeOpenList.First], r11		;Set next node as first in open list
			dec qword [NodeOpenList.Count]		;Dec open list count
			mov qword [r14 + Node.Closed], 0	;Close current node
			;check for failure
			inc r12								;Inc Iteration Counter
			cmp qword [NodeOpenList.Count], 0	;Check if open list is empty
			jz .no_path_found					;Jump to "no path" if it is
			cmp r12, [Grid.OutBufferSize]		;Check if path is too long
			jge .no_path_found					;Jump to "no path" if it is
			jmp .next_open						;Else, check next open node
		.path_found:
			mov rax, r15
			mov rbx, [Grid.POutBuffer]
			xor rcx, rcx
			xor rdx, rdx
			xor rdi, rdi
			mov rsi, [Grid.PStartNode]
			call _Node.Traceback
			mov rax, rcx
			call _Node.Empty
			ret
		.no_path_found:
			mov rax, -1
			call _Node.Empty
			ret
			