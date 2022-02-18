UNAME := $(shell uname)
CC = gcc
CFLAGS = -Wall -std=c11 -g
LDFLAGS= -L.


INC = include/
SRC = src/
BIN = bin/
PARSER_SRC_FILES = $(wildcard src/SVG*.c)
PARSER_OBJ_FILES = $(patsubst src/SVG%.c,bin/SVG%.o,$(PARSER_SRC_FILES))

ifeq ($(UNAME), Linux)
	XML_PATH = /usr/include/libxml2
endif
ifeq ($(UNAME), Darwin)
	XML_PATH = /System/Volumes/Data/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/libxml2
endif

parser: $(BIN)libsvgparser.so

$(BIN)libsvgparser.so: $(PARSER_OBJ_FILES) $(BIN)LinkedListAPI.o
	gcc -shared -o $(BIN)libsvgparser.so $(PARSER_OBJ_FILES) $(BIN)LinkedListAPI.o -lxml2 -lm

#Compiles all files named SVG*.c in src/ into object files, places all corresponding SVG*.o files in bin/
$(BIN)SVG%.o: $(SRC)SVG%.c $(INC)LinkedListAPI.h $(INC)SVG*.h
	gcc $(CFLAGS) -I$(XML_PATH) -I$(INC) -c -fpic $< -o $@

$(BIN)liblist.so: $(BIN)LinkedListAPI.o
	$(CC) -shared -o $(BIN)liblist.so $(BIN)LinkedListAPI.o

$(BIN)LinkedListAPI.o: $(SRC)LinkedListAPI.c $(INC)LinkedListAPI.h
	$(CC) $(CFLAGS) -c -fpic -I$(INC) $(SRC)LinkedListAPI.c -o $(BIN)LinkedListAPI.o

clean:
	rm -rf $(BIN)StructListDemo $(BIN)xmlExample $(BIN)*.o $(BIN)*.so


###################################################################################################
SVGParser.o: SVGParser.c SVGParser.h
	$(CC) $(CFLAGS) -c -fpic SVGParser.c

SVGParser: $(SRC)SVGParser.c $(SRC)LinkedListAPI.c $(SRC)SVGHelper.c
	$(CC) $(CFLAGS) -I$(XML_PATH) -I$(INC) $(SRC)SVGParser.c $(SRC)LinkedListAPI.c $(SRC)SVGHelper.c -lm -lxml2 -o $(BIN)SVGParser

SVGHelper.o: SVGHelper.c SVGHelper.h
	$(CC) $(CFLAGS) -c -fpic SVGHelper.c

SVGHelper: SVGHelper.o 
	$(CC) $(CFLAGS) $(LDFLAGS) -I/usr/include/libxml2 -o SVGHelper SVGHelper.o -lxml2