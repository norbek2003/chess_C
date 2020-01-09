#include "networking.h"
#include "chess_base.h"

int main(int argc, char **argv) {
  GAME * game = generate_game();
  print_board(game);
  int server_socket;
  char buffer[BUFFER_SIZE];
  int move [4] = {-1, -1, -1, -1};
  fd_set read_fds;

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );
  int game_won = 0;
  while (!game_won) {
    printf("WHITE TO MOVE...\n");
    read(server_socket, buffer, sizeof(buffer));
    printf("WHITE PLAYED: %s\n\n", buffer);
    attempt_piece_move(game, game->board[buffer[1] - 49][buffer[0] - 65], buffer[2] - 65, buffer[3] - 49);
    print_board(game);
    game->turn = !game->turn;
    if(in_draw(game)){
      if(in_check(game, game->turn)){
	printf("%s WINS!\n", game->turn ? "WHITE" : "BLACK");
      }else{
	printf("STALEMATE. \n");
      }
      return 0;
    }
    printf("BLACK TO MOVE!\n");
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
    write(server_socket, buffer, sizeof(buffer));
    if(in_draw(game)){
      if(in_check(game, game->turn)){
	printf("%s WINS!\n", game->turn ? "WHITE" : "BLACK");
      }else{
	printf("STALEMATE. \n");
      }
      exit(0);
    }
  }
}
