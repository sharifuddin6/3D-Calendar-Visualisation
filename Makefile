# Makefile
CC = g++
CFLAGS = -Wall
LIBS = -lGL -lGLU -lglut -lm -lpthread

# files to be compiled
FILES = src/main.cpp src/appView.cpp src/appModel.cpp src/appController.cpp src/helper/calendar.cpp src/helper/visualisation.cpp src/helper/event.cpp include/tinyfiledialogs/tinyfiledialogs.c include/drawtext/text3d.cpp include/objmodelloader/objectLoader.cpp

# output file
OUTPUT = 3DCalendarVis

# target which compiles executable
all : $(FILES)
	$(CC) $(CFLAGS) $(FILES) $(LIBS) -o $(OUTPUT)

clean :
	rm -f $(OUTPUT)
