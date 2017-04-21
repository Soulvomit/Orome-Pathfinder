;Author:	Jonas Brown
;Date:		27/12-2016
;File: 		Node2D.asm

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
	;IN: rax = Node1, rbx = Node2
	;OUT: rcx = vManhattanDistance
	.CalcManhattanDistance:
		mov r8w, [rax + Node.Position.X] 
		mov r9w, [rax + Node.Position.Y]
		sub r8w, [rbx + Node.Position.X] 
		sub r9w, [rbx + Node.Position.Y]
		;abs r8
		mov r10w, r8w 
		neg r8w
		cmovl r8w, r10w
		;abs r9
		mov r10w, r9w
		neg r9w
		cmovl r9w, r10w
		;store return value in rcx and ret
		and r8, 0xFFFF
		and r9, 0xFFFF
		mov rcx, r8
		add rcx, r9
		ret
		
	;Uses r8-r15 as temp storage.
	;IN: ax = Node.Position.X; bx = Node.Position.Y, dx = Grid.Width
	;OUT: rcx = Node Pointer
	.GetByCoordinates:
		mov r8, rbx
		imul r8, rdx
		add r8, rax
		imul r8, Node.Size
		mov rcx, [rbp + NodeStack.Bottom]
		sub rcx, r8
		ret