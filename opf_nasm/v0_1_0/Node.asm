[BITS 64]
[SECTION .text]
[GLOBAL _Node.Ctor]
[GLOBAL _Node.Initialize]
[GLOBAL _Node.Update]
[GLOBAL _Node.Traceback]
[GLOBAL _Node.GetByID]
[GLOBAL _Node.UpdateAdjecentNode]
[GLOBAL _Node.Open]
[GLOBAL _Node.Pop]
[GLOBAL _Node.RemoveTop]
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
[DEFAULT REL]
 
_Node:
	;Uses rsi,rdi to access data segment.
	;IN: rax = Position.X, rbx = Position.Y, rcx = Traversable, rdx = Resistance.					 
	.Ctor:
		;caller addr
		pop rbp
		;NodeStack.Top + (Node.Size*Node.ID) + offset
		push rbx						;Node.Position.Y: 	offset = 8*10
		push rax						;Node.Position.X: 	offset = 8*9
		push rdx 						;Node.Resistance: 	offset = 8*8
		push rcx						;Node.Traversable: 	offset = 8*7
		push 0							;Node.Closed: 		offset = 8*6
		push 0							;Node.GCost: 		offset = 8*5
		push 0							;Node.HCost: 		offset = 8*4
		push 0							;Node.FCost: 		offset = 8*3
		push qword [NodeStack.Count]	;Node.ID: 			offset = 8*2
		push 0xFFFFFFFFFFFFFFFF			;Node.PParent: 		offset = 8*1
		push 0xFFFFFFFFFFFFFFFF			;Node.PNext: 		offset = 8*0
		;inc node counter
		inc qword [NodeStack.Count]
		;save top ptr
		mov qword [NodeStack.Top], rsp
		;return to caller
		push rbp
		ret
		
	;IN: rax; AdjecentNode, rbx; TargetNode, rdx; CurrentNode.
	;OUT: rcx = 1 if rax is TargetNode, else 0.
	.Initialize:
		;set current node as adjecent nodes parent
		mov [rax + Node.PParent], rdx
		;if this node is target node return 1, else initialize node
		cmp rax, rbx
		jz .target_found
			;store parents g cost as adjecent g cost
			mov r8, [rax + Node.PParent]			;Get parent pointer
			mov r8, [r8 + Node.GCost]				;Get parent g cost from pointer
			mov qword [rax + Node.GCost], r8		;Store parent g cost, in adjecent g cost
			;add the multiplication of basecost and resistance to adjecent g cost
			mov r9, [Node.BaseCost]					;Get static basecost 
			imul r9, [rax + Node.Resistance]		;Multiply basecost with resistance
			add qword [rax + Node.GCost], r9		;Add multiplication result to adjecent basecost
			;calc manhatten distance to target
			call _Node2D.CalcManhattanDistance
			;init h,f costs
			mov qword [rax + Node.HCost], rcx
			mov r8, [rax + Node.GCost]
			mov qword [rax + Node.FCost], r8
			add qword [rax + Node.FCost], rcx
			call _Node.Open
			mov rcx, 0
			ret	
		.target_found:
			mov rcx, 1
			ret
			
	;IN: rax; AdjecentNode, rbx; TargetNode, rdx; CurrentNode.
	;OUT: rcx = 1 if node was updated, else 0.
	.Update:
		;compute new g cost
		mov rdi, [rax + Node.PParent]
		mov rdi, [rdi + Node.GCost]
		xor r10, r10
		mov r10, [Node.BaseCost]
		imul r10, [rax + Node.Resistance]
		add rdi, r10
		;calc manhatten distance to target
		call _Node2D.CalcManhattanDistance
		mov r9, rdi
		add r9, rcx
		;if updated f cost is larger then current f cost, don't update
		cmp r9, [rax + Node.FCost]
		jg .no_update
		je .tie_breaker
		;else update all costs and set new parent; return true
		.do_update:
			;set current node as adjecent nodes parent
			mov [rax + Node.PParent], rdx
			mov [rax + Node.GCost], rdi
			mov [rax + Node.HCost], rcx
			mov [rax + Node.FCost], r9
			mov rcx, 1
			ret
		.tie_breaker:
			;if f-costs are equal and path is shorter, do update
			cmp [rax + Node.GCost], rdi
			jl .do_update
		.no_update:
			mov rcx, 0
			ret
	
	;IN: rax = AdjecentNode.
	;OUT: rcx = 0 if new node or new top node, 1 if new bottom node.
	.Open:
		mov r8, [NodeOpenList.First]
		mov r10, [r8 + Node.FCost]
		cmp r10, [rax + Node.FCost]
		jge .new_first
		mov r9, [NodeOpenList.Last]
		mov r10, [r9 + Node.FCost]
		cmp r10, [rax + Node.FCost]		
		jle .new_last
		call private.fSortedInsert
		jmp .open_done
		.new_first:
			mov r9, [r8 + Node.PNext]
			mov [r8 + Node.PNext], rax
			mov [rax + Node.PNext], r9
			mov rcx, 0
			jmp .open_done
		.new_last:
			mov [r9 + Node.PNext], rax
			mov [NodeOpenList.Last], rax
			mov rcx, 0
			jmp .open_done
		.open_done:
			inc qword [NodeOpenList.Count]
			ret
			
	;IN: rax = OffsetX, rbx = OffsetY, rdi = CurrentNode, rsi; TargetNode
	;OUT: rcx = 0 if out-of-bounds, 1 if closed or non-traversable, 2 if updated, 
	;			3 if sent to update, but not updated, 4 if initialized, 5 if target node 
	.UpdateAdjecentNode:
		;x,y position for adjecent node
		add rax, [rdi + Node.Position.X]
		add rbx, [rdi + Node.Position.Y]
		;if adjecent node is out-of-bounds
		cmp rax, [Grid.MapWidth]
		jge .oob
		cmp rax, 0
		jl .oob
		cmp rbx, [Grid.MapHeight]
		jge .oob
		cmp rbx, 0
		jl .oob
		;reference node adjecent to current
		mov rdx, [Grid.MapWidth]
		call _Node2D.GetByCoordinates
		;if it is closed and is non-traversable 
		cmp qword [rcx + Node.Closed], 0
		jnz .closed_nontraversable
		cmp qword [rcx + Node.Traversable], 0
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
			mov rbx, rsi
			mov rdx, rdi
			call _Node.Update
			cmp rcx, 0
			jz .u_not_updated
			mov rcx, 2
			ret
		.u_not_updated:
			mov rcx, 3
			ret
		.i_initialized:
			mov rax, rcx
			mov rbx, rsi
			mov rdx, rdi
			call _Node.Initialize
			cmp rcx, 1
			jz .i_targetfound
			mov rcx, 4
			ret
		.i_targetfound:
			mov rcx, 5
			ret
			
	;IN: rax = Node.ID
	;OUT: rcx = Node Pointer
	.GetByID:
		imul r8, rax, Node.Size
		mov rcx, [NodeStack.Bottom]
		sub rcx, r8
		ret
			
	;IN: rax = TargetNode, rbx = POutBuffer, rdx = DWord Index,  rsi = Starting Node, rdi = Pop Counter
	;OUT: rcx = Path Length
	.Traceback:
		;store node id on stack
		mov r8, [rax + Node.ID]				;Get node id
		push r8								;Push node id to stack
		inc rcx								;Inc path length
		;if current traceback nodes parent is not start node
		cmp qword [rax + Node.PParent], rsi
		jz .fill_outbuffer
			;recursively traceback through parents
			mov rax, [rax + Node.PParent]
			jmp .Traceback
		.fill_outbuffer:
			;pop the node id into outbuffer
			pop r8
			mov [rbx + rdx], r8
			add rdx, 4
			inc rdi
			cmp rdi, rcx
			jz .done
			jmp .fill_outbuffer
		.done:
			ret
			
	;Uses rsi,rdi to access data segment.
	;Removes node on top of stack, saves values in regs.
	.Pop:
		pop rbp		;caller addr
		;dec node counter
		;mov rsi, NodeStack.Count
		dec qword [NodeStack.Count]
		;pop sequence
		pop rax		;Node.PNext
		pop rbx		;Node.PParent
		pop rdx		;Node.ID
		pop r8		;Node.FCost
		pop r9		;Node.HCost
		pop r10		;Node.GCost
		pop r11		;Node.Closed
		pop r12		;Node.Traversable
		pop r13		;Node.Resistance
		pop r14		;Node.Position.Y
		pop r15		;Node.Position.X
		;save top ptr
		;mov rsi, NodeStack.Top
		mov [NodeStack.Top], rsp
		;return
		push rbp
		ret
		
	;Uses rsi,rdi to access data segment. 
	;Removes node on top of stack, faster then PopTop.
	.RemoveTop:
		pop rbp
		;call sequence
		call private.fStackDeallocOne
		call private.fSaveTopAfterRet
		;ret
		push rbp
		ret
		
	;Uses rsi,rdi to access data segment. 
	;Empties the node stack.
	.Empty:
		pop rbp
		;call sequence
		call private.fStackDeallocAll
		call private.fSaveTopAfterRet
		;ret
		push rbp
		ret	
		
	;PRIVATE SUBROUTINES:
	private:
		;IN: rax = AdjecentNode.
		;OUT: rcx = 2 if node was allocated based on f-cost, rcx = 3 if node was allocated based on h-cost.
		.fSortedInsert:
			mov r8, [NodeOpenList.First]	;save first in open list = current node
			.next_open_node:
				mov r10, r8					;save current topframe
				mov r8, [r8 + Node.PNext]	;save current topframes next node
				;check costs
				mov r9, [rax + Node.FCost]	;save adjecents f-cost
				cmp r9, [r8 + Node.FCost]	;compare adjecents f-cost with next nodes f-cost
				jg .next_open_node			;if adjecent is more f-expensive, start new frame
				jl .node_is_cheaper_f		;if adjecent is f-cheaper, link sequence
				;tie-breaker 
				mov r9, [rax + Node.HCost]	;save adjecents h-cost
				cmp r9, [r8 + Node.HCost]	;compare adjecents h-cost with next nodes h-cost
				jg .next_open_node			;if adjecent is more h-expensive, start new frame
				jle .node_is_cheaper_h		;if adjecent is h-cheaper or equal, link sequence
				.node_is_cheaper_f:
					mov rcx, 2					;return 2
					jmp .node_is_cheaper
				.node_is_cheaper_h:
					mov rcx, 3 					;return 3
					jmp .node_is_cheaper
				.node_is_cheaper:
					mov [r10 + Node.PNext], rax	;link current topframe to adjecent
					mov [rax + Node.PNext], r8	;link adjecent to topframes next node
					ret
			
		;deallocates top node
		.fStackDeallocOne:
			;dec node counter
			dec qword [NodeStack.Count]
			;ret and remove last node
			ret Node.Size
			
		;deallocates all nodes
		.fStackDeallocAll:
			pop r8
			;remove all nodes
			mov rsi, Node.Size
			imul rsi, [NodeStack.Count]
			add rsp, rsi
			;null node counter
			mov qword [NodeStack.Count], 0
			;ret
			push r8
			ret
			
		;saves top ptr after correctly a ret needed for some subroutines
		.fSaveTopAfterRet:
			;save base ptr
			mov [NodeStack.Top], rsp
			add dword [NodeStack.Top], 0x8
			ret
			
		;saves top ptr
		.fSaveTopBeforeRet:
			;save base ptr
			mov [NodeStack.Top], rsp
			ret