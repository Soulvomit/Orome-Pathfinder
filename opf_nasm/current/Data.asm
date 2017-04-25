;Author:	Jonas Brown
;Date:		27/12-2016
;File: 		Data.asm

[BITS 64]
[SECTION .data]
;Node
[GLOBAL Node.Position.Y]
[GLOBAL Node.Position.X]
[GLOBAL Node.Resistance]
[GLOBAL Node.Closed]
[GLOBAL Node.GCost]
[GLOBAL Node.HCost]
[GLOBAL Node.FCost]
[GLOBAL Node.ID]
[GLOBAL Node.PParent]
[GLOBAL Node.PNext]
[GLOBAL Node.Size]
;NodeStack
[GLOBAL NodeStack.Top]
[GLOBAL NodeStack.Bottom]
[GLOBAL NodeStack.Count]
;NodeOpenList
[GLOBAL NodeOpenList.First]
[GLOBAL NodeOpenList.Count]
;AdjecentArray
[GLOBAL AdjecentArray.Count]
[GLOBAL AdjecentArray.Offsets]
;Grid
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
[GLOBAL Grid.Size]
[DEFAULT REL]
ALIGN 8

;per node data accessors
;description of node struct:
Node:
	;imm const: offsets accessors, 2d related
	.Position.Y:	equ 	54		;8*6+6 	= 54
	.Position.X:	equ 	52		;8*6+4 	= 52
	;imm const: offsets accessors, general
	.Resistance:	equ		50		;8*6+2 	= 50
	.Closed:		equ		48		;8*6 	= 48
	.GCost:			equ		40		;8*5 	= 40
	.HCost:			equ		32		;8*4 	= 32
	.FCost:			equ 	24		;8*3 	= 24
	.ID: 			equ 	16		;8*2 	= 16
	.PParent:		equ 	8		;8*1 	= 8
	.PNext			equ		0		;8*0 	= 0
	;imm const: offsets accessors, size of a node struct
	.Size:			equ 	56		;8*7	= 56

;per execution unit data accessors
;description of node stack struct:			
NodeStack:
	;imm const: offsets accessors, the topmost node on stack
	.Top:			equ		0 	;8*0 	= 0
	;imm const: offsets accessors, bottom node on stack
	.Bottom:		equ		8	;8*1 	= 8
	;imm const: number of nodes on the stack
	.Count:			equ		16	;8*2 	= 16

;description of node open list struct:
NodeOpenList:
	;imm const: offsets accessors, the fist node in open list
	.First:			equ		24	;8*3 	= 24
	;imm const: offsets accessors, number of nodes in open list
	.Count:			equ		32	;8*4 	= 32

;description of node adjecent array struct:
AdjecentArray:
	;imm const: offsets accessors, adjecent array count
	.Count:		equ		40	;8*5	= 40
	;static data: adjecent offsets (first half = straights, second half = diagonals)
	.Offsets:	dw 		1,0, -1,0, 0,1, 0,-1, 1,1, 1,-1, -1,1, -1,-1
	
;description of grid struct 
Grid:
	;imm const: offsets accessors, grid
	.StartX:			equ 	42	;8*5+2	= 42
	.StartY:			equ 	44	;8*5+4	= 44
	.TargetX:			equ 	46	;8*5+6	= 46
	.TargetY:			equ 	48	;8*6	= 48
	.MapWidth:			equ		50	;8*6+2	= 50
	.MapHeight:			equ 	52	;8*6+4	= 52
	.OutBufferSize: 	equ 	54	;8*6+6	= 54	
	.POutBuffer: 		equ 	56	;8*7	= 56
	.PMap				equ 	64	;8*8	= 64
	.PStartNode:		equ 	72	;8*9	= 72
	;imm const: offsets accessors, size of a grid struct
	.Size:				equ 	80	;8*10 	= 80
