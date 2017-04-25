;Author:	Jonas Brown
;Date:		27/12-2016
;File: 		Node.asm

[BITS 64]
[SECTION .text]
[GLOBAL _Node.Ctor]
[GLOBAL _Node.Traceback]
[GLOBAL _Node.CheckAdjecentNodes]
[GLOBAL _Node.Empty]
;From _Node2D:
[EXTERN _Node2D.CalcManhattanDistance]
[EXTERN _Node2D.GetByCoordinates]
;From Data - Node
[EXTERN Node.Position.Y]
[EXTERN Node.Position.X]
[EXTERN Node.Resistance]
[EXTERN Node.Closed]
[EXTERN Node.GCost]
[EXTERN Node.HCost]
[EXTERN Node.FCost]
[EXTERN Node.ID]
[EXTERN Node.PParent]
[EXTERN Node.PNext]
[EXTERN Node.Size]
;From Data - NodeStack
[EXTERN NodeStack.Bottom]
[EXTERN NodeStack.Count]
;From Data - NodeOpenList
[EXTERN NodeOpenList.First]
[EXTERN NodeOpenList.Count]
;From Data - AdjecentArray
[EXTERN AdjecentArray.Count]
[EXTERN AdjecentArray.Offsets]
;From Data - Grid
[EXTERN Grid.MapWidth]
[EXTERN Grid.MapHeight]
[EXTERN Grid.OutBufferSize]
[EXTERN Grid.Size]
[DEFAULT REL]
 
