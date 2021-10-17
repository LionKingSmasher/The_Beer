CC_SOURCE= \
	./src/beer_sock.cc \
	./src/beer_zip.cc \
	./src/beer.cc

OUT_OBJS=   \
	./src/beer_sock.o \
	./src/beer_zip.o \
	./src/beer.o
EX_LIBS=
EX_INC= \
     -Iinclude/

CPP=g++

CFLAGS = -W -Wall -O2 -fPIC -no-pie -c -o

all: $(OUT_OBJS)
	make -f ./src/asm_source.mk

src/%.o: src/%.cc
	$(CPP) $(CFLAGS) $@ $^ $(EX_INC) $(EX_LIBS)
