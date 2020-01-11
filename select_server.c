#include "networking.h"
#include "chess_base.h"

void process(char *s);
void subserver(int from_client);

int main() {

  int listen_socket;
  int client_socket;
  int subserver_count = 0;
  char buffer[BUFFER_SIZE];

  //set of file descriptors to read from
  fd_set read_fds;

  listen_socket = server_setup();

  while (1) {
    client_socket = server_connect(listen_socket);
    subserver(client_socket);
  }
}

void subserver(int client_socket) {
  GAME * game = generate_game();
  print_board(game);
  char buffer[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);
  int move [4] = {-1, -1, -1, -1};
  printf("WHITE TO MOVE!\n");
  while(1){
    memset(buffer, 0, BUFFER_SIZE);
    memset(move, -1, 4);
    get_move_from_stdin(move);
    int r = attempt_piece_move(game, game->board[move[1]][move[0]], move[2], move[3]);
    if(r){
      game->turn = !game->turn;
      print_board(game);
      break;
    }
  }
  move[0] += 65;
  move[1] += 49;
  move[2] += 65;
  move[3] += 49;
  for(int i = 0; i < 4; i++) buffer[i] = move[i];
  write(client_socket, buffer, sizeof(buffer));
  int game_won = 0;
  printf("BLACK TO MOVE...\n");
  while (read(client_socket, buffer, sizeof(buffer))) {
    printf("BLACK PLAYED: %s\n\n", buffer);
    attempt_piece_move(game, game->board[buffer[1] - 49][buffer[0] - 65], buffer[2] - 65, buffer[3] - 49);
    print_board(game);
    game->turn = !game->turn;    
    if(in_draw(game)){
      if(in_check(game, game->turn)){
	printf("%s WINS!\n", game->turn ? "WHITE" : "BLACK");
      }else{
	printf("STALEMATE. \n");
      }
      exit(0);
    }
    while(1){
      memset(buffer, 0, BUFFER_SIZE);
      memset(move, -1, 4);
      get_move_from_stdin(move);
      int r = attempt_piece_move(game, game->board[move[1]][move[0]], move[2], move[3]);
      if(r){
	game->turn = !game->turn;
	print_board(game);
	printf("BLACK TO MOVE...\n");
	break;
      }
    }
    move[0] += 65;
    move[1] += 49;
    move[2] += 65;
    move[3] += 49;
    for(int i = 0; i < 4; i++) buffer[i] = move[i];
    write(client_socket, buffer, sizeof(buffer));
    if(in_draw(game)){
      if(in_check(game, game->turn)){
	printf("%s WINS!\n", game->turn ? "WHITE" : "BLACK");
      }else{
	printf("STALEMATE. \n");
      }
      exit(0);
    }
  }
  close(client_socket);
  exit(0);
}