SOURCE= \
	src/beer_sock.cc

OBJS=   \
	src/beer_sock.o
LIBS=
INC= \
     -Iinclude/
CPP=g++

$(OBJS): $(SOURCE)
	$(CPP) -W -Wall -O2 -c -o $@ $^ $(INC) $(LIBS)
