CC=gcc
AR=ar
ASM=nasm

LIBNAME= libbeer# Library Name
LIBVER= 20211015# Library Version

OUTPUT_FOLD= output

OBJS= \
	src/beer.o \
      	src/beer_zip.o \
        src/beer_sock.o \
        src/beer_base64.o

LIB= \
        $(OUTPUT_FOLD)/libbeer.a

HEADER= \
	include/beer.h \
	include/beer_sock.h \
	include/beer_zip.h

INSTALL_FILE= \
	      $(LIBNAME)-$(LIBVER).zip

all:
	if [ ! -d "$(OUTPUT_FOLD)" ]; then \
		mkdir $(OUTPUT_FOLD); \
	fi

	make -f ./src/source.mk
	$(AR) crv $(LIB) $(OBJS)

install:
	cp $(HEADER) $(OUTPUT_FOLD)/
	zip -r $(INSTALL_FILE) ./$(OUTPUT_FOLD)/*
#   rm -rf $(OUTPUT_FOLD)

clear:
	rm -rf $(OUTPUT_FOLD) $(OBJS) $(LIB) 

