#include "chess_base.h"
void print_possible_positions(GAME * game, PIECE_TYPE type){
  print_board(game);
  printf("\nPiece Position {Possible Moves}\n\n");
  for(int i = 0; i < 32; i++){
    PIECE * piece = game->pieces[i];
    if(piece){// && piece->type == type){
      print_piece(piece);
      printf(" (%d, %d) { ", piece->x, piece->y);
      for(int y = 0; y < 8; y ++)
	for(int x = 0; x < 8; x++)
	  if(is_valid_move(game, piece, x, y))
	    printf("(%d, %d) ", x, y);
      printf("}\n");
    }
  }
}
void pawn_test(){
  printf("========== TESTING PAWNS ==========\n\n");
  GAME * game = generate_game();

  move_piece(game, game->board[6][0], 2, 2);
  move_piece(game, game->board[6][1], 4, 3);
  move_piece(game, game->board[6][7], 7, 5);

  move_piece(game, game->board[1][6], 5, 5);
  move_piece(game, game->board[1][7], 3, 4);
  move_piece(game, game->board[1][0], 0, 2);

  for(int i = 0; i < 32; i ++){
    PIECE * p = game->pieces[i];
    if(p->type != Pawn){
      game->board[p->y][p->x] = 0;
      game->pieces[i] = 0;
    }
  }
  print_possible_positions(game, Pawn);
}
void knight_test(){
  printf("========== TESTING KNIGHTS =========\n\n");
  GAME * game = generate_game();
  for(int i = 0; i < 32; i ++){
    PIECE * p = game->pieces[i];
    if(p->type != Knight && p->type != King){
      game->board[p->y][p->x] = 0;
      game->pieces[i] = 0;
    }
  }
  move_piece(game, game->board[0][4], 3, 3);
  move_piece(game, game->board[7][3], 4, 4);
  game->board[3][3]->type = game->board[4][4]->type = Knight;
  print_possible_positions(game, Knight);
}
int main(){
  pawn_test();
  knight_test();
  return 0;
}
