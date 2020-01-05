int is_valid_move(GAME * game, PIECE * piece, int x, int y);
void move_piece(GAME * game, PIECE * piece, int x, int y);
char piece_symbol(PIECE * piece);
void print_piece(PIECE * piece);
void print_board(GAME * game);
void generate_pieces(struct side * side);
GAME * generate_game();

