CC = clang++
CFLAGS = -std=c++2a -Wall -g
OBJ = games/pong.cpp \
	shapes/shapes.cpp \
	renderer/terminalRenderer.cpp \
	main.cpp


all:
	$(CC) $(CFLAGS) $(OBJ) -o pong.exe