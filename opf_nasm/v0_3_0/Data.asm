;Author:	Jonas Brown
;Date:		27/12-2016
;File: 		Data.asm

[BITS 64]
[SECTION .data]
;Node
[GLOBAL Node.Position.Y]
[GLOBAL Node.Position.X]
[GLOBAL Node.Resistance]
[GLOBAL Node.Traversable]
[GLOBAL Node.Closed]
[GLOBAL Node.GCost]
[GLOBAL Node.HCost]
[GLOBAL Node.FCost]
[GLOBAL Node.ID]
[GLOBAL Node.PParent]
[GLOBAL Node.PNext]
[GLOBAL Node.Size]
[GLOBAL Node.BaseCost]
[GLOBAL Node.AdjecentOffsets]
;NodeStack
[GLOBAL NodeStack.Top]
[GLOBAL NodeStack.Bottom]
[GLOBAL NodeStack.Count]
;NodeOpenList
[GLOBAL NodeOpenList.First]
[GLOBAL NodeOpenList.Last]
[GLOBAL NodeOpenList.Count]
;Grid
[GLOBAL Grid.IncludeDiagonals]
[GLOBAL Grid.StartX]
[GLOBAL Grid.StartY]
[GLOBAL Grid.PStartNode]
[GLOBAL Grid.TargetX]
[GLOBAL Grid.TargetY]
[GLOBAL Grid.PMap]
[GLOBAL Grid.MapWidth]
[GLOBAL Grid.MapHeight]
[GLOBAL Grid.POutBuffer]
[GLOBAL Grid.OutBufferSize]
;TEST
;[GLOBAL TestData.PMap]
;[GLOBAL TestData.POutBuffer]
[DEFAULT REL]
ALIGN 8

;per node data accessors:
Node:
	;.ShadowBytes2	equ		62		;8*7+6	= 62
	;.ShadowBytes1	equ		60		;8*7+4	= 60
	;.ShadowBytes	equ		58		;8*7+2	= 58
	;imm const: offsets accessors for supplied data:
	.Position.Y:	equ 	56		;8*7 	= 56
	.Position.X:	equ 	54		;8*6+6 	= 54
	;imm const: offsets accessors:
	.Resistance:	equ		52		;8*6+4 	= 52
	.Traversable:	equ		50		;8*6+2 	= 50
	.Closed:		equ		48		;8*6 	= 48
	.GCost:			equ		40		;8*5 	= 40
	.HCost:			equ		32		;8*4 	= 32
	.FCost:			equ 	24		;8*3 	= 24
	.ID: 			equ 	16		;8*2 	= 16
	.PParent:		equ 	8		;8*1 	= 8
	.PNext			equ		0		;8*0 	= 0
	;imm const: offsets accessors: size of a node
	.Size:			equ 	58		;8*7+2	= 58
	;.Size:			equ 	64		;8*6 	= 64
	;const static data: base cost of traversing a node
	.BaseCost: 			dq		1
	.AdjecentOffsets:	dq 		1,0, -1,0, 0,1, 0,-1, 1,1, 1,-1, -1,1, -1,-1

;per execution unit data accessors:	
;stack alignment need - add 2 shadow bytes			
NodeStack:
	;imm const: offsets accessors: the topmost node on stack
	.Top:			equ		0 	;8*0 	= 0
	;imm const: offsets accessors: bottom node on stack
	.Bottom:		equ		8	;8*1 	= 8
	;imm const: number of nodes on the stack
	.Count:			equ		16	;8*2 	= 16

NodeOpenList:
	;imm const: offsets accessors: the fist node in open list
	.First:			equ		24	;8*3 	= 24
	;imm const: offsets accessors: the last node in open list
	.Last:			equ		32	;8*4 	= 32
	;imm const: offsets accessors: number of nodes in open list
	.Count:			equ		40	;8*5 	= 40

Grid:
	;imm const: offsets accessors:
	.IncludeDiagonals	equ		48	;8*6	= 48
	.StartX:			equ 	50	;8*6+2	= 50
	.StartY:			equ 	52	;8*6+4	= 52
	.TargetX:			equ 	54	;8*6+6	= 54
	.TargetY:			equ 	56	;8*7	= 56
	.MapWidth:			equ		58	;8*7+2	= 58
	.MapHeight:			equ 	60	;8*7+4	= 60
	.OutBufferSize: 	equ 	62	;8*7+6	= 62	
	.POutBuffer: 		equ 	64	;8*8	= 64
	.PMap				equ 	72	;8*9	= 72
	.PStartNode:		equ 	80	;8*10	= 80
;	.Size:			equ 	88	;8*11 	= 88