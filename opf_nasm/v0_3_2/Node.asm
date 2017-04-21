;Author:	Jonas Brown
;Date:		27/12-2016
;File: 		Node.asm

[BITS 64]
[SECTION .text]
[GLOBAL _Node.Ctor]
[GLOBAL _Node.Traceback]
[GLOBAL _Node.UpdateAdjecentNode]
[GLOBAL _Node.Empty]
;From _Node2D:
[EXTERN _Node2D.CalcManhattanDistance]
[EXTERN _Node2D.GetByCoordinates]
;From Data - Node
[EXTERN Node.Position.Y]
[EXTERN Node.Position.X]
[EXTERN Node.Resistance]
[EXTERN Node.Traversable]
[EXTERN Node.Closed]
[EXTERN Node.GCost]
[EXTERN Node.HCost]
[EXTERN Node.FCost]
[EXTERN Node.ID]
[EXTERN Node.PParent]
[EXTERN Node.PNext]
[EXTERN Node.Size]
[EXTERN Node.BaseCost]
;From Data - NodeStack
[EXTERN NodeStack.Top]
[EXTERN NodeStack.Bottom]
[EXTERN NodeStack.Count]
;From Data - NodeOpenList
[EXTERN NodeOpenList.First]
[EXTERN NodeOpenList.Last]
[EXTERN NodeOpenList.Count]
;From Data - Grid
[EXTERN Grid.MapWidth]
[EXTERN Grid.MapHeight]
[EXTERN Grid.OutBufferSize]
[DEFAULT REL]
 
