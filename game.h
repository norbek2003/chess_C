void move_piece(GAME * game, PIECE * piece, int x, int y);
int attempt_piece_move(GAME * game, PIECE * piece, int x, int y);

void get_move_from_stdin(int * move);

char piece_symbol(PIECE * piece);
void print_piece(PIECE * piece);

void print_board_base(GAME * game, int col_inc, char * row);
void print_board(GAME * game);
void print_board_debug(GAME * game);

void generate_pieces(struct side * side);
GAME * generate_game();
void print_location(int x, int y);
void play_game();
