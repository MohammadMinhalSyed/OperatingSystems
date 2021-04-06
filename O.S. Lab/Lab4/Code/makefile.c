CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread
LFLAGS = 
LIBS = -lm
SOURCES = main.c hostd.c queue.c sigtrap.c utility.c
OBJECTS = $(subst .c,.o,$(SOURCES))
BIN = main
.PHONY: clean help

main : $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $< 

all : $(BIN)

clean:
	rm -f $(OBJECTS) $(BIN) *~

help:
	@echo "Valid targets:"
	@echo "  all:    generates all binary files"
	@echo "  clean:  removes .o and binary files"