_Node:
	;IN: ax = Position.X, bx = Position.Y, cx = Traversable, dx = Resistance.					 
	.Ctor:
		;caller addr
		pop rdi
		;NodeStack.Top + (Node.Size*Node.ID) + offset
		;push word 0						;Shadow bytes
		;push word 0						;Shadow bytes
		;push word 0						;Shadow bytes
		push bx								;Node.Position.Y: 	offset = 8*7	= 56
		push ax								;Node.Position.X: 	offset = 8*6+6 	= 54
		push dx 							;Node.Resistance: 	offset = 8*6+4 	= 52
		push cx								;Node.Traversable: 	offset = 8*6+2 	= 50
		push word  0						;Node.Closed: 		offset = 8*6 	= 48
		push qword 0						;Node.GCost: 		offset = 8*5	= 40
		push qword 0						;Node.HCost: 		offset = 8*4	= 32
		push qword 0						;Node.FCost: 		offset = 8*3	= 24
		push qword [rbp + NodeStack.Count]	;Node.ID: 			offset = 8*2	= 16
		push 0xFFFFFFFFFFFFFFFF				;Node.PParent: 		offset = 8*1	= 8
		push 0xFFFFFFFFFFFFFFFF				;Node.PNext: 		offset = 8*0	= 0
		;inc node counter
		inc qword [rbp + NodeStack.Count]
		;save top ptr
		mov qword [rbp + NodeStack.Top], rsp
		;return to caller
		push rdi
		ret
		
	;IN: ax = OffsetX, bx = OffsetY
	;OUT: rcx = 0 if out-of-bounds, 1 if closed or non-traversable, 2 if updated, 
	;			3 if sent to update, but not updated, 4 if initialized, 5 if target node 
	.UpdateAdjecentNode:
		;x,y position for adjecent node
		add ax, word [r14 + Node.Position.X]
		add bx, word [r14 + Node.Position.Y]
		;if adjecent node is out-of-bounds
		cmp ax, word [rbp + Grid.MapWidth]
		jge .oob
		cmp ax, 0
		jl .oob
		cmp bx, word [rbp + Grid.MapHeight]
		jge .oob
		cmp bx, 0
		jl .oob
		;reference node adjecent to current
		xor rdx, rdx 
		mov dx, [rbp + Grid.MapWidth]
		call _Node2D.GetByCoordinates
		;if it is closed and is non-traversable 
		cmp word [rcx + Node.Closed], 0
		jnz .closed_nontraversable
		cmp word [rcx + Node.Traversable], 0
		jz .closed_nontraversable
		;check if node should be updated or initialized
		cmp qword [rcx + Node.PParent], -1
		jz .i_initialized
		jnz .u_updated
		.oob:
			mov rcx, 0
			ret
		.closed_nontraversable:
			mov rcx, 1
			ret
		.u_updated:
			mov rax, rcx
			mov rdx, r14
			call private.fUpdate
			cmp rcx, 0
			jz .u_not_updated
			mov rcx, 2
			ret
		.u_not_updated:
			mov rcx, 3
			ret
		.i_initialized:
			mov rax, rcx
			mov rbx, r15
			mov rdx, r14
			call private.fInitialize
			cmp rcx, 1
			jz .i_targetfound
			mov rcx, 4
			ret
		.i_targetfound:
			mov rcx, 5
			ret
				
	;IN: rax = TargetNode, rbx = POutBuffer, rdx = DWord Index,  rsi = Starting Node, rdi = Pop Counter
	;OUT: rcx = Path Length
	.Traceback:
		;store node id on stack
		mov r8, [rax + Node.ID]					;get node id
		push r8									;push node id to stack
		inc rcx									;inc path length
		cmp cx, word [rbp + Grid.OutBufferSize]	;if path length = buffer size
		jz .fill_outbuffer						;fill out buffer with path ids
		cmp qword [rax + Node.PParent], rsi		;if start node = parent
		jz .fill_outbuffer						;fill out buffer with path ids
			;else, recursively traceback through parents
			mov rax, [rax + Node.PParent]		;else, store parent in rax 
			jmp .Traceback						;continue traceback
		.fill_outbuffer:
			;pop the node id into outbuffer
			pop r8					;pop r8 = next in path
			mov [rbx + rdx], r8		;store next node in path in outbuffer
			add rdx, 4				;add size of dword to rdx
			inc rdi					;inc rdi = counter
			cmp rdi, rcx			;if counter = path length
			jz .done				;job done!
			jmp .fill_outbuffer		;else, continue to fill outbuffer
		.done:
			ret						;return

	;IN: rax = Node.ID
	;OUT: rcx = Node Pointer
	.GetByID:
		imul r8, rax, Node.Size
		mov rcx, [rbp + NodeStack.Bottom]
		sub rcx, r8
		ret

	;Uses rsi,rdi and rbp to access data segment. 
	;Empties the node stack. NOTE: Must be called in the same "scope" as _Node.Ctor
	.Empty:
		pop rbp
		;call sequence
		call private.fStackDeallocAll
		;call private.fSaveTopAfterRet
		push rbp
		ret	
		
	;PRIVATE SUBROUTINES
	private:
		;IN: rax = AdjecentNode, rbx = TargetNode, rdx = CurrentNode.
		;OUT: rcx = 1 if rax is TargetNode, else 0.
		.fInitialize:
			;set current node as adjecent nodes parent
			mov [rax + Node.PParent], rdx
			;if this node is target node return 1, else initialize node
			cmp rax, rbx
			jz .target_found
				;store parents g cost as adjecent g cost
				mov r8, [rdx + Node.GCost]				;get parent g cost from pointer
				mov qword [rax + Node.GCost], r8		;store parent g cost, in adjecent g cost
				;add the multiplication of basecost and resistance to adjecent g cost
				mov r9, [rax + Node.Resistance]			;get resistance multi
				and r9, 0xFFFF							;convert word of r9 into qword
				imul r9, [Node.BaseCost]				;multiply basecost with resistance
				add qword [rax + Node.GCost], r9		;add multiplication result to adjecent basecost
				;calc manhatten distance to target
				call _Node2D.CalcManhattanDistance
				;init h,f costs
				mov qword [rax + Node.HCost], rcx
				mov r8, [rax + Node.GCost]
				add r8, rcx
				mov qword [rax + Node.FCost], r8
				call private.fOpen
				mov rcx, 0
				ret	
			.target_found:
				mov rcx, 1
				ret
				
		;IN: rax = AdjecentNode, rdx = CurrentNode.
		;OUT: rcx = 1 if node was updated, else 0.
		.fUpdate:
			;compute new g cost
			mov r8, [rdx + Node.GCost]
			mov r9, r8
			mov r10, [rax + Node.Resistance]
			and r10, 0xFFFF
			imul r10, [Node.BaseCost]
			add r8, r10
			add r8, [rax + Node.HCost]
			;if updated f cost is larger then current f cost, don't update
			cmp r8, [rax + Node.FCost]
			jg .no_update
			je .tie_breaker
			;else update all costs and set new parent; return true
			.do_update:
				;set current node as adjecent nodes parent
				mov [rax + Node.PParent], rdx
				mov [rax + Node.GCost], r9
				mov [rax + Node.FCost], r8
				mov rcx, 1
				ret
			.tie_breaker:
				;if f-costs are equal and path is shorter, do update
				cmp r9, [rax + Node.GCost]
				jl .do_update
			.no_update:
				mov rcx, 0
				ret
		
		;IN: rax = AdjecentNode.
		;OUT: rcx = 0 if new node or new top node, 1 if new bottom node.
		.fOpen:
			mov r8, [rbp + NodeOpenList.First]
			cmp qword r8, -1
			jz .first
			mov r10, [r8 + Node.FCost]
			cmp r10, [rax + Node.FCost]
			jg .new_first
			call private.fSortedInsert
			jmp .open_done
			.first:
				mov [rbp + NodeOpenList.First], rax
				mov rcx, 0
				jmp .open_done
			.new_first:
				mov [rax + Node.PNext], r8
				mov [rbp + NodeOpenList.First], rax
				mov rcx, 1
				jmp .open_done
			.open_done:
				inc qword [rbp + NodeOpenList.Count]
				ret
			
		;IN: rax = AdjecentNode.
		;OUT: rcx = 3 if node was allocated based on f-cost, rcx = 4 if node was allocated based on h-cost.
		.fSortedInsert:
			mov r8, [rbp + NodeOpenList.First]	;save first in open list = current node
			mov rbx, [rax + Node.FCost]			;save adjecents f-cost
			mov rdx, [rax + Node.HCost]			;save adjecents h-cost
			.next_open_node:
				mov r10, r8						;get next topframe
				mov r8, [r8 + Node.PNext]		;save current topframes next node
				cmp qword r8, -1				;if topframes next node is unset
				jz .new_last					;new last node
				;check costs
				;mov r9, [rax + Node.FCost]		;save adjecents f-cost
				cmp rbx, [r8 + Node.FCost]		;compare adjecents f-cost with topframes f-cost
				jg .next_open_node				;if adjecent is more f-expensive, start new frame
				jl .node_is_cheaper_f			;if adjecent is f-cheaper, link sequence
				;tie-breaker 
				;mov r9, [rax + Node.HCost]		;save adjecents h-cost
				cmp rdx, [r8 + Node.HCost]		;compare adjecents h-cost with topfames h-cost
				jg .next_open_node				;if adjecent is more h-expensive, start new frame
				jle .node_is_cheaper_h			;if adjecent is h-cheaper or equal, link sequence
				.new_last:
					mov [r10 + Node.PNext], rax	;link current topframe to adjecent
					mov rcx, 2					;return 2
					ret
				.node_is_cheaper_f:
					mov rcx, 3					;return 3
					jmp .node_is_cheaper
				.node_is_cheaper_h:
					mov rcx, 4 					;return 4
					jmp .node_is_cheaper
				.node_is_cheaper:
					mov [r10 + Node.PNext], rax	;link current topframe to adjecent
					mov [rax + Node.PNext], r8	;link adjecent to topframes next node
					ret

		;Removes node on top of stack, saves values in regs.
		.fPop:
			pop rbp			;caller addr
			dec qword [r9 + NodeStack.Count]
			;pop sequence
			pop rax			;Node.PNext
			pop rbx			;Node.PParent
			pop rdx			;Node.ID
			pop r8			;Node.FCost
			pop r9			;Node.HCost
			pop r10			;Node.GCost
			pop r11			;Node.Closed
			pop r12			;Node.Traversable
			pop r13			;Node.Resistance
			pop r14			;Node.Position.Y
			pop r15			;Node.Position.X
			;save top ptr
			mov [r9 + NodeStack.Top], rsp
			;return
			push rbp
			ret
			
		;Uses rsi,rdi to access data segment. 
		;Removes node on top of stack, faster then PopTop.
		.fRemoveTop:
			pop rbp
			;call sequence
			call private.fStackDeallocOne
			call private.fSaveTopAfterRet
			;ret
			push rbp
			ret
			
		;deallocates top node
		.fStackDeallocOne:
			;dec node counter
			dec qword [r9 + NodeStack.Count]
			;ret and remove last node
			ret Node.Size
			
		;deallocates all nodes
		.fStackDeallocAll:
			pop rdi
			;remove all nodes
			mov rsi, Node.Size
			imul rsi, [r9 + NodeStack.Count]
			add rsp, rsi
			add rsp, 88
			;null node counter
			mov qword [r9 + NodeStack.Count], 0
			push rdi
			ret
			
		;saves top ptr after correctly a ret needed for some subroutines
		.fSaveTopAfterRet:
			;save base ptr
			mov [rbp + NodeStack.Top], rsp
			add dword [rbp + NodeStack.Top], 0x8
			ret
			
		;saves top ptr
		.fSaveTopBeforeRet:
			;save base ptr
			mov [rbp + NodeStack.Top], rsp
			ret