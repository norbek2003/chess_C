#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

typedef enum {Pawn, Bishop, Knight, Rook, Queen, King} PIECE_TYPE;
typedef enum {White, Black} SIDE;

typedef struct piece {
  PIECE_TYPE type;
  SIDE side;
  int x;
  int y;
  int captured;
  int has_moved;
} PIECE;

typedef struct move {
  int from_x;
  int from_y;
  int to_x;
  int to_y;
  PIECE * moved_piece;
  PIECE * captured_piece;
  struct move * next_move;
  char notation[8];
} MOVE;

struct side {
  PIECE * pieces[16];
  PIECE * king;
  SIDE side;
};
typedef struct game{
  struct side * sides[2];
  PIECE * board[8][8];
  PIECE * pieces[32];
  SIDE turn;
  MOVE * moves;
} GAME;

#define RESET "\x1b[0m"
#define B_WHITE "\033[107m"
#define B_BLACK "\033[40m"
#define B_GREEN "\033[42m"
#define ROW "ABCDEFGH"

#include "game.h"
#include "rules.h"
