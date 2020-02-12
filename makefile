CURRENTDIR = $(shell pwd)
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJDIR = $(SRCDIR)/obj
OBJECTS = $(patsubst $(SRCDIR)/%.c,%.o,$(SOURCES))

FLAGS = -Wall $(shell sdl2-confif --cflags)
LIBS = $(shell sdl2-config --libs)
CC = cc

BINDIR = bin
APPNAME = snake
BIN = $(BINDIR)/$(APPNAME)

LOGSDIR = $(BINDIR)
LOGFILE = $(LOGSDIR)/.log


env:
	export SNAKE_LOG_FILE=$(CURRENTDIR)/$(LOGFILE)

directories:
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(LOGSDIR)

$(OBJECTS):
	$(CC) $(FLAGS) $(LIBS) -c $(SOURCES)
	@mv *.o $(OBJDIR)

build: env directories $(OBJECTS)
	$(CC) $(FLAGS) $(LIBS) $(OBJDIR)/$(OBJECTS) -o $(BIN)

debug:
	$(CC) $(FLAGS) $(LIBS) -g $(SOURCES)

run:
	@echo ""
	@./$(BIN)

$(APPNAME):
	$(CC) $(FLAGS) $(LIBS) -O2 $(OBJECTS) -o $(BIN)

.PHONY: clean
clean:
	-rm -rfv a.out* $(OBJDIR)

all: build run
