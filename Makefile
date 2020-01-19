ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif
all: game.o rules.o rule_tests.o select sserver
	$(CC) -o game game.o rules.o rule_tests.o
game.o: game.c chess_base.h
	$(CC) -c game.c
rules.o: rules.c chess_base.h
	$(CC) -c rules.c
rules_tests.o: rule_tests.c chess_base.h
	$(CC) -c rule_tests.c

select: sclient sserver

sserver: select_server.o networking.o rules.o game.o
	$(CC) `pkg-config --cflags gtk+-3.0` -o server gui.o select_server.o networking.o game.o rules.o  `pkg-config --libs gtk+-3.0`


sclient: select_client.o networking.o rules.o game.o gui.o
	$(CC) `pkg-config --cflags gtk+-3.0` -o client gui.o select_client.o networking.o game.o rules.o  `pkg-config --libs gtk+-3.0`

select_client.o: select_client.c networking.h
	$(CC) `pkg-config --cflags gtk+-3.0` -c select_client.c `pkg-config --libs gtk+-3.0`
select_server.o: select_server.c networking.h
	$(CC) `pkg-config --cflags gtk+-3.0` -c select_server.c `pkg-config --libs gtk+-3.0`
gui.o: gui.c gui.h chess_base.h
	$(CC) `pkg-config --cflags gtk+-3.0` -c gui.c `pkg-config --libs gtk+-3.0`
networking.o: networking.c networking.h
	$(CC) -c networking.c
run:
	./game
clean:
	rm -f *~
	rm -f *.o
