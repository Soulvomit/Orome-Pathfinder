nasm64 -O 3 -f win64 Node.asm -o Node.o64 -l Node.lst
#nasm64 -Wall -g -F cv8 -f win64 Node.asm -o Node.o64 -l Node.lst
nasm64 -O 3 -f win64 Node2D.asm -o Node2D.o64 -l Node2D.lst
#nasm64 -Wall -g -F cv8 -f win64 Node2D.asm -o Node2D.o64 -l Node2D.lst
nasm64 -O 3 -f win64 FindPath.asm -o FindPath.o64 -l FindPath.lst
#nasm64 -Wall -g -F cv8 -f win64 FindPath.asm -o FindPath.o64 -l FindPath.lst
nasm64 -O 3 -f win64 Data.asm -o Data.o64 -l Data.lst
#nasm64 -Wall -g -F cv8 -f win64 Data.asm -o Data.o64 -l Data.lst

#link .dll:
ld -shared -O 3 -e DllMain -o opf_debug.dll Node.o64 Node2D.o64 FindPath.o64 Data.o64 -Map=opf_debug.map
ld -shared -O 3 -s -e DllMain -o opf.dll Node.o64 Node2D.o64 FindPath.o64 Data.o64 -Map=opf.map

#ld -shared -O 3 -s -e DllMain -o pathfinder.dll Node.o64 Node2D.o64 FindPath.o64 Data.o64 --stack 0x1DCD65000 -Map=pathfinder.map