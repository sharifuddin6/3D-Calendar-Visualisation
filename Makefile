# Makefile

# files to be compiled
FILES = main.cpp appView.h appView.cpp appModel.h appModel.cpp appController.h appController.cpp calendar.h calendar.cpp

# output file
OUTPUT = prototype

# target which compiles executable
all : $(FILES)
	g++ $(FILES) -w -lGL -lGLU -lglut -o $(OUTPUT)
