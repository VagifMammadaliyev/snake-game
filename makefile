CURRENTDIR = $(shell pwd)
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJDIR = $(SRCDIR)/obj
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

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

dirs:
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(LOGSDIR)

$(OBJECTS):
	$(CC) $(FLAGS) $(LIBS) -c $(SOURCES)
	mv *.o $(OBJDIR)/

build: env dirs $(OBJECTS)
	$(CC) $(FLAGS) $(LIBS) $(OBJECTS) -o $(BIN)

rebuild: clean build

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

all: rebuild run
