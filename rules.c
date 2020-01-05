#include "chess_base.h"

int is_valid_move_pawn(struct game * game, struct piece * piece, int x, int y){
  int direction = piece->side ? -1 : 1;
  if(piece->x == x && abs(piece->y - y) <= 2 && !game->board[y][x]){
    if(piece->y + direction == y){
      return 1;
    }
    if((piece->y == (piece->side ? 6 : 1)) && (piece->y + (direction  * 2) == y)){
      return 1;
    }
  }
  if(abs(piece->x - x) == 1 && y - piece->y == direction && game->board[y][x] && game->board[y][x]->side != piece->side){
    //printf("\n(%d, %d, %d, %d, %d, 3)", piece->x, piece->y, x, y, direction);
    return 1;
  }
  return 0;
}
int is_valid_move(struct game * game, struct piece * piece, int x, int y){
  if(x == -1 || x == 8 || y == -1 || y == 8)
    return 0;
  if(piece->x == x && piece->y == y)
    return 0;
  switch(piece->type){
  case Pawn:
    return is_valid_move_pawn(game, piece, x, y);
  case Knight:
    break;
  case Bishop:
    break;
  case Rook:
    break;
  case Queen:
    break;
  case King:
    break;
  }
  return 0;
}
