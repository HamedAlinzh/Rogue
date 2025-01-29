CC = gcc
CFLAGS = -lncurses -lSDL2 -lSDL2_mixer -I$(INDIR) -g
INDIR = ./include/
SRCDIR = ./source/
SOURCES = $(SRCDIR)*.c\
		  $(SRCDIR)entities/*.c


all: rogue

rogue: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./rogue

clean:
	rm rogue
