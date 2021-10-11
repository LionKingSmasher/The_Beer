CC_SOURCE= \
	./src/beer_sock.cc \
	./src/beer_zip.cc

OUT_OBJS=   \
	./src/beer_sock.o \
	./src/beer_zip.o
EX_LIBS=
EX_INC= \
     -Iinclude/

CPP=g++

all: $(OUT_OBJS)

src/%.o: src/%.cc
	$(CPP) -W -Wall -O2 -c -o $@ $^ $(EX_INC) $(EX_LIBS)
