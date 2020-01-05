all: game.o rules.o rule_tests.o
	gcc -o game game.o rules.o rule_tests.o
game.o: game.c chess_base.h
	gcc -c game.c
rules.o: rules.c chess_base.h
	gcc -c rules.c
rules_tests.o: rule_tests.c chess_base.h
	gcc -c rule_tests.c
run:
	./game
clean:
	rm -f *~
	rm -f *.o
