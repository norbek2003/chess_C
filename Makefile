
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
	gcc `pkg-config --cflags gtk+-3.0` -o server gui.o select_server.o networking.o game.o rules.o  `pkg-config --libs gtk+-3.0`


sclient: select_client.o networking.o rules.o game.o gui.o
	gcc `pkg-config --cflags gtk+-3.0` -o client gui.o select_client.o networking.o game.o rules.o  `pkg-config --libs gtk+-3.0`

select_client.o: select_client.c networking.h
	gcc `pkg-config --cflags gtk+-3.0` -c select_client.c `pkg-config --libs gtk+-3.0`
select_server.o: select_server.c networking.h
	gcc `pkg-config --cflags gtk+-3.0` -c select_server.c `pkg-config --libs gtk+-3.0`
gui.o: gui.c gui.h chess_base.h
	gcc `pkg-config --cflags gtk+-3.0` -c gui.c `pkg-config --libs gtk+-3.0`
networking.o: networking.c networking.h
	gcc -c networking.c
run:
	./game
clean:
	rm -f *~
	rm -f *.o
