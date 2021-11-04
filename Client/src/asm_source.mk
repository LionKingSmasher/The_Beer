ASM_SOURCE = \
	./src/beer_base64.asm

ASM_OBJ = \
	./src/beer_base64.o

all: $(ASM_OBJ)

src/%.o: src/%.asm
	nasm -felf64 $^