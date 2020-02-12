CURRENTDIR = $(shell pwd)
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJDIR = $(SRCDIR)/obj
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

FLAGS = -Wall $(shell sdl2-config --cflags)
LIBS = $(shell sdl2-config --libs)
CC = cc

BINDIR = bin
APPNAME = snake
BIN = $(BINDIR)/$(APPNAME)


dirs:
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)

$(OBJECTS):
	$(CC) $(FLAGS) $(LIBS) -c $(SOURCES)
	mv *.o $(OBJDIR)/

build: dirs $(OBJECTS)
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
	-rm $$SNAKE_LOG_FILE

all: rebuild run
