ASM_SOURCE = \
	./src/beer_base64.s

ASM_OBJ = \
	./src/beer_base64.o

all: $(ASM_OBJ)

src/%.o: src/%.s
	nasm -felf64 $^