OBJS = main.c code/variables.c code/general.c code/player.c code/game_object.c code/ui.c code/map.c
OBJ_NAME = main

# Compiler
CC = gcc

INCLUDE_PATHS = -ID:\Programming_libraries\SDL2\x86_64-w64-mingw32\include\SDL2
LIBRARY_PATHS = -LD:\Programming_libraries\SDL2\x86_64-w64-mingw32\lib
COMPILER_FLAGS = -w
# -Wl,-subsystem,windows
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)