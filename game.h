typedef enum {Pawn, Bishop, Knight, Rook, Queen, King} PIECE_TYPE;
typedef enum {White, Black} SIDE;

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
  struct piece * board[8][8];
};
  

#define RESET "\x1b[0m"
#define B_WHITE "\033[107m"
#define B_BLACK "\033[40m"
#define B_GREEN "\033[42m"
