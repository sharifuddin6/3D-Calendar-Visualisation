# Makefile

# files to be compiled
FILES = src/main.cpp src/appView.h src/appView.cpp src/appModel.h src/appModel.cpp src/appController.h src/appController.cpp src/helper/calendar.h src/helper/calendar.cpp src/helper/visualisation.h src/helper/visualisation.cpp src/helper/assetloader.h src/helper/assetloader.cpp src/helper/event.h src/helper/event.cpp lib/tinyfiledialogs/tinyfiledialogs.h lib/tinyfiledialogs/tinyfiledialogs.c

# output file
OUTPUT = prototype

# target which compiles executable
all : $(FILES)
	g++ $(FILES) -w -lGL -lGLU -lglut -o $(OUTPUT)
