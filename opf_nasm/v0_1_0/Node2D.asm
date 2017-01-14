[BITS 64]
[SECTION .text]
[GLOBAL _Node2D.CalcManhattanDistance]
[GLOBAL _Node2D.GetByCoordinates]
;From Node
[EXTERN Node.Position.X]
[EXTERN Node.Position.Y]
[EXTERN Node.Size]
[EXTERN NodeStack.Bottom]
[DEFAULT REL]

_Node2D:
	;Uses r8-r15 as temp storage 
	;Params: rax = Node1, rbx = Node2
	;Return: rcx = vManhattanDistance
	.CalcManhattanDistance:
		mov r8, [rax + Node.Position.X] 
		mov r9, [rax + Node.Position.Y]
		sub r8, [rbx + Node.Position.X] 
		sub r9, [rbx + Node.Position.Y]
		;abs r8
		mov r10, r8 
		neg r8
		cmovl r8, r10
		;abs r9
		mov r10, r9
		neg r9
		cmovl r9, r10
		;store return value in rcx and ret
		mov rcx, r8
		add rcx, r9
		ret
		
	;Uses r8-r15 as temp storage.
	;Params: rax = Node.Position.X; rbx = Node.Position.Y, rdx = Grid.Width
	;Return: rcx = Node Pointer
	.GetByCoordinates:
		mov r8, rbx
		imul r8, rdx
		add r8, rax
		imul r8, Node.Size
		mov rcx, [NodeStack.Bottom]
		sub rcx, r8
		ret