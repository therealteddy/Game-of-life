GINCLUDE=C:/msys64/mingw64/include 
LINCLUDE=./include/
LIBRARY=C:/msys64/mingw64/lib
SRCDIR=./src/*
BINDIR=./bin/main.exe

default: 
	gcc $(SRCDIR) -o $(BINDIR) -std=c99 -I $(GINCLUDE) -I $(LINCLUDE) -L $(LIBRARY) -lraylib -lopengl32 -lgdi32 -lwinmm -v

run: default
	./bin/./main.exe