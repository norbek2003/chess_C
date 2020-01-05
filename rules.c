#include "chess_base.h"

int is_location_attacked(GAME * game, SIDE by_side, int x, int y){
  //printf("are we?\n");
  for(int i = 0; i < 16; i++){
    PIECE * p = game->sides[by_side]->pieces[i];
    //print_piece(p);
    if(p && !p->captured && is_valid_move(game, p, x, y)){
      return 1;
    }
  }
  return 0;
}
int in_check(GAME * game, SIDE side){
  PIECE * king = game->sides[side]->king;
  return is_location_attacked(game, !side, king->x, king->y);
}
int is_blocked_py_piece(GAME * game, PIECE * piece, int x, int y, int x_dir, int y_dir){
  int xs = piece->x;
  int ys = piece->y;
  while(1){
    xs += x_dir;
    ys += y_dir;
    if(xs == -1 || xs == 8 || ys == -1 || ys == 8)
      break;
    if(xs == x && ys == y)
      break;
    if(game->board[ys][xs])
      return 1;
  }
  return 0;
}
int is_valid_move_pawn(GAME * game, PIECE * piece, int x, int y){
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
    return 1;
  }
  return 0;
}
int is_valid_move_knight(GAME * game, PIECE * piece, int x, int y){
  x = abs(piece->x - x);
  y = abs(piece->y - y);
  return y * y + x * x == 5;
}
int is_valid_move_bishop(GAME * game, PIECE * piece, int x, int y){
  if(abs(piece->x - x) != abs(piece->y - y))
    return 0;
  int x_dir = - (piece->x - x) / abs(piece->x - x);
  int y_dir = - (piece->y - y) / abs(piece->y - y);
  return !is_blocked_py_piece(game, piece, x, y, x_dir, y_dir);
}
int is_valid_move_rook(GAME * game, PIECE * piece, int x, int y){
  int x_dir = piece->x == x ? 0 : (- (piece->x - x) / abs(piece->x - x));
  int y_dir = piece->y == y ? 0 : (- (piece->y - y) / abs(piece->y - y));
  return (x_dir * x_dir + y_dir * y_dir == 1) && !is_blocked_py_piece(game, piece, x, y, x_dir, y_dir);
}
int is_valid_castle(GAME * game, PIECE * king, int x, int y){
  if(in_check(game, king->side) || king->has_moved  || king->y != y || (x != 2 && x != 6))
    return 0;
  PIECE * rook = game->board[king->y][x == 2 ? 0 : 7];
  if(!rook || rook->has_moved)
    return 0;
  int x_dir = (- (king->x - x) / abs(king->x - x));
  if(is_blocked_py_piece(game, king, x, y, x_dir, 0))
    return 0;
  if(is_location_attacked(game, king->side ? Black : White, x + x_dir, y) || is_location_attacked(game, king->side ? Black : White, x + (x_dir * 2), y))
    return 0;
  return rook->x + 1;
}
int is_valid_move_king(GAME * game, PIECE * piece, int x, int y){
  if(abs(piece->x - x) > 1 || abs(piece->y - y) > 1)
    return is_valid_castle(game, piece, x, y);
  PIECE * new_pos = game->board[y][x];
  game->board[y][x] = game->board[piece->y][piece->x] = 0;
  int r = !is_location_attacked(game, !piece->side, x, y);
  game->board[piece->y][piece->x] = piece;
  game->board[y][x] = new_pos;
  return r;
}
int is_valid_move(GAME * game, PIECE * piece, int x, int y){
  if(x == -1 || x == 8 || y == -1 || y == 8)
    return 0;
  if(piece->x == x && piece->y == y)
    return 0;
  if(game->board[y][x] && game->board[y][x]->side == piece->side)
    return 0;
  switch(piece->type){
  case Pawn:
    return is_valid_move_pawn(game, piece, x, y);
  case Knight:
    return is_valid_move_knight(game, piece, x, y);
  case Bishop:
    return is_valid_move_bishop(game, piece, x, y);
  case Rook:
    return is_valid_move_rook(game, piece, x, y);
  case Queen:
    return is_valid_move_rook(game, piece, x, y) || is_valid_move_bishop(game, piece, x, y);
  case King:
    return is_valid_move_king(game, piece, x, y);
  }
  return 0;
}
