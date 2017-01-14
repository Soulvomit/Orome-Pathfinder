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
;TEST
[EXTERN TestData.PMap]
[EXTERN TestData.POutBuffer]
[DEFAULT REL]

DllMain:
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
	;call FindPath
    mov eax, 1
    ret

FindPath:
	;failsafe: varify grid values
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
	;initialize "per execution" tls data
	mov rbp, rsp
	push qword 0			;Grid.PStartNode@80
	mov rax, [rbp + 40]		;Grid.PMap@72
	push rax				
	mov rax, [rbp + 64]		;Grid.POutBuffer@64
	push rax				
	mov rax, [rbp + 72]		;Grid.OutBufferSize62
	push ax					
	mov rax, [rbp + 56]		;Grid.MapHeight60
	push ax					
	mov rax, [rbp + 48]		;Grid.MapWidth58
	push ax					
	push r9w				;Grid.TargetY56
	push r8w				;Grid.TargetX54
	push dx					;Grid.StartY52
	push cx					;Grid.StartX50
	push word 0				;Grid.ShadowBytes48
	push qword 0			;NodeOpenList.Count@40
	push qword 0			;NodeOpenList.Last@32
	push qword 0			;NodeOpenList.First@24
	push qword 0			;NodeStack.Count@16
	push qword 0			;NodeStack.Bottom@8
	push qword 0			;NodeStack.Top@0
	mov rbp, rsp			;Save a ptr to the thread local storage
	;initialize values for node creation
	mov [rbp + NodeStack.Bottom], rsp   			;Set bottom node to stack pointer
	sub qword [rbp + NodeStack.Bottom], Node.Size	;Add size bottom node
	xor cx, cx										;Clean rcx
	xor r8, r8				 	  					;Row Counter
	xor r9, r9				  						;Col Counter
	xor r10, r10 				  					;Node Counter
	mov r11, [rbp + Grid.PMap]			  			;Pointer to map buffer
	mov r12, [rbp + Grid.MapWidth]					;Move MapWidth into r12	
	mov r13, [rbp + Grid.MapHeight]					;Move MapHieght into r13
	and r12, 0xFFFF									;convert word of r12 into qword
	and r13, 0xFFFF									;convert word of r13 into qword
	imul r12, r13									;Multiply r12 with MapHeight
	;create nodes on stack from grid
	.alloc:									;Entry of stack alloction loop
		cmp r10, r12						;Check for last node in map 
		jz .find_path						;If last node, terminate alloc loop
			cmp r9w, [rbp + Grid.MapWidth]	;Check for last node in row
			jz .switch_row					;If last node in row, row switch
			mov ax, r9w						;ARG: X
			mov bx, r8w						;ARG: Y
			mov cl, [r11+r10]				;ARG: Traversable
			mov dx, 1						;ARG: Resistance
			call _Node.Ctor					;Call Constructor
			inc r10							;Inc Node Counter
			inc r9							;Inc Row Counter
			jmp .alloc						;Continue alloc loop
			.switch_row:					;Entry of row switch
				inc r8						;Inc Column Counter
				xor r9, r9					;Reset Row Counter
				jmp .alloc					;Continue alloc loop
	
	.find_path:
		;store addr of target node in r15
		mov ax, [rbp + Grid.TargetX]
		mov bx, [rbp + Grid.TargetY]
		mov dx, [rbp + Grid.MapWidth]
		and rax, 0XFFFF
		and rbx, 0XFFFF
		and rdx, 0XFFFF
		call _Node2D.GetByCoordinates
		cmp word [rcx + Node.Traversable], 0
		jz .no_path_found_1
		mov r15, rcx
		;store addr of starting node as first and last on open list
		mov ax, [rbp + Grid.StartX]
		mov bx, [rbp + Grid.StartY]
		mov dx, [rbp + Grid.MapWidth]
		call _Node2D.GetByCoordinates
		cmp word [rcx + Node.Traversable], 0
		jz .no_path_found_2
		mov qword [rbp + Grid.PStartNode], rcx
		mov qword [rbp + NodeOpenList.First], rcx
		mov qword [rcx + Node.PNext], rcx
		mov qword [rcx + Node.HCost], 0x1FFFFFFF
		mov qword [rcx + Node.FCost], 0x1FFFFFFF
		inc qword [rbp + NodeOpenList.Count]			;Inc open list count		
		;find path sequence
		xor r12w, r12w
		.next_open:
			;ready current node, store
			mov r14, [rbp + NodeOpenList.First]			;Get new current node
			cmp qword [rbp + NodeOpenList.First], -1	;Check that current node has a valid link
			jz .no_path_found_3							;Jump to "no path" if it doesn't
			mov word [r14 + Node.Closed], 1				;Close current node
			;ready NodeOpenList.First node, pop
			mov r11, [r14 + Node.PNext]					;Get current.PNext
			mov [rbp + NodeOpenList.First], r11			;Set OpenList.First to current.PNext
			mov qword [r14 + Node.PNext], -1			;Current - set PNext to -1 
			;check if open list is empty
			cmp qword [rbp + NodeOpenList.Count], 0		;Cmp OpenList.Count = 0
			jz .no_path_found_4							;Jump to "no path" if it is
			dec qword [rbp + NodeOpenList.Count]		;Else dec open list count
			;ready adjecent check proc
			xor r11, r11								;Reset r11
			mov r13, Node.AdjecentOffsets				;Starting Adjecent Offset
			;update the current node adjecent nodes
			.next_adjecent:
				xor rax, rax							;Reset rax
				xor rbx, rbx							;Reset rbx
				mov ax, word [r13]						;ARG: OffsetX
				mov bx, word [r13 + 8]					;ARG: OffsetY
				call _Node.UpdateAdjecentNode			;Call UpdateAdjecentNode
				cmp rcx, 5								;Check if target is found
				jz .path_found							;Jump to "path found" if it is
				add r13, 16								;Add 16 to offset
				inc r11									;Inc Iteration Counter
				cmp r11, 8								;Check for last offset
			jnz .next_adjecent							;If last offset, terminate adjecent loop
			;check if we are above max path length
			inc r12w									;Inc Iteration Counter
			cmp r12w, word [rbp + Grid.OutBufferSize]	;Check if path is too long
			jge .no_path_found_5						;Jump to "no path" if it is
			jmp .next_open								;Else, check next open node
		.path_found:
			mov rax, r15
			mov rbx, [rbp + Grid.POutBuffer]
			xor rcx, rcx
			xor rdx, rdx
			xor rdi, rdi
			mov rsi, [rbp + Grid.PStartNode]
			call _Node.Traceback
			mov rax, rcx
			jmp .pf_done
		.no_path_found:
			mov rax, -1
			ret
		.no_path_found_1:
			mov rax, -2
			jmp .pf_done
		.no_path_found_2:
			mov rax, -3
			jmp .pf_done
		.no_path_found_3:
			mov rax, -4
			jmp .pf_done
		.no_path_found_4:
			mov rax, -5
			jmp .pf_done
		.no_path_found_5:
			mov rax, -6
			jmp .pf_done
		.pf_done:
			mov r9, rbp
			call _Node.Empty
			ret