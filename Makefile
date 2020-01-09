all: game.o rules.o rule_tests.o select sserver
	gcc -o game game.o rules.o rule_tests.o
game.o: game.c chess_base.h
	gcc -c game.c
rules.o: rules.c chess_base.h
	gcc -c rules.c
rules_tests.o: rule_tests.c chess_base.h
	gcc -c rule_tests.c

select: sclient sserver

sserver: select_server.o networking.o rules.o game.o
	gcc -o server select_server.o networking.o rules.o game.o

sclient: select_client.o networking.o rules.o game.o
	gcc -o client select_client.o networking.o game.o rules.o

select_client.o: select_client.c networking.h
	gcc -c select_client.c

select_server.o: select_server.c networking.h
	gcc -c select_server.c

networking.o: networking.c networking.h
	gcc -c networking.c


run:
	./game
clean:
	rm -f *~
	rm -f *.o
