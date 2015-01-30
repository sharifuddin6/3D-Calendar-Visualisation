# Makefile

# files to be compiled
FILES = main.cpp cube.h cube.cpp calendar.h calendar.cpp

# output file
OUTPUT = prototype

# target which compiles executable
all : $(FILES)
	g++ $(FILES) -w -lGL -lGLU -lglut -o $(OUTPUT)