_Node:		
	;IN: r13 = AdjecentOffsets, r14 = CurrentNode, r15 = TargetNode
	;OUT: rcx = 0 = out-of-bounds, 1 = closed or non-traversable, 2 = updated, 
	;			3 = sent to update but no update, 4 = initialized, 5 = target node found 
	.CheckAdjecentNodes:
		;ready adjecent check proc
		xor r11, r11								;clear r11
		mov r13, AdjecentArray.Offsets				;store pointer to adjecent offsets array
		;check the current node's adjecent nodes
		.next_adjecent:
			;get next adjecent
			xor rax, rax							;clear rax
			xor rbx, rbx							;clear rbx
			xor rdx, rdx							;clear rdx
			mov ax, word [r13]						;offset x
			mov bx, word [r13 + 2]					;offset y
			;x,y position for adjecent node
			add ax, word [r14 + Node.Position.X]	;arg 1 GetByCoordinates: add offset x to current node position
			add bx, word [r14 + Node.Position.Y]	;arg 2 GetByCoordinates: add offset y to current node position
			mov dx, [rbp + Grid.MapWidth]			;arg 3 GetByCoordinates: map width
			;if, adjecent node is out-of-bounds
			cmp ax, dx								;compare x to map width
			jge .out_of_bounds						;if x above map width, out-of-bounds, end check
			cmp ax, 0								;compare x to 0
			jl .out_of_bounds						;if x below 0, out-of-bounds, end check
			cmp bx, word [rbp + Grid.MapHeight]		;compare y to map height
			jge .out_of_bounds						;if y above map height, out-of-bounds, end check
			cmp bx, 0								;compare y to 0								
			jl .out_of_bounds						;if y below zero, out-of-bounds, end check
			;else, get current node adjecent
			call _Node2D.GetByCoordinates			;call GetByCoordinates
			;if it is closed and is non-traversable 
			cmp word [rcx + Node.Closed], 0			;compare adjecent.closed to 0
			jnz .closed_nontraversable				;if true, closed, end check
			cmp word [rcx + Node.Resistance], 0		;compare adjecent.resistance to 0
			jz .closed_nontraversable				;if true, nontraversable, end check
			;check if node should be updated or initialized
			cmp qword [rcx + Node.PParent], -1		;compare adjecent.parent to null
			jz .initialize							;if true, initialize adjecent
			jnz .try_update							;else if false, try to update adjecent
			.out_of_bounds:
				mov rcx, 0							;set rcx, 0
				jmp .check_done						;check done
			.closed_nontraversable:
				mov rcx, 1							;set rcx, 1
				jmp .check_done						;check done
			.try_update:
				mov rax, rcx						;arg 1 fUpdate: adjecent node pointer
				call private.fUpdate				;call fUpdate
				cmp rcx, 0							;compare ruturn value to 0
				jz .update_failed					;if true, update failed
				;jnz .update_succeded				;else if false, update succeded
				;.update_succeded:
					mov rcx, 2						;set rcx, 2
					jmp .check_done					;adjecent check done
				.update_failed:
					mov rcx, 3						;set rcx, 3
					jmp .check_done					;adjecent check done
			.initialize:
				mov rax, rcx						;arg 1 fInitialize: adjecent node pointer
				call private.fInitialize			;call fInitialize
				cmp rcx, 1
				jz .target_found					;if true, target found
				;jnz .initialized					;else if false, update succeded
				;.initialized:
					mov rcx, 4						;set rcx, 4
					jmp .check_done					;adjecent check done
				.target_found:
					mov rcx, 5						;set return value, 5
					ret								;terminate loop and return
			.check_done:
				add r13, 4								;inc position in adjecent offsets array with word*2
				inc r11									;inc iteration counter
				cmp r11w, [rbp + AdjecentArray.Count]	;check for last offset
				jnz .next_adjecent						;if not last offset, continue loop through adjecent nodes
				ret										;else, terminate loop and return
	
	;IN: rax = TargetNode, rbx = POutBuffer, rdx = DWord Index,  rsi = StartNode, rdi = Pop Counter
	;OUT: rcx = path length
	.Traceback:
		;store node id on stack
		push qword [rax + Node.ID]				;push node id to stack
		inc rcx									;inc path length
		cmp cx, word [rbp + Grid.OutBufferSize]	;if path length = buffer size
		jz .fill_next							;fill dword outbuffer with path IDs
		cmp qword [rax + Node.PParent], rsi		;if start node = parent
		jz .fill_next							;fill dword outbuffer with path IDs
		;else, recursively traceback through parents
		mov rax, [rax + Node.PParent]			;else, store parent in rax 
		jmp .Traceback							;continue traceback
		.fill_next:
			;pop the node id into outbuffer
			pop r8					;pop next in path
			mov [rbx + rdx], r8		;store next in path in dword outbuffer
			add rdx, 4				;add size of dword to rdx
			inc rdi					;inc rdi = counter
			cmp rdi, rcx			;if counter = path length
			jz .fill_done			;job done!
				jmp .fill_next		;else, continue to fill outbuffer
			.fill_done:
				ret					;return

	;Uses rsi,rdi and rbp to access data segment. 
	;Empties the node stack. NOTE: Must be called in the same "scope" as node construction
	.Empty:
		pop rbp
		call private.fStackDeallocAll
		push rbp
		ret	
		
	;PRIVATE SUBROUTINES
	private:				
		;IN: rax = AdjecentNode, r15 = TargetNode, r14 = CurrentNode.
		;OUT: rcx = 1 if rax is TargetNode, else 0.
		.fInitialize:
			mov [rax + Node.PParent], r14			;set current as adjecents parent
			cmp rax, r15							;compare target to adjecent
			jz .target_found						;if true, target found
			;jnz .initialize						;else, target not found, initialize node
			;.initialize:							
				mov rbx, [r14 + Node.GCost]				;get parent g-cost
				add bx, word [rax + Node.Resistance]	;add resistance and g-cost 
				mov [rax + Node.GCost], rbx				;set adjecent g-cost to g-cost + resistance
				call _Node2D.CalcManhattanDistance		;calc manhatten distance to target, preserves rbx
				mov [rax + Node.HCost], rcx				;set return value as adjecent h-cost
				add rbx, rcx							;add h-cost to resistance and g-cost 
				mov [rax + Node.FCost], rbx				;store added values as adjecent f-cost
				call .fOpen								;open adjecent
				mov rcx, 0								;set ret val
				ret										;return
			.target_found:
				mov rcx, 1								;set ret val
				ret										;return
						
		;IN: rax = AdjecentNode, r14 = CurrentNode.
		;OUT: rcx = 1 if node was updated, else 0.
		.fUpdate:
			;compute new g cost
			mov r8, [r14 + Node.GCost]				;set new g-cost to current g-cost
			add r8w, word [rax + Node.Resistance]	;add adjecent resistance to to new g-cost
			mov r9, r8								;set new f-cost to new g-cost 
			add r9, [rax + Node.HCost]				;add adjecent h-cost to new f-cost
			cmp r9, [rax + Node.FCost]				;compare new f-cost	to adjecent f-cost
			jg .no_update							;if, new f-cost is larger then current f cost, no update
			jl .update								;else if, new f-costs are less, update 
			;je .f_equal							;else, f-costs are equal
			;.f_equal:								
				cmp r8, [rax + Node.GCost]			;compare new g-cost	to old g-cost
				jge .no_update						;if new g-cost is greather or equal, no update
				;jl .update							;else, update
			.update:
				mov [rax + Node.PParent], r14 		;update adjecent parent to current
				mov [rax + Node.GCost], r8			;update adjecent g-cost to new g-cost
				mov [rax + Node.FCost], r9			;update adjecent f-cost to new f-cost
				mov rcx, 1							;update ret val
				ret									;return
			.no_update:						
				mov rcx, 0							;set ret val
				ret									;return
		
		;IN: rax = AdjecentNode.
		;OUT: rcx = 0 if new node or new top node, 1 if new bottom node.
		.fOpen:
			cmp qword [rbp + NodeOpenList.Count], 0	;check if open list is empty
			jle .push_empty							;if it is, push empty
			mov r9, [rbp + NodeOpenList.First]		;save first in open list as next						
			mov rbx, [rax + Node.FCost]				;save adjecents f-cost
			cmp rbx, [r9 + Node.FCost]				;compare adjecent f-cost to next f-cost
			jl .push_front							;if, adjecent f-cost less, front push
			;jge .insert_stoted						;else if, adjecent f-cost greater or equal, insert sorted
			;.insert_stoted:
				call .fSortedInsert					;call insert sorted
				jmp .open_done						;and end proc
			.push_empty:							
				mov [rbp + NodeOpenList.First], rax	;set adjecent as first
				mov rcx, 0							;set return val
				jmp .open_done						;and end proc
			.push_front:
				mov [rbp + NodeOpenList.First], rax	;set adjecent as first
				mov [rax + Node.PNext], r9			;link next to adjecent		
				mov rcx, 1							;set return val
				;jmp .open_done						;and end proc
			.open_done:
				inc qword [rbp + NodeOpenList.Count];increase open list count	
				ret									;return
			
		;IN: rax = AdjecentNode.
		;OUT: rcx = 3 if node was allocated based on f-cost, rcx = 4 if node was allocated based on h-cost.
		.fSortedInsert:
			;mov r9, [rbp + NodeOpenList.First]	;save first in open list as next
			;mov rbx, [rax + Node.FCost]		;save adjecents f-cost
			mov rdx, [rax + Node.HCost]			;save adjecents h-cost
			.next_open:
				mov r8, r9						;set current as next 
				mov r9, [r8 + Node.PNext]		;set next as current.next 
				cmp qword r9, -1				;compare next node to null
				jz .push_back					;if null, next is last 
				cmp rbx, [r9 + Node.FCost]		;compare adjecent f-cost to current f-cost
				jg .next_open					;if adjecent f-cost is more expensive, get next open
				jl .insert_f					;if adjecent f-cost is cheaper, insert
				;je .equal_f					;else, f-cost equal 
				;.equal_f:
					cmp rdx, [r9 + Node.HCost]	;compare adjecent h-cost to current h-cost
					jg .next_open				;if adjecent h-cost is more expensive, get next open
					jle .insert_hf				;if adjecent h-cost is cheaper AND f-costs are equal, insert
				.push_back:
					mov [r8 + Node.PNext], rax	;link adjecent to current
					mov rcx, 2					;set return val
					ret							;return
				.insert_f:
					mov rcx, 3					;set return val
					jmp .insert					;insert
				.insert_hf:
					mov rcx, 4 					;set return val
					;jmp .insert				;insert
				.insert:
					mov [r8 + Node.PNext], rax	;link adjecent to current 
					mov [rax + Node.PNext], r9	;link next to adjecent
					ret							;return
			
		;deallocates all nodes
		.fStackDeallocAll:
			pop rdi
			;remove all nodes
			mov rsi, Node.Size
			imul rsi, [r9 + NodeStack.Count]
			add rsp, rsi
			add rsp, Grid.Size
			;null node counter
			mov qword [r9 + NodeStack.Count], 0
			push rdi
			ret
