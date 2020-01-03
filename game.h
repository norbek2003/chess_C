

typedef enum {Pawn, Bishop, Knight, Rook, Queen, King} PIECE_TYPE;
typedef enum {White, Black} SIDE;
typedef char BOARD[8][8];

struct piece {
  PIECE_TYPE type;
  SIDE side;
  int x;
  int y;
  int captured;
};
struct side {
  struct piece * pieces[16];
  SIDE side;
};
struct game {
  struct side * sides[2];
};
  
