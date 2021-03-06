#include "chess_base.h"
void print_possible_positions(GAME * game){
  print_board_debug(game);
  printf("\nPiece Position {Possible Moves}\n\n");
  for(int i = 0; i < 32; i++){
    PIECE * piece = game->pieces[i];
    if(piece){
      print_piece(piece);
      printf(" (%d, %d) { ", piece->x, piece->y);
      for(int y = 0; y < 8; y ++)
	for(int x = 0; x < 8; x++)
	  if(is_valid_move_for_piece(game, piece, x, y))
	    printf("(%d, %d) ", x, y);
      printf("}\n");
    }
  }
}
void pawn_test(){
  printf("\n========== TESTING PAWNS ==========\n\n");
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
  print_possible_positions(game);
}
void knight_test(){
  printf("\n========== TESTING KNIGHTS =========\n\n");
  GAME * game = generate_game();
  for(int i = 0; i < 32; i ++){
    PIECE * p = game->pieces[i];
    if(p->type != Knight && p->type != King){
      game->board[p->y][p->x] = 0;
      game->pieces[i] = 0;
    }
  }
  move_piece(game, game->board[0][4], 3, 3);
  move_piece(game, game->board[7][4], 4, 4);
  game->board[3][3]->type = game->board[4][4]->type = Knight;
  print_possible_positions(game);
}
void bishop_test(){
  printf("\n========== TESTING BISHOPS =========\n\n");
  GAME * game = generate_game();
  for(int i = 0; i < 32; i ++){
    PIECE * p = game->pieces[i];
    if(p->type != Bishop && p->type != King){
      game->board[p->y][p->x] = 0;
      game->pieces[i] = 0;
    }
  }
  move_piece(game, game->board[0][4], 3, 5);
  move_piece(game, game->board[7][4], 4, 2);
  game->board[2][4]->type = game->board[5][3]->type = Bishop;
  print_possible_positions(game);
}
void rook_test(){
  printf("\n========== TESTING ROOKS ===========\n\n");
  GAME * game = generate_game();
  for(int i = 0; i < 32; i ++){
    PIECE * p = game->pieces[i];
    if(p->type != Rook && p->type != King && !(p->x == 4 && p->type == Pawn)){
      game->board[p->y][p->x] = 0;
      game->pieces[i] = 0;
    }else if(p->type = King){
      p->type = Knight;
    }
  }
  move_piece(game, game->board[1][4], 4, 3);
  move_piece(game, game->board[6][4], 3, 4);
  game->board[3][4]->type = game->board[4][3]->type = Rook;
  print_possible_positions(game);
}
void queen_test(){
  printf("\n========== TESTING QUEENS ==========\n\n");
  GAME * game = generate_game();
  for(int i = 0; i < 32; i ++){
    PIECE * p = game->pieces[i];
    if(p->type != Rook && p->type != King && !(p->x == 4 && p->type == Pawn)){
      game->board[p->y][p->x] = 0;
      game->pieces[i] = 0;
    }else if (p->type != King){
      p->type = Queen;
    }else{
      p->type = Knight;
    }
  }
  move_piece(game, game->board[1][4], 4, 3);
  move_piece(game, game->board[6][4], 3, 4);
  game->board[3][4]->type = game->board[4][3]->type = Queen;
  print_possible_positions(game);
}
void king_test(){
  printf("\n========== TESTING KINGS =========\n\n");
  GAME * game = generate_game();
  for(int i = 0; i < 32; i ++){
    PIECE * p = game->pieces[i];
    if(p->type != Rook && p->type != King && !(p->x == 4 && p->y == 6)){
      game->board[p->y][p->x] = 0;
      game->pieces[i] = 0;
    }
  }
  //move_piece(game, game->board[1][4], 4, 3);
  move_piece(game, game->board[6][4], 3, 4);
  game->board[4][3]->type = Rook;
  print_possible_positions(game);
}
void setup_test(){
  printf("\n========== TESTING BOARD =========\n\n");
  GAME * game = generate_game();
  print_possible_positions(game);
}
void check_test(){
  printf("\n========== TESTING CHECK =========\n(WHITE TO MOVE)\n\n");
  GAME * game = generate_game();
  move_piece(game, game->board[1][3], 3, 2);
  move_piece(game, game->board[6][4], 4, 5);
  move_piece(game, game->board[0][6], 5, 2);
  move_piece(game, game->board[7][5], 1, 3);
  print_board_debug(game);
  printf("\nPiece Position {Possible Moves}\n\n");
  for(int i = 0; i < 16; i++){
    PIECE * piece = game->sides[0]->pieces[i];
    if(piece){
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
int main(){
  pawn_test();
  knight_test();
  bishop_test();
  rook_test();
  queen_test();
  king_test();
  setup_test();
  check_test();
  play_game();
  return 0;
}
