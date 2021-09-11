IN=main.c base/core.c base/headers.c
OUT=xope
FLAGS=-Wall

compile:
	gcc -o $(OUT) $(IN) $(FLAGS)

testasm:
	nasm -f elf64 -o xope.o xope.asm && ld xope.o -o test && ./test

run:
	gcc -o $(OUT) $(IN) $(FLAGS) && ./$(OUT) && nasm -f elf64 -o program.o program.asm && ld program.o -o program && ./program

.PHONY: clean
clean:
	rm $(OUT)
