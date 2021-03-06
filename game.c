#include "chess_base.h"
void move_piece(GAME * game, PIECE * piece, int x, int y){
  game->board[piece->y][piece->x] = 0;
  game->board[y][x] = piece;
  piece->x = x;
  piece->y = y;
}
MOVE * generate_move(){
  MOVE * m = malloc(sizeof(MOVE));
  m->next_move = NULL;
  m->moved_piece = NULL;;
  m->captured_piece = NULL;
  m->notation[0] = 0;
  return m;
}
void add_move(GAME * game, PIECE * piece, PIECE * captured_piece, int orig_x, int orig_y, int x, int y, int move_status){
  MOVE * move = game->moves;
  while(move->next_move){
    move = move->next_move;
  }
  move->from_x = orig_x;
  move->from_y = orig_y;
  move->to_x = x;
  move->to_y = y;
  move->moved_piece = piece;
  move->captured_piece = captured_piece;
  move->next_move = generate_move();
  int p = 0;
  if(move_status > 1){
    strcpy(move->notation, move_status == 2 ? "O-O-O  " : "O-O    ");
  }else{
    memset(move->notation, ' ', 8);
    move->notation[p++] = "PBNRQK"[piece->type];
    move->notation[p++] = "ABCDEFGH"[orig_x];
    move->notation[p++] = "12345678"[orig_y];
    if(captured_piece){
      move->notation[p++] = 'x';
      move->notation[p++] = "PBNRQK"[captured_piece->type];
    }
    move->notation[p++] = "ABCDEFGH"[x];
    move->notation[p++] = "12345678"[y];

    move->notation[7] = 0;
  }
}
int attempt_piece_move(GAME * game, PIECE * piece, int x, int y){
  if(!piece || piece->side != game->turn)
    return 0;
  int orig_x = piece->x;
  int orig_y = piece->y;
  int is_valid = is_valid_move(game, piece, x, y);
  if(!is_valid)
    return 0;
  PIECE * captured = game->board[y][x];
  if(captured)
    captured->captured = 1;
  move_piece(game, piece, x, y);
  piece->has_moved = 1;
  if(is_valid > 1){ // Castle
    int x_dir = (- (orig_x - x) / abs(orig_x - x));
    move_piece(game, game->board[y][is_valid - 2], x - x_dir, y);
  }
  add_move(game, piece, captured, orig_x, orig_y, x, y, is_valid);
  return is_valid;
}
void get_move_from_stdin(int * move){
  while(!(-1 < move[0] && move[0] < 8 && -1 < move[1] && move[1] < 8 && -1 < move[2] && move[2] < 8 && -1 < move[3] && move[3] < 8)){
    printf("Please input move->");
    char *buffer = NULL;
    int read;
    size_t len;
    read = getline(&buffer, &len, stdin);
    move[0] = toupper(buffer[0]) - 65;
    move[1] = toupper(buffer[1]) - 49;
    move[2] = toupper(buffer[2]) - 65;
    move[3] = toupper(buffer[3]) - 49;
    //printf("%d %d %d %d\n", move[0], move[1], move[2], move[3]);
  }
  printf("\n");
}
char piece_symbol(PIECE * piece){
  if(!piece)
    return ' ';
  return (piece->side ? "pbnrqk":"PBNRQK")[piece->type];
}
void print_piece(PIECE * piece){
  printf("%c", piece_symbol(piece));
}
void print_board_base(GAME * game, int col_inc, char * row){
  for(int y = 7; y >= 0; y--){
    printf("%d ", y + col_inc);
    for(int x = 0; x < 8; x++){
      char * background = (((x + 1) % 2 && (y + 1) % 2) || (x % 2 && y % 2)) ? B_GREEN : B_WHITE;
      printf("\033[30m%s %c " "\033[0m", background, piece_symbol(game->board[y][x]));
    }
    printf("\n");
  }
  printf("%s", row);
}
void print_board(GAME * game){
  print_board_base(game, 1, "   A  B  C  D  E  F  G  H \n");
}
void print_board_debug(GAME * game){
  print_board_base(game, 0, "   0  1  2  3  4  5  6  7 \n");
}
void generate_pieces(struct side * side){
  int i = 0;
  for(int i = 0; i < 16; i++){
    side->pieces[i] = malloc(sizeof(PIECE));
    side->pieces[i]->captured = 0;
    side->pieces[i]->has_moved = 0;
    side->pieces[i]->side = side->side;
  }
  for(int i = 0; i < 8; i++){
    side->pieces[i]->type = Pawn;
    side->pieces[i]->y = side->side ? 6 : 1;
    side->pieces[i]->x = i;
  }
  int start = side->side ? 7 : 0;
  int y = start;
  PIECE_TYPE types[] = {Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook};
  for(int i = 8; i < 16; i++){
    side->pieces[i]->type = types[i - 8];
    side->pieces[i]->y = y;
    side->pieces[i]->x = i - 8;
    if(types[i - 8] == King){
      side->king = side->pieces[i];
    }
  }
}
GAME * generate_game(){
  GAME *game = malloc(sizeof(GAME));
  for(int side = 0; side < 2; side++){
    game->sides[side] = malloc(sizeof(struct side));
    game->sides[side]->side = side;
    generate_pieces(game->sides[side]);
  }
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      game->board[y][x] = 0;
    }
  }
  for(int side = 0; side < 2; side ++){
    for(int i = 0; i < 16; i ++){
      PIECE * piece = game->sides[side]->pieces[i];
      game->board[piece->y][piece->x] = piece;
      game->pieces[side * 16 + i] = piece;
    }
  }
  game->moves = generate_move();
  game->turn = White;
  return game;
}
void print_location(int x, int y){
  printf("%c%d", "ABCDEFGH"[x], y);
}

void play_game(){
  GAME * game = generate_game();
  printf("=====Play Chess============\n");
  print_board(game);
  int move [4] = {-1, -1, -1, -1};
  while(1){
    printf("%s TO MOVE\n", game->turn ? "BLACK" : "WHITE");
    get_move_from_stdin(move);
    if(attempt_piece_move(game, game->board[move[1]][move[0]], move[2], move[3])){
      game->turn = !game->turn;
      print_board(game);
    }
    memset(move, -1, 4);
    if(in_draw(game, game->turn)){
      if(in_check(game, game->turn)){
	printf("%s WINS!\n", game->turn ? "WHITE" : "BLACK");
	return;
      }
      printf("DRAW. \n");
      return;
    }
  }
}
