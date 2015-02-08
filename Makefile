# Makefile
CC = g++
CFLAGS = -Wall
LIBS = -lGL -lGLU -lglut -lm -lpthread

# files to be compiled
FILES = src/main.cpp src/appView.cpp src/appModel.cpp src/appController.cpp src/helper/calendar.cpp src/helper/visualisation.cpp src/helper/assetloader.cpp src/helper/event.cpp lib/tinyfiledialogs/tinyfiledialogs.c

# output file
OUTPUT = prototype

# target which compiles executable
all : $(FILES)
	$(CC) $(CFLAGS) $(FILES) $(LIBS) -o $(OUTPUT)

clean :
	rm -f $(OUTPUT)
