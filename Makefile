mac:
	gcc -g -I src -I /usr/local/include -L /usr/local/lib -o game -lSDL2main -lSDL2 -lSDL2_image game.c
wind:
	gcc -g -I src -I sdl/include -L sdl/lib -o game game.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image