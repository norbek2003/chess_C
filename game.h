int is_valid_move(struct game * game, struct piece * piece, int x, int y);
void move(struct game * game, struct piece * piece, int x, int y);
char piece_symbol(struct piece * piece);
void print_piece(struct piece * piece);
void print_board(struct game * game);
void generate_pieces(struct side * side);
struct game * generate_game();

