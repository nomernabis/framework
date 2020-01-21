OBJS = main.cpp Window.h Window.cpp Color.h Color.cpp Rectangle.h Rectangle.cpp Renderer.h Renderer.cpp Colors.h game/Map.h game/Map.cpp
CC = g++
COMPILER_FLAGS = -w
LINKER_FLAGS = -lSDL2
OBJ_NAME = a
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
