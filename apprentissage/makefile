main : main.o sceneSDL.o
	gcc -o main main.o sceneSDL.o -lSDL2 -lSDL2_image -lm

main.o : main.c sceneSDL.h
	gcc -c -Wall -Wextra main.c -o main.o -lSDL2 -lSDL2_image -lm

sceneSDL.o : sceneSDL.c
	gcc -c -Wall -Wextra sceneSDL.c -o sceneSDL.o -lSDL2 -lSDL2_image