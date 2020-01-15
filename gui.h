#include "networking.h"
#include "chess_base.h"

struct gui_data;
typedef struct{
  int x;
  int y;
  struct gui_data * gui_data;
} POSITION;
typedef struct gui_data{
  GAME * game;
  POSITION * selected_piece;
  GtkWidget * grid[8][8];
  GtkWidget * window;
  SIDE side;
  int server_socket;
  int listener;
  GtkWidget * captured_piece_displays[2];
} GUI_DATA;


void myCSS(void);

char * piece_symbol_unicode(PIECE * piece);

void update_board(GUI_DATA * data);

void button_press (GtkWidget *widget, gpointer data);

void activate (GtkApplication *app, gpointer gdata);
