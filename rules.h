int is_location_attacked(GAME * game, SIDE by_side, int x, int y);

int in_check(GAME * game, SIDE side);
int in_draw(GAME * game);

int is_blocked_py_piece(GAME * game, PIECE * piece, int x, int y, int x_dir, int y_dir);

int is_valid_move_pawn(GAME * game, PIECE * piece, int x, int y);
int is_valid_move_knight(GAME * game, PIECE * piece, int x, int y);
int is_valid_move_bishop(GAME * game, PIECE * piece, int x, int y);
int is_valid_move_rook(GAME * game, PIECE * piece, int x, int y);

int is_valid_castle(GAME * game, PIECE * king, int x, int y);
int is_valid_move_king(GAME * game, PIECE * piece, int x, int y);

int is_valid_move_for_piece(GAME * game, PIECE * piece, int x, int y);
int is_valid_move(GAME * game, PIECE * piece, int x, int y);



