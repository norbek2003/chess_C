all: game.o rules.o
	gcc -o game game.o rules.o
game.o: game.c game.h
	gcc -c game.c
rules.o: rules.c game.h
	gcc -c rules.c
run:
	./game
