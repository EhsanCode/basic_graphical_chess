
// chess game
// 79/1/27  2000-04-15
/*****************************************************************************
	  AUTHORS::
		   EHSAN AMINI                  SI=(77323287)
				   &&
		   KAYVAN HAJ HASSAN TEHRANI    SI=(77323358)
*******************************************************************************/
#include <stdio.h>
#include <iostream.h>
#include <iomanip.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream.h>
#include <STRING.H>
#include <dos.h>
#include <graphics.h>

#define X x * 50 + board_x
#define Y y * 50 + board_y

void display_init(void)
{
	int gdriver = DETECT;
	int gmode, errorcode;
	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();
	if (errorcode != grOk) /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}
}
int check_keyboard(void);

class Queue;
class Eleman_q
{
	friend class Queue;
	Eleman_q *back;
	int x[4];

public:
	Eleman_q(void)
	{
		back = NULL;
	}
};

class Queue
{
	struct Eleman_q *top, *last;

public:
	void add(int *);
	int del(int *);
	int is_empte(void)
	{
		if (top == NULL)
			return 1;
		return 0;
	}
	Queue(void)
	{
		top = NULL;
		last = NULL;
	}
	~Queue(void);
};
void Queue::add(int *x)
{
	Eleman_q *p;
	p = new Eleman_q;
	p->x[0] = x[0];
	p->x[1] = x[1];
	p->x[2] = x[2];
	p->x[3] = x[3];
	if (is_empte())
	{
		top = p;
		last = p;
		return;
	}
	last->back = p;
	last = p;
	return;
}
int Queue::del(int *x)
{
	Eleman_q *s;
	if (is_empte() == 1)
		return 0;
	x[0] = top->x[0];
	x[1] = top->x[1];
	x[2] = top->x[2];
	x[3] = top->x[3];
	s = top->back;
	delete top;
	top = s;
	return 1;
}
Queue::~Queue(void)
{
	int x[4];
	while (!is_empte())
		del(x);
}
class Piece;
class Stack;
class Eleman_s
{
	friend class Stack;
	Eleman_s *back;
	int x1, x2, y1, y2;
	Piece *piece;

public:
	Eleman_s(void)
	{
		back = NULL;
	}
};
/*___________________________________________________________________________
			A Stack for keeping moves
_____________________________________________________________________________*/
class Stack
{
	struct Eleman_s *top;
	int count;

public:
	void add(int, int, int, int, Piece *);
	int del(int &, int &, int &, int &, Piece **);
	int counter(void)
	{
		return (count);
	}
	Stack(void)
	{
		top = NULL;
		count = 0;
	}
	~Stack(void);
};
void Stack::add(int x1, int y1, int x2, int y2, Piece *p)
{
	Eleman_s *s;
	s = top;
	top = new Eleman_s;
	top->x1 = x1;
	top->x2 = x2;
	top->y1 = y1;
	top->y2 = y2;
	top->piece = p;
	top->back = s;
	if (p != NULL)
		count++;
}
int Stack::del(int &x1, int &y1, int &x2, int &y2, Piece **p)
{
	int x;
	Eleman_s *s;
	if (top == NULL)
		return 0;
	x1 = top->x1;
	x2 = top->x2;
	y1 = top->y1;
	y2 = top->y2;
	*p = top->piece;
	s = top->back;
	delete top;
	top = s;
	if (*p != NULL)
		count--;
	return 1;
}
Stack::~Stack(void)
{
	int a1, a2, a3, a4;
	Piece *p;
	while (del(a1, a2, a3, a4, &p))
		;
}

/*_______________________________________________________________________________
			   A class for  making Piece's object
_________________________________________________________________________________*/
class Piece
{
private:
protected:
	int x, y, color_piece, first_mov;

public:
	Piece(void)
	{
	}
	Piece(int a, int b, int c) : x(a), y(b), color_piece(c)
	{
		first_mov = 0;
	}
	virtual int move(int x1, int y1)
	{
		x1 = x1 + 1 - 1; // for warning
		y1 = y1 + 1 - 1; // for warning
		return 3;
	}
	int first_move(void)
	{
		return first_mov;
	}
	void dec_move(int x1, int y1)
	{
		first_mov--;
		x = x1;
		y = y1;
	}
	int color(void)
	{
		return (color_piece);
	}
	virtual char type(void)
	{
		return ' ';
	}
	void location(int &x1, int &y1)
	{
		x1 = x;
		y1 = y;
	}
};
/*___________________________________________________________________________
				KING PIECE
_____________________________________________________________________________*/
class king : public Piece
{
public:
	king(int a, int b, int c) : Piece(a, b, c)
	{
	}
	int move(int x, int y)
	{
		int x1 = abs(x - Piece::x), y1 = abs(y - Piece::y);
		if ((x1 <= 1) && (y1 <= 1))
		{
			Piece::x = x;
			Piece::y = y;
			Piece::first_mov++;
			return (1);
		}
		else if (Piece::first_mov == 0 && (y1 == 2) && (x1 == 0))
		{
			Piece::x = x;
			Piece::y = y;
			Piece::first_mov++;
			return (1);
		}
		return (0);
	}
	char type(void)
	{
		return 'K';
	}
};
/*___________________________________________________________________________
				  KNIGHT  PIECE
_____________________________________________________________________________*/

class knight : public Piece
{

public:
	knight(int a, int b, int c) : Piece(a, b, c)
	{
	}
	int move(int x, int y)
	{
		Piece::x = x;
		Piece::y = y;
		return 1;
	}
	char type(void)
	{
		return 'N';
	}
};
/*___________________________________________________________________________
			   BISHOP PIECE
_____________________________________________________________________________*/

class bishop : public Piece
{

public:
	bishop(int a, int b, int c) : Piece(a, b, c)
	{
	}
	int move(int x, int y)
	{
		Piece::x = x;
		Piece::y = y;
		return 1;
	}
	char type(void)
	{
		return 'B';
	}
};

/*___________________________________________________________________________
				 ROOK  PIECE
_____________________________________________________________________________*/

class rook : public Piece
{
public:
	rook(int a, int b, int c) : Piece(a, b, c)
	{
	}
	int move(int x, int y)
	{
		Piece::x = x;
		Piece::y = y;
		Piece::first_mov++;
		return 1;
	}
	char type(void)
	{
		return 'R';
	}
};
/*___________________________________________________________________________
				 PIECE
_____________________________________________________________________________*/

class queen : public Piece
{
public:
	queen(int a, int b, int c) : Piece(a, b, c)
	{
	}
	int move(int x, int y)
	{
		Piece::x = x;
		Piece::y = y;
		return 1;
	}
	char type(void)
	{
		return 'Q';
	}
};
/*___________________________________________________________________________
				   PAWN  PIECE
_____________________________________________________________________________*/

class pawn : public Piece
{
public:
	pawn(int a, int b, int c) : Piece(a, b, c)
	{
	}
	int move(int x, int y)
	{
		Piece::x = x;
		Piece::y = y;
		Piece::first_mov++;
		return (1);
	}

	char type(void)
	{
		return 'P';
	}
};
class Display_chess_board;
class Graphic;
/*______________________________________________________________________________

_________________________________________________________________________________*/
class Text_bar
{
	friend class Graphic;
	char p[8];
	int text_bar_normal_text, text_bar_mark_char, text_bar_color;
	int back_menu_color;
	int mark_menu_option_color;
	static int text_bar_mark_num;
	void text_bar_config(void);

public:
	Text_bar(void);
	void graph_text_bar(int mark = 0);
	int Text_bar::graph_menu_of_mark_text_bar(int, int, int, char **, int expanse_num = 0);
};
int Text_bar::text_bar_mark_num = 0;
Text_bar::Text_bar(void)
{
	text_bar_config();
}
void Text_bar::text_bar_config(void)
{
	for (int i = 0; i < 8; i++)
		p[i] = 255;
	text_bar_normal_text = 10;
	text_bar_mark_char = 4;
	text_bar_color = 13;
	back_menu_color = 9;
	mark_menu_option_color = 0;
}
void Text_bar::graph_text_bar(int mark)
{
	if (mark != 5)
		text_bar_mark_num = mark;
	setcolor(15);
	rectangle(0, 0, 639, 23);
	setfillpattern(p, text_bar_color);
	floodfill(2, 2, 15);
	line(48, 0, 48, 23);
	line(130, 0, 130, 23);
	line(208, 0, 208, 23);
	line(261, 0, 261, 23);
	floodfill(50, 2, 15);
	floodfill(135, 2, 15);
	floodfill(215, 2, 15);
	settextstyle(1, 0, 1);
	setcolor(text_bar_mark_char);
	outtextxy(0, 0, " F");
	outtextxy(47, 0, " O");
	outtextxy(129, 0, " D");
	outtextxy(207, 0, " H");
	setcolor(text_bar_normal_text);
	outtextxy(2, 0, "  ile ");
	outtextxy(49, 0, "  ptions ");
	outtextxy(132, 0, "  isplay ");
	outtextxy(212, 0, "  elp ");
	if (mark)
		switch (text_bar_mark_num)
		{
		case 1:
			setfillpattern(p, 0);
			floodfill(2, 2, 15);
			setcolor(text_bar_mark_char);
			outtextxy(0, 0, " F");
			setcolor(text_bar_normal_text);
			outtextxy(2, 0, "  ile ");
			break;
		case 2:
			setfillpattern(p, 0);
			floodfill(50, 2, 15);
			setcolor(text_bar_mark_char);
			outtextxy(47, 0, " O");
			setcolor(text_bar_normal_text);
			outtextxy(49, 0, "  ptions ");
			break;
		case 3:
			setfillpattern(p, 0);
			floodfill(135, 2, 15);
			setcolor(text_bar_mark_char);
			outtextxy(129, 0, " D");
			setcolor(text_bar_normal_text);
			outtextxy(132, 0, "  isplay ");
			break;
		case 4:
			setfillpattern(p, 0);
			floodfill(215, 2, 15);
			setcolor(text_bar_mark_char);
			outtextxy(207, 0, " H");
			setcolor(text_bar_normal_text);
			outtextxy(212, 0, "  elp ");
			break;
		}
}
int Text_bar::graph_menu_of_mark_text_bar(int left, int width, int num_options, char *text_options[], int expanse_num)
{
	int choice = -1;
	char ch = 'x';
	int x_max, y_max;
	int bottom = num_options * 18 + 23;
	int top = 23, riget = left + width;
	int back_menu_color = 9;
	int mark_menu_option_color = 0;
	setcolor(15);
	void *buf;
	static void *buf_last, *buf_last_menu;
	static int left_last = left, top_last = top;
	int size;
	if (expanse_num)
	{
		top += ((expanse_num - 1) * 18) + 9;
		putimage(left_last, top_last, buf_last_menu, 0);
	}
	bottom = num_options * 18 + top;
	x_max = getmaxx();
	y_max = getmaxy();
	size = imagesize(left, top, riget, bottom);
	if (size != -1)
	{
		buf = malloc(size);
		if (buf)
			getimage(left, top, riget, bottom, buf);
	}
	setviewport(left, top, riget, bottom, 1);
	clearviewport();
	setcolor(15);
	rectangle(0, 0, riget - left, bottom - top);
	setfillpattern(p, back_menu_color);
	floodfill(2, 2, 15);
	settextstyle(0, 0, 1);
	for (int i = 0; i < num_options; i++)
	{
		setcolor(15);
		line(0, (i + 1) * 18, width, (i + 1) * 18);
		if (text_options[i][0] == '-')
			setcolor(8);
		else if (text_options[i][0] == '+')
		{
			setfillpattern(p, 10);
			floodfill(8, 9 + (18 * i), 15);
			setcolor(13);
		}
		else
		{
			setcolor(14);
			choice = i;
		}
		outtextxy(8, 6 + (18 * i), 1 + text_options[i]);
	}
	if (choice == -1)
		getch();
	else
	{
		while (!(ch == 27 || ch == 13))
		{
			ch = getch();
			if (ch == 0)
			{
				setcolor(14);
				setfillpattern(p, back_menu_color);
				floodfill(2, 2 + ((choice)*18), 15);
				outtextxy(8, 6 + (18 * choice), 1 + text_options[choice]);
				switch (getch())
				{
				case 80:
					choice = (++choice) % (num_options);
					while (text_options[choice][0] == '-' || text_options[choice][0] == '+')
						choice = (++choice) % (num_options);
					break;
				case 72:
					int choice_help;
					--choice;
					if (choice < 0)
						choice = num_options - 1;
					choice_help = choice;
					while (text_options[choice_help][0] == '-' || text_options[choice][0] == '+')
					{
						choice = (--choice) % (num_options);
						if (choice < 0)
							choice_help = num_options - abs(choice);
						else
							choice_help = choice;
					}
					choice = choice_help;
					break;
				}
				setfillpattern(p, mark_menu_option_color);
				floodfill(2, 2 + ((choice)*18), 15);
				outtextxy(8, 6 + (18 * choice), 1 + text_options[choice]);
			}
		}
	}
	setviewport(0, 0, x_max, y_max, 1);
	free(buf_last_menu);
	size = imagesize(left, top, riget, bottom);
	if (size != -1)
	{
		buf_last_menu = malloc(size);
		if (buf_last_menu)
			getimage(left, top, riget, bottom, buf_last_menu);
	}
	if (expanse_num)
	{
		// cout<<"putimage(left_last,top_last,buf_last,0);";
		putimage(left_last, top_last, buf_last, 0);
	}
	// cout<<"putimage(left,top,buf,0);";
	putimage(left, top, buf, 0);
	free(buf_last);
	free(buf);
	size = imagesize(left, top, riget, bottom);
	if (size != -1)
	{
		buf_last = malloc(size);
		if (buf_last)
			getimage(left, top, riget, bottom, buf_last);
	}
	left_last = left;
	top_last = top;
	if (ch == 13)
		return (choice + 1);
	return 0;
}
/*______________________________________________________________________________

_________________________________________________________________________________*/
class Config
{
	friend class Play;
	Text_bar text_bar;
	char *options_menu_txet[10];
	char *options_plus_menu_txet[10];
	char *file_menu_txet[10];
	char *display_menu_txet[10];
	char tern_of_move;
	char operations_elective;
	int exit;

public:
	Config(void);
	int config_check(char key = '\0');
	void ch_exit(void)
	{
		exit = 0;
	}
};
// char Config::*options_menu_txet[]={" Undo "};
// char Config::*file_menu_txet[]={"-Load","-Save"," Exit  Alt+x"};
/*______________________________________________________________________________

_________________________________________________________________________________*/
Config::Config(void)
{
	int i, len;
	char *options_menu_txet_make[] = {"-Undo ", " Permitted move", " Logically moves ...", " Random moves ..."};
	for (i = 0; i < 4; i++)
	{
		len = strlen(options_menu_txet_make[i]);
		options_menu_txet[i] = new char[len + 1];
		strcpy(options_menu_txet[i], options_menu_txet_make[i]);
	}
	char *file_menu_txet_make[] = {" Load", "-Save", " New game", " Exit  Alt+x"};
	for (i = 0; i < 4; i++)
	{
		len = strlen(file_menu_txet_make[i]);
		file_menu_txet[i] = new char[len + 1];
		strcpy(file_menu_txet[i], file_menu_txet_make[i]);
	}
	char *options_plus_menu_txet_make[] = {"+  White    Black", " User     Computer", " Computer     User", " Computer Computer", " User         User"};
	for (i = 0; i < 5; i++)
	{
		len = strlen(options_plus_menu_txet_make[i]);
		options_plus_menu_txet[i] = new char[len + 1];
		strcpy(options_plus_menu_txet[i], options_plus_menu_txet_make[i]);
	}
	char *display_menu_txet_make[] = {" Revival display", "-Colors", " ", " "};
	for (i = 0; i < 2; i++)
	{
		len = strlen(display_menu_txet_make[i]);
		display_menu_txet[i] = new char[len + 1];
		strcpy(display_menu_txet[i], display_menu_txet_make[i]);
	}
	tern_of_move = 'u';
	operations_elective = 'l';
	exit = 1;
}
/*______________________________________________________________________________

_________________________________________________________________________________*/
int Config::config_check(char key)
{
	union REGS in, out;
	if (!exit)
		return 0;
	if (key == 27)
		text_bar.graph_text_bar(0);
	in.h.ah = 2;
	int86(0x16, &in, &out);
	if ((out.h.al & 8) == 8)
	{
		text_bar.graph_text_bar(5);
		key = getch();
		if (key == 0)
			key = getch();
		/*
		for (int i=0;i<3;i++)
		{
		 puts(file_menu_txet[i]);
		 getch();
		}
		*/
		switch (key)
		{
		case 'x':
		case 'X':
		case 45:
			exit = 0;
			return 0;
			break;
		case 'f':
		case 'F':
		case 33:
			text_bar.graph_text_bar(1);
			switch (text_bar.graph_menu_of_mark_text_bar(0, 100, 4, file_menu_txet))
			{
			case 1:
				operations_elective = 'v';
				return 1;
				break;
			case 2:
				//    ??  <<==
				break;
			case 3:
				operations_elective = 'n';
				return 1;
				break;
			case 4:
				operations_elective = 'q';
				exit = 0;
				return 0;
				break;
			}
			text_bar.graph_text_bar(0);
			return -1;
			break;
		case 'o':
		case 'O':
		case 24:
			text_bar.graph_text_bar(2);
			switch (text_bar.graph_menu_of_mark_text_bar(48, 160, 4, options_menu_txet))
			{
			case 1:
				operations_elective = 'u'; // Undo
				break;
			case 2:
				operations_elective = 'p';
				break;
			case 3:
				operations_elective = 'l';
				switch (text_bar.graph_menu_of_mark_text_bar(208, 148, 5, options_plus_menu_txet, 3))
				{
				case 2:
					tern_of_move = 'b';
					break;
				case 3:
					tern_of_move = 'w';
					break;
				case 4:
					tern_of_move = 'c';
					break;
				case 5:
					tern_of_move = 'u';
					break;
				}
				break;
			case 4:
				operations_elective = 'r';
				switch (text_bar.graph_menu_of_mark_text_bar(208, 148, 4, options_plus_menu_txet, 4))
				{
				case 2:
					tern_of_move = 'b';
					break;
				case 3:
					tern_of_move = 'w';
					break;
				case 4:
					tern_of_move = 'c';
					break;
				}
				break;
			}
			text_bar.graph_text_bar(0);
			return -1; //   <<==
			break;
		case 'd':
		case 'D':
		case 32:
			text_bar.graph_text_bar(3);
			switch (text_bar.graph_menu_of_mark_text_bar(130, 136, 2, display_menu_txet))
			{
			case 1:
				operations_elective = 'd';
				break;
			case 2:
				/*	switch(text_bar.graph_menu_of_mark_text_bar(208,148,4,display_plus_menu_txet,2))
				   {
					case 2:

					break;
					case 3:

					break;
					case 4:

					break;
				   }
			*/ break;
			}
			text_bar.graph_text_bar(0);
			return -1; //   <<==
			break;
		case 'h':
		case 'H':
		case 35:
			text_bar.graph_text_bar(4);
			//    ??  <<==
			break;
		}
	}
	return 1;
}
/*_________________________________________________________________________________

___________________________________________________________________________________*/
class Graphic
{
	Config config;
	Text_bar text_bar;
	char p[8];
	void *buf_black, *buf_white, *buf_masseg;
	int graph_en;
	int black_home_color, white_home_color;
	int black_piece_color, white_piece_color, line_board_color;
	int background_color, text_color;
	int pointer_x, pointer_y;
	int set_pointer_x, set_pointer_y;
	int board_x, board_y;
	int far *high, *low;
	int set_piece_color(int color);

public:
	void graph_enabel(int);
	void color_config(void);
	void set_graphic_bufer(void);
	void clean_home(int, int);
	void graph_board(void);
	void graph_piece_in_board(int, int, char, int);
	void graph_pointer(int, int, int, int set = 0);
	void graph_pawn(int, int, int);
	void graph_rook(int, int, int);
	void graph_bishop(int, int, int);
	void graph_queen(int, int, int);
	void graph_knight(int, int, int);
	void graph_king(int, int, int);
	int graph_change_pawn(int color = 1);
	void end_out_move_adress_in_graphic_board(char *);
	void out_masseg_in_graphic_board(char *);
	void end_out_masseg_in_graphic_board(void);
	Graphic(void);
	~Graphic(void);
};

Graphic::Graphic(void)
{
	for (int i = 0; i < 8; i++)
		p[i] = 255;
	// clrscr();
	color_config();
	graph_en = 1;
	pointer_x = 0;
	pointer_y = 0;
	set_pointer_x = set_pointer_y = -1;
	set_graphic_bufer();
	/*
	int gdriver = DETECT;
	int gmode,errorcode;
	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	/*	  {
		  printf("Graphics error: %s\n", grapherrormsg(errorcode));
		  printf("Press any key to halt:");
		  getch();
		  exit(1); /* terminate with an error code */
	//	  }
	setbkcolor(0);
	setfillpattern(p, background_color);
	floodfill(1, 1, 1);
}
Graphic::~Graphic(void)
{
	free(buf_white);
	free(buf_black);
	restorecrtmode();
	closegraph();
}
void Graphic::graph_enabel(int en)
{
	graph_en = en;
}

void Graphic::color_config(void)
{
	black_home_color = 6;
	white_home_color = 7;
	line_board_color = 15;
	black_piece_color = 0;
	white_piece_color = 15;
	background_color = 3;
	text_color = 12;
	board_x = 50;
	board_y = 20;
}
void Graphic::set_graphic_bufer(void)
{
	int size;
	setbkcolor(0);
	cleardevice();
	setcolor(15);
	rectangle(0, 0, 52, 52);
	setfillpattern(p, black_home_color);
	floodfill(3, 3, 15);
	size = imagesize(1, 1, 48, 48);
	if (size != -1)
	{
		buf_black = malloc(size);
		if (buf_black)
		{
			getimage(1, 1, 48, 48, buf_black);
			putimage(200, 200, buf_black, 0);
		}
	}
	setbkcolor(0);
	cleardevice();
	setcolor(15);
	rectangle(0, 0, 52, 52);
	setfillpattern(p, white_home_color);
	floodfill(3, 3, 15);
	size = imagesize(1, 1, 48, 48);
	if (size != -1)
	{
		buf_white = malloc(size);
		if (buf_white)
		{
			getimage(1, 1, 48, 48, buf_white);
			putimage(200, 200, buf_white, 0);
		}
	}
}

void Graphic::clean_home(int x, int y)
{
	if (!graph_en)
		return;
	if (((x + y + 2) % 2) == 0)
		putimage(Y + 1, X + 1, buf_white, 0);
	else
		putimage(Y + 1, X + 1, buf_black, 0);
}
int Graphic::set_piece_color(int color)
{
	if (color != 1)
	{
		setcolor(black_piece_color);
		setfillpattern(p, white_piece_color);
		return black_piece_color;
	}
	setcolor(white_piece_color);
	setfillpattern(p, black_piece_color);
	return white_piece_color;
}

void Graphic::graph_board(void)
{
	int i, j;
	cleardevice();
	setfillpattern(p, background_color);
	floodfill(1, 1, 1);
	text_bar.graph_text_bar(5);
	setcolor(line_board_color);
	settextstyle(1, 0, 2);
	for (i = 0; i < 8; i++)
	{
		char ch = i + 'a';
		outtextxy(board_y + i * 50 + 21, board_x + 400, &ch);
		ch = '8' - i;
		outtextxy(board_y - 15, board_x + i * 50 + 15, &ch);
	}
	rectangle(board_y, board_x, 400 + board_y, 400 + board_x);
	for (i = 50; i <= 400; i += 50)
	{
		line(0 + board_y, i + board_x, 400 + board_y, i + board_x);
		line(i + board_y, 0 + board_x, i + board_y, 400 + board_x);
	}
	for (j = 2; j < 400; j += 50)
		for (i = 10 + j; i < 400; i += 100)
		{
			setfillpattern(p, white_home_color);
			floodfill(j + board_y, i + board_x, line_board_color);
			floodfill(i + board_y, j + board_x, line_board_color);
			if ((i + 50) < 400)
			{
				setfillpattern(p, black_home_color);
				floodfill(j + board_y, i + board_x + 50, line_board_color);
				floodfill(i + 50 + board_y, j + board_x, line_board_color);
			}
		}
	settextstyle(0, 0, 1);
	setcolor(8);
	outtextxy(board_y + 400, board_x, " >       EHSAN AMINI");
	outtextxy(board_y + 400, board_x + 20, " >KAYVAN HAJ HASSAN TEHRANI");
	settextstyle(4, 1, 8);
	setcolor(5);
	outtextxy(board_y + 500, board_x + 4, " MAYBOD ");
	/*
	 void *buf;
	 unsigned size;
	 size=imagesize(0,0,200,200);
	 if (size!=-1)
		{
		 buf=malloc(size);
		 if (buf)
			{
			 getimage(0,0,200,200,buf);
			 putimage(240,240,buf,0);
			}
		}
	*/
}
void Graphic::graph_piece_in_board(int x, int y, char piece, int color)
{
	if (!graph_en)
		return;
	clean_home(x, y);
	if (color == -1)
		color = 0;
	switch (piece)
	{
	case 'P':
		graph_pawn(x, y, color);
		break;
	case 'R':
		graph_rook(x, y, color);
		break;
	case 'B':
		graph_bishop(x, y, color);
		break;
	case 'Q':
		graph_queen(x, y, color);
		break;
	case 'N':
		graph_knight(x, y, color);
		break;
	case 'K':
		graph_king(x, y, color);
		break;
	}
}
int Graphic::graph_change_pawn(int color)
{
	int color_p;
	int i, m = 0;
	int piece_y = 2;
	char key = 'x';
	if (color == -1)
		color = 0;
	void *buf;
	unsigned size;
	size = imagesize(board_y + 400, board_x + 100, board_y + 450, board_x + 300);
	if (size != -1)
	{
		buf = malloc(size);
		if (buf)
			getimage(board_y + 400, board_x + 100, board_y + 450, board_x + 300, buf);
	}
	setcolor(line_board_color);
	rectangle(board_y + 400, board_x + 100, board_y + 450, board_x + 300);
	for (i = 150; i <= 300; i += 50)
		line(board_y + 400, board_x + i, board_y + 450, board_x + i);
	for (i = 125; i <= 225; i += 100)
	{
		setfillpattern(p, white_home_color);
		floodfill(board_y + 425, board_x + i, line_board_color);
		setfillpattern(p, black_home_color);
		floodfill(board_y + 425, board_x + i + 50, line_board_color);
	}
	graph_queen(2, 8, color);
	graph_rook(3, 8, color);
	graph_bishop(4, 8, color);
	graph_knight(5, 8, color);
	graph_pointer(2, 8, !color);
	while (key != '\r')
	{
		while (m != 1)
		{
			m = check_keyboard();
			if (m == 2)
				config.config_check();
		}
		key = getch();
		config.config_check(key);
		if (key == 0)
		{
			key = getch();
			switch (key)
			{
			case 80:
				if (piece_y < 5)
					graph_pointer(++piece_y, 8, !color);
				break;
			case 72:
				if (piece_y > 2)
					graph_pointer(--piece_y, 8, !color);
				break;
			}
		}
	}
	putimage(board_y + 400, board_x + 100, buf, 0);
	free(buf);
	return (piece_y - 1);
}

void Graphic::graph_pointer(int x, int y, int pointer_color, int set)
{
	int fill_color;
	int Y_old = pointer_y * 50 + board_y;
	int X_old = pointer_x * 50 + board_x;
	int Y_set = set_pointer_y * 50 + board_y;
	int X_set = set_pointer_x * 50 + board_x;
	int unset = 0;
	if (pointer_color == 1)
		pointer_color = white_piece_color;
	else
		pointer_color = black_piece_color;
	if (!(set_pointer_x == pointer_x && set_pointer_y == pointer_y))
	{
		if ((pointer_x + pointer_y) % 2)
			fill_color = black_home_color;
		else
			fill_color = white_home_color;

		setcolor(fill_color);
		rectangle(Y_old + 2, X_old + 2, Y_old + 48, X_old + 48);
		rectangle(Y_old + 3, X_old + 3, Y_old + 47, X_old + 47);
		rectangle(Y_old + 4, X_old + 4, Y_old + 46, X_old + 46);
	}
	if (set_pointer_x != -1 && set) // UNSET
	{
		if ((set_pointer_x + set_pointer_y) % 2)
			fill_color = black_home_color;
		else
			fill_color = white_home_color;

		setcolor(fill_color);
		rectangle(Y_set + 2, X_set + 2, Y_set + 48, X_set + 48);
		rectangle(Y_set + 3, X_set + 3, Y_set + 47, X_set + 47);
		rectangle(Y_set + 4, X_set + 4, Y_set + 46, X_set + 46);
		unset = 1;
	}
	if (!(set_pointer_x == x && set_pointer_y == y) || set)
	{
		setcolor(pointer_color);
		rectangle(Y + 2, X + 2, Y + 48, X + 48);
		if (set && set_pointer_x == -1)
		{
			setlinestyle(1, 0, 1);
			set_pointer_x = x;
			set_pointer_y = y;
		}
		rectangle(Y + 3, X + 3, Y + 47, X + 47);
		setlinestyle(0, 0, 1);
		rectangle(Y + 4, X + 4, Y + 46, X + 46);
	}
	pointer_x = x;
	pointer_y = y;
	if (unset) // UNSET
		set_pointer_x = set_pointer_y = -1;
}
void Graphic::graph_pawn(int x, int y, int color)
{
	int color_p;
	color_p = set_piece_color(color);
	ellipse(Y + 25, X + 20, 300, 244, 3, 3);
	ellipse(Y + 25, X + 27, 300, 244, 8, 4);
	ellipse(Y + 25, X + 42, 0, 180, 10, 12);
	line(Y + 15, X + 42, Y + 35, X + 42);
	floodfill(Y + 25, X + 20, color_p);
	floodfill(Y + 25, X + 27, color_p);
	floodfill(Y + 25, X + 40, color_p);
}
void Graphic::graph_rook(int x, int y, int color)
{
	int color_p;
	color_p = set_piece_color(color);
	line(Y + 22, X + 16, Y + 28, X + 16);
	line(Y + 22, X + 19, Y + 22, X + 16);
	line(Y + 28, X + 19, Y + 28, X + 16);
	line(Y + 19, X + 19, Y + 22, X + 19);
	line(Y + 31, X + 19, Y + 28, X + 19);
	line(Y + 19, X + 16, Y + 19, X + 19);
	line(Y + 31, X + 16, Y + 31, X + 19);
	line(Y + 15, X + 16, Y + 19, X + 16);
	line(Y + 35, X + 16, Y + 31, X + 16);
	line(Y + 15, X + 20, Y + 15, X + 16);
	line(Y + 35, X + 20, Y + 35, X + 16);
	line(Y + 18, X + 22, Y + 15, X + 20);
	line(Y + 32, X + 22, Y + 35, X + 20);
	line(Y + 18, X + 35, Y + 18, X + 22);
	line(Y + 32, X + 35, Y + 32, X + 22);
	line(Y + 21, X + 35, Y + 29, X + 35);
	line(Y + 15, X + 38, Y + 18, X + 35);
	line(Y + 35, X + 38, Y + 32, X + 35);
	line(Y + 15, X + 42, Y + 15, X + 38);
	line(Y + 35, X + 42, Y + 35, X + 38);
	line(Y + 15, X + 42, Y + 35, X + 42);
	floodfill(Y + 25, X + 20, color_p);
}
void Graphic::graph_bishop(int x, int y, int color)
{
	int color_p;
	color_p = set_piece_color(color);
	ellipse(Y + 25, X + 14, 360, 0, 2, 2);
	ellipse(Y + 25, X + 25, 315, 225, 7, 8);
	line(Y + 25, X + 22, Y + 25, X + 27);
	line(Y + 23, X + 24, Y + 27, X + 24);
	ellipse(Y + 25, X + 32, 360, 0, 7, 2);
	ellipse(Y + 25, X + 37, 290, 250, 13, 3);
	line(Y + 20, X + 41, Y + 25, X + 37);
	line(Y + 30, X + 41, Y + 25, X + 37);
	floodfill(Y + 25, X + 14, color_p);
	floodfill(Y + 22, X + 27, color_p);
	floodfill(Y + 28, X + 29, color_p);
	floodfill(Y + 25, X + 32, color_p);
	floodfill(Y + 27, X + 37, color_p);
	floodfill(Y + 23, X + 37, color_p);
}
void Graphic::graph_queen(int x, int y, int color)
{
	int color_p;
	color_p = set_piece_color(color);
	circle(Y + 7, X + 18, 2);
	line(Y + 14, X + 34, Y + 9, X + 20);
	line(Y + 18, X + 33, Y + 9, X + 20);
	circle(Y + 15, X + 14, 2);
	line(Y + 18, X + 33, Y + 16, X + 16);
	line(Y + 23, X + 32, Y + 16, X + 16);
	circle(Y + 25, X + 12, 2);
	line(Y + 23, X + 32, Y + 25, X + 14);
	line(Y + 27, X + 32, Y + 25, X + 14);
	circle(Y + 35, X + 14, 2);
	line(Y + 27, X + 32, Y + 34, X + 16);
	line(Y + 32, X + 33, Y + 34, X + 16);
	circle(Y + 43, X + 18, 2);
	line(Y + 32, X + 33, Y + 41, X + 20);
	line(Y + 36, X + 34, Y + 41, X + 20);

	ellipse(Y + 25, X + 38, 330, 40, 13, 5);
	ellipse(Y + 25, X + 38, 140, 210, 13, 5);
	line(Y + 13, X + 41, Y + 37, X + 41);

	floodfill(Y + 7, X + 18, color_p);
	floodfill(Y + 15, X + 14, color_p);
	floodfill(Y + 25, X + 12, color_p);
	floodfill(Y + 35, X + 14, color_p);
	floodfill(Y + 43, X + 18, color_p);

	floodfill(Y + 15, X + 32, color_p);
	floodfill(Y + 19, X + 31, color_p);
	floodfill(Y + 24, X + 31, color_p);
	floodfill(Y + 28, X + 31, color_p);
	floodfill(Y + 34, X + 31, color_p);

	floodfill(Y + 25, X + 34, color_p);
	floodfill(Y + 25, X + 40, color_p);
}
void Graphic::graph_knight(int x, int y, int color)
{
	int color_p;
	color_p = set_piece_color(color);
	line(Y + 24, X + 15, Y + 25, X + 10);
	line(Y + 27, X + 16, Y + 25, X + 10);
	line(Y + 21, X + 16, Y + 22, X + 11);
	line(Y + 24, X + 16, Y + 22, X + 11);
	ellipse(Y + 25, X + 42, 0, 100, 15, 27);
	ellipse(Y + 25, X + 42, 20, 70, 12, 24);
	ellipse(Y + 29, X + 33, 105, 150, 15, 18);
	ellipse(Y + 17, X + 28, 100, 330, 4, 3);
	ellipse(Y + 23, X + 21, 0, 360, 1, 1);
	ellipse(Y + 14, X + 26, 270, 355, 5, 4);
	ellipse(Y + 20, X + 20, 270, 330, 10, 10);
	ellipse(Y + 19, X + 30, 330, 23, 10, 10);
	ellipse(Y + 27, X + 42, 90, 180, 5, 6);
	line(Y + 23, X + 42, Y + 40, X + 42);
	floodfill(Y + 25, X + 40, color_p);
	floodfill(Y + 20, X + 26, color_p);
}
void Graphic::graph_king(int x, int y, int color)
{
	int color_p;
	color_p = set_piece_color(color);
	line(Y + 25, X + 12, Y + 25, X + 7);
	line(Y + 23, X + 9, Y + 27, X + 9);
	arc(Y + 14, X + 21, 15, 180, 5);
	arc(Y + 25, X + 19, 0, 180, 6);
	arc(Y + 36, X + 21, 0, 165, 5);
	circle(Y + 25, X + 20, 2);
	line(Y + 13, X + 36, Y + 9, X + 21);
	line(Y + 37, X + 36, Y + 41, X + 21);
	ellipse(Y + 25, X + 34, 30, 150, 14, 4);
	ellipse(Y + 25, X + 38, 0, 360, 13, 4);
	floodfill(Y + 25, X + 20, color_p);
	floodfill(Y + 25, X + 27, color_p);
	floodfill(Y + 25, X + 31, color_p);
	floodfill(Y + 25, X + 38, color_p);
}
void Graphic::end_out_move_adress_in_graphic_board(char *masseg)
{
	static char last_move[6] = {"    \0"};
	setcolor(12);
	// rectangle(board_y+450,board_x+350,board_y+520,board_x+400);
	// floodfill(board_y+455,board_x+355,12);
	settextstyle(1, 0, 2);
	setcolor(15);
	outtextxy(board_y + 422, board_x + 352, "Last�����");
	outtextxy(board_y + 422, board_x + 375, "New�����");
	setcolor(0);
	outtextxy(board_y + 462, board_x + 352, last_move);
	outtextxy(board_y + 462, board_x + 375, masseg);
	strcpy(last_move, masseg);
}
void Graphic::out_masseg_in_graphic_board(char *masseg)
{
	unsigned size;
	size = imagesize(board_y + 400, board_x + 50, board_y + 425, board_x + 400);
	if (size != -1)
	{
		buf_masseg = malloc(size);
		if (buf_masseg)
			getimage(board_y + 400, board_x + 50, board_y + 425, board_x + 400, buf_masseg);
	}
	setcolor(text_color);
	settextstyle(1, 1, 2);
	outtextxy(board_y + 400, board_x + 50, masseg);
}
void Graphic::end_out_masseg_in_graphic_board(void)
{
	putimage(board_y + 400, board_x + 50, buf_masseg, 0);
	free(buf_masseg);
}
/*___________________________________________________________________________
				CLASS FOR BOARD
_____________________________________________________________________________*/
class Board
{
	friend class Display_chess_board;
	Piece *piece[8][8];
	Stack st;
	Graphic graphic;
	int counter, case_logical_move;
	int king_p[2][2];
	Piece *p;

public:
	Board(void);
	int move(int, int, int, int, int &react); // from main
	void undo(void);
	int check_undo(void);
	int xy_mojaz(int, int, int, int);
	int piece_in_board(int, int);
	int check(int, int, int x2 = -1, int y2 = -1);
	int check_turn(int);
	int check_fil(int, int, int, int);
	int check_rook(int, int, int, int);
	int check_pawn(int, int, int, int);
	int check_knight(int, int, int, int);
	int check_knight_opponent(int, int, int);
	int castle(int, int, int, int);
	int inpassing(int, int, int, int);
	void change_pawn(int, int, int);
	int king_check(int, int);
	int knight_check(int, int);
	int pawn_check(int, int);
	int bishop_check(int, int);
	int rook_check(int, int);
	int legal_moves(Queue *);
	int best_logical_move(int, int *);
	int best_logical_move_number(int, int *);
	int value_board(void);
};
/*_______________________________________________________________________________
			   A constructor  for  Board class
_________________________________________________________________________________*/
Board::Board(void)
{
	counter = 0;
	case_logical_move = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			piece[j][i] = NULL;
	for (i = 0; i < 8; i++)
	{
		piece[1][i] = new pawn(1, i, 1);
		piece[6][i] = new pawn(6, i, -1);
	}
	piece[0][4] = new king(0, 4, 1);
	king_p[0][0] = 0;
	king_p[0][1] = 4;
	piece[7][4] = new king(7, 4, -1);
	king_p[1][0] = 7;
	king_p[1][1] = 4;
	piece[0][1] = new knight(0, 1, 1);
	piece[0][6] = new knight(0, 6, 1);
	piece[7][1] = new knight(7, 1, -1);
	piece[7][6] = new knight(7, 6, -1);
	piece[0][2] = new bishop(0, 2, 1);
	piece[0][5] = new bishop(0, 5, 1);
	piece[7][2] = new bishop(7, 2, -1);
	piece[7][5] = new bishop(7, 5, -1);
	piece[0][0] = new rook(0, 0, 1);
	piece[0][7] = new rook(0, 7, 1);
	piece[7][0] = new rook(7, 0, -1);
	piece[7][7] = new rook(7, 7, -1);
	piece[0][3] = new queen(0, 7, 1);
	piece[7][3] = new queen(7, 3, -1);
}
/*_______________________________________________________________________________
			   Undo function from Board class
_________________________________________________________________________________*/
void Board::undo(void)
{
	int x1, y1, x2, y2;
	Piece *pi;
	if (--counter < 0)
	{
		counter++;
		return;
	}
	st.del(x1, y1, x2, y2, &pi);
	if (piece[x2][y2] != NULL)
	{
		if (piece[x2][y2]->type() == 'K')
		{
			if (piece[x2][y2]->color() == 1)
			{
				king_p[0][0] = x1;
				king_p[0][1] = y1;
			}
			else
			{
				king_p[1][0] = x1;
				king_p[1][1] = y1;
			}
			if (abs(y1 - y2) == 2)
			{
				undo(); // RECURSIVE FUNCTION
				counter++;
			}
		}
		// inpassing undo
		else if (piece[x2][y2]->type() == 'P' && counter != 0)
		{
			int x1_h, y1_h, x2_h, y2_h;
			Piece *p_h;
			st.del(x1_h, y1_h, x2_h, y2_h, &p_h);
			st.add(x1_h, y1_h, x2_h, y2_h, p_h);
			if (p_h != NULL)
				if (p_h->type() == 'P' && piece[x2][y2]->color() != p_h->color() && abs(x1_h - x2_h) == 2 && y2 == y1_h)
				{
					st.del(x1_h, y1_h, x2_h, y2_h, &p_h);
					piece[x2_h][y2_h] = p_h;
					if (!case_logical_move)
					{
						if (p_h != NULL)
							graphic.graph_piece_in_board(x2_h, y2_h, p_h->type(), p_h->color());
						else
							graphic.clean_home(x2_h, y2_h);
					}
				}
		}
		else // pawn change undo
		{
			int x1_h, y1_h, x2_h, y2_h;
			Piece *p_h;
			st.del(x1_h, y1_h, x2_h, y2_h, &p_h);
			st.add(x1_h, y1_h, x2_h, y2_h, p_h);
			if (x1_h == x2_h && y1_h == y2_h)
			{
				counter++;
				undo(); // RECURSIVE FUNCTION
				piece[x1][y1] = p_h;
				graphic.graph_piece_in_board(x1, y1, p_h->type(), p_h->color());
				piece[x1][y1]->dec_move(x1, y1);
				piece[x2][y2] = pi;
				if (!case_logical_move)
				{
					if (pi != NULL)
						graphic.graph_piece_in_board(x2, y2, pi->type(), pi->color());
					else
						graphic.clean_home(x2, y2);
				}
				return;
			}
		}
	}
	piece[x1][y1] = piece[x2][y2];
	if (!case_logical_move)
		if (piece[x1][y1] != NULL)
			graphic.graph_piece_in_board(x1, y1, piece[x2][y2]->type(), piece[x2][y2]->color());
		else
			graphic.clean_home(x1, y1);
	piece[x1][y1]->dec_move(x1, y1);
	piece[x2][y2] = pi;
	if (!case_logical_move)
	{
		if (pi != NULL)
			graphic.graph_piece_in_board(x2, y2, pi->type(), pi->color());
		else
			graphic.clean_home(x2, y2);
	}
}
/*_______________________________________________________________________________

_________________________________________________________________________________*/
int Board::check_undo(void)
{
	if (counter <= 0)
		return 0;
	return 1;
}
/*_______________________________________________________________________________
		 xy_mojaz function which checks correctness of the move
_________________________________________________________________________________*/
int Board::xy_mojaz(int x1, int y1, int x2, int y2)
{
	if (x1 == x2 && y1 == y2)
		return (0); // for no move
	if (!piece_in_board(x1, y1))
		return (0); // for mabda out of board
	if (!piece_in_board(x2, y2))
		return (0); // for magsad out of board
	if (piece[x1][y1] == NULL)
		return (0); // for mohre poohc
	if (piece[x2][y2] != NULL && piece[x2][y2]->color() == piece[x1][y1]->color())
		return (0); // for  mohre ro moh
	if (check_turn(piece[x1][y1]->color()) == 0)
		return (0);
	p = piece[x1][y1];
	if (piece[x1][y1]->type() == 'P')
		return (check_pawn(x1, y1, x2, y2));
	if (piece[x1][y1]->type() == 'B')
		return (check_fil(x1, y1, x2, y2));
	if (piece[x1][y1]->type() == 'R')
		return (check_rook(x1, y1, x2, y2));
	if (piece[x1][y1]->type() == 'Q')
		return ((check_rook(x1, y1, x2, y2) || (check_fil(x1, y1, x2, y2))));
	if (piece[x1][y1]->type() == 'N')
	{
		if (!check_knight(x1, y1, x2, y2))
			return 0;
	}
	if (piece[x1][y1]->type() == 'K' && (abs(y1 - y2) == 2) && (abs(x1 - x2) == 0))
		return (castle(x1, y1, x2, y2));
	if (piece[x1][y1]->type() == 'K')
		return (check(x1, y1, x2, y2));
	return (1);
}
/*_______________________________________________________________________________
			   Move function from Board class
_________________________________________________________________________________*/
int Board::move(int x1, int y1, int x2, int y2, int &react)
{
	react = 0;
	if (xy_mojaz(x1, y1, x2, y2) != 0)
	{
		if (piece[x1][y1]->move(x2, y2) != 0)
		{
			st.add(x1, y1, x2, y2, piece[x2][y2]);
			piece[x2][y2] = piece[x1][y1];
			piece[x1][y1] = NULL;
			counter++;
			if (piece[x2][y2]->type() == 'K')
				if (piece[x2][y2]->color() == 1)
					piece[x2][y2]->location(king_p[0][0], king_p[0][1]);
				else
					piece[x2][y2]->location(king_p[1][0], king_p[1][1]);
			if (piece[x2][y2]->color() != 1)
			{
				if (!check(king_p[1][0], king_p[1][1]))
				{
					undo();
					react = -1;
					return (0);
				}
				if (!check(king_p[0][0], king_p[0][1]))
					react = 2;
			}
			else
			{
				if (!check(king_p[0][0], king_p[0][1]))
				{
					undo();
					react = -2;
					return (0);
				}
				if (!check(king_p[1][0], king_p[1][1]))
					react = 1;
			}
			if (!case_logical_move)
			{
				graphic.clean_home(x1, y1);
				graphic.graph_piece_in_board(x2, y2, piece[x2][y2]->type(), piece[x2][y2]->color());
			}
			return (1);
		}
	}
	return (0);
}
/*_______________________________________________________________________________
			  check_turn  function from Board class
			  1=w
_________________________________________________________________________________*/
int Board::check_turn(int c)
{
	if (((counter + 2) % 2 == 1 && c == 1) || ((counter + 2) % 2 == 0 && c == -1))
		return 1;
	return 0;
}
/*__________________________________________________________________________________

___________________________________________________________________________________*/
int Board::piece_in_board(int x, int y)
{
	if ((x <= 7 && x >= 0) && (y <= 7 && y >= 0))
		return 1;
	return 0;
}

/*_______________________________________________________________________________
			   Castle function from Board class
_________________________________________________________________________________*/
int Board::castle(int x1, int y1, int x2, int y2)
{
	x2 = x2 + 1 - 1; // for warning
	int rook_y, sum = 0, react;
	if ((y2 - y1) > 0)
		rook_y = 7;
	else
		rook_y = 0;
	if (piece[x1][rook_y] != NULL)
		if (piece[x1][rook_y]->type() == 'R' &&
			piece[x1][rook_y]->first_move() == 0 &&
			(piece[x1][y1]->first_move() == 0))
			if (rook_y == 7)
				for (int i = 0; i < 3; i++)
					sum += check(x1, y1, x1, y1 + i);
			else
				for (int i = 0; i < 3; i++)
					sum += check(x1, y1, x1, y1 - i);
	if (sum != 3)
		return 0;
	if (rook_y == 7)
	{
		if (!move(x1, 7, x1, 5, react))
			return 0;
	}
	else if (!move(x1, 0, x1, 3, react))
		return 0;
	counter--;
	return (1);
}
/*_______________________________________________________________________________
	check  function from Board class which receives all
	opponent's pieces ability that can check(KISH) own king
_________________________________________________________________________________*/
int Board::check(int x1, int y1, int x2, int y2)
{
	int sum;
	if (x2 == -1 && y2 == -1)
	{
		x2 = x1;
		y2 = y1;
	}
	Piece *piece_mvaght = piece[x2][y2];
	piece[x2][y2] = piece[x1][y1];
	if (!(x1 == x2 && y1 == y2))
		piece[x1][y1] = NULL;
	sum = knight_check(x2, y2);
	sum += pawn_check(x2, y2);
	sum += bishop_check(x2, y2);
	sum += rook_check(x2, y2);
	sum += king_check(x2, y2);
	piece[x1][y1] = piece[x2][y2];
	piece[x2][y2] = piece_mvaght;
	sum /= 5;
	return (sum);
}
/*_______________________________________________________________________________
			  king_check  function from Board class
			  returns a value to main func{check}
_________________________________________________________________________________*/
int Board::king_check(int x2, int y2)
{
	int x, y, zx = 1, zy = 1;
	for (int i = 0; i < 8; i++)
	{
		x = x2;
		y = y2;
		switch (i)
		{
		case 1:
			zy = -1;
			break;
		case 2:
			zx = -1;
			break;
		case 3:
			zy = 1;
			break;
		case 4:
			zx = 0;
			break;
		case 5:
			zy = -1;
			break;
		case 6:
			zx = 1;
			zy = 0;
			break;
		case 7:
			zx = -1;
			break;
		}
		x += zx;
		y += zy;
		if (x >= 0 && x <= 7 && y >= 0 && y <= 7)
			if (piece[x][y] != NULL)
				if (piece[x][y]->type() == 'K')
					return 0;
	}
	return 1;
}
/*_______________________________________________________________________________
			  knight_check  function from Board class
			  returns a value to main func{check}
_________________________________________________________________________________*/
int Board::knight_check(int x2, int y2)
{
	if (!check_knight_opponent(x2 + 2, y2 + 1, piece[x2][y2]->color()))
		return 0;
	if (!check_knight_opponent(x2 + 2, y2 - 1, piece[x2][y2]->color()))
		return 0;
	if (!check_knight_opponent(x2 + 1, y2 + 2, piece[x2][y2]->color()))
		return 0;
	if (!check_knight_opponent(x2 + 1, y2 - 2, piece[x2][y2]->color()))
		return 0;
	if (!check_knight_opponent(x2 - 2, y2 - 1, piece[x2][y2]->color()))
		return 0;
	if (!check_knight_opponent(x2 - 2, y2 + 1, piece[x2][y2]->color()))
		return 0;
	if (!check_knight_opponent(x2 - 1, y2 + 2, piece[x2][y2]->color()))
		return 0;
	if (!check_knight_opponent(x2 - 1, y2 - 2, piece[x2][y2]->color()))
		return 0;
	return 1;
}
/*_________________________________________________________________________________

__________________________________________________________________________________*/
int Board::check_knight_opponent(int x, int y, int c)
{
	if (piece_in_board(x, y))
		if (piece[x][y] != NULL)
			if (piece[x][y]->type() == 'N')
				if (piece[x][y]->color() != c)
					return 0;
	return 1;
}
/*_______________________________________________________________________________
			  pawn_check  function from Board class
			  returns a value to main func{check}
_________________________________________________________________________________*/
int Board::pawn_check(int x2, int y2)
{
	if (piece[x2][y2]->color() == -1)
	{
		if (x2 - 1 > 0 && y2 - 1 >= 0)
			if (piece[x2 - 1][y2 - 1] != NULL)
				if (piece[x2 - 1][y2 - 1]->type() == 'P')
					if (piece[x2 - 1][y2 - 1]->color() == 1)
						return 0;
		if (x2 - 1 > 0 && y2 + 1 < 8)
			if (piece[x2 - 1][y2 + 1] != NULL)
				if (piece[x2 - 1][y2 + 1]->type() == 'P')
					if (piece[x2 - 1][y2 + 1]->color() == 1)
						return 0;
	}
	if (piece[x2][y2]->color() == 1)
	{
		if (x2 + 1 < 8 && y2 - 1 >= 0)
			if (piece[x2 + 1][y2 - 1] != NULL)
				if (piece[x2 + 1][y2 - 1]->type() == 'P')
					if (piece[x2 + 1][y2 - 1]->color() == -1)
						return 0;
		if (x2 + 1 < 8 && y2 + 1 < 8)
			if (piece[x2 + 1][y2 + 1] != NULL)
				if (piece[x2 + 1][y2 + 1]->type() == 'P')
					if (piece[x2 + 1][y2 + 1]->color() == -1)
						return 0;
	}
	return 1;
}
/*_______________________________________________________________________________
			  bishop_check  function from Board class
			  returns a value to main func{check}
_________________________________________________________________________________*/
int Board::bishop_check(int x2, int y2)
{
	int x, y, zx = 1, zy = 1;
	for (int i = 0; i < 4; i++)
	{
		x = x2;
		y = y2;
		switch (i)
		{
		case 1:
			zy = -1;
			break;
		case 2:
			zx = -1;
			break;
		case 3:
			zy = 1;
			break;
		}
		x += zx;
		y += zy;
		while (x >= 0 && x <= 7 && y >= 0 && y <= 7)
		{
			if (piece[x][y] != NULL)
				if (piece[x][y]->type() == 'B' ||
					piece[x][y]->type() == 'Q')
					if (piece[x2][y2]->color() != piece[x][y]->color())
						return 0;
					else
						break;
				else
					break;
			x += zx;
			y += zy;
		}
	}
	return 1;
}
/*_______________________________________________________________________________
			  rook_check  function from Board class
			  returns a value to main func{check}
_________________________________________________________________________________*/
int Board::rook_check(int x2, int y2)
{
	int x, y, zx = 1, zy = 0;
	for (int i = 0; i < 4; i++)
	{
		x = x2;
		y = y2;
		switch (i)
		{
		case 1:
			zx = -1;
			break;
		case 2:
			zx = 0;
			zy = 1;
			break;
		case 3:
			zy = -1;
			break;
		}
		x += zx;
		y += zy;
		while (x >= 0 && x <= 7 && y >= 0 && y <= 7)
		{
			if (piece[x][y] != NULL)
				if (piece[x][y]->type() == 'R' ||
					piece[x][y]->type() == 'Q')
					if (piece[x2][y2]->color() != piece[x][y]->color())
						return 0;
					else
						break;
				else
					break;
			x += zx;
			y += zy;
		}
	}
	return 1;
}
/*_______________________________________________________________________________
			  check_fil  function from Board class
			  returns a value to xy_mojaz function
_________________________________________________________________________________*/
int Board::check_fil(int x1, int y1, int x2, int y2)
{
	int x_help = x1 - x2, y_help = y1 - y2;
	int z_x = -1, z_y = -1, z = 1;
	if (x_help == y_help || x_help == -y_help)
	{
		if (x_help < 0)
		{
			z_x = 1;
			z = -1;
		}
		if (y_help < 0)
			z_y = 1;
		for (int i = 1; i != (x_help * z); i++)
			if (piece[(x1 + (i * z_x))][(y1 + (i * z_y))] != NULL)
				return 0;
	}
	else
		return 0;
	return 1;
}
/*_______________________________________________________________________________
			  check_rook  function from Board class
			  returns a value to xy_mojaz function
_________________________________________________________________________________*/
int Board::check_rook(int x1, int y1, int x2, int y2)
{
	int x_help = x1 - x2, y_help = y1 - y2;
	int z_x = -1, z_y = -1, x0 = 1, y0 = 1, sh;
	if ((x_help == 0) || (y_help == 0))
	{
		if (x_help == 0)
			x0 = 0;
		else
			y0 = 0;
		if (x_help < 0)
			z_x = 1;
		if (y_help < 0)
			z_y = 1;
		sh = x_help + y_help;
		if (sh < 0)
			sh *= -1;
		for (int i = 1; i != sh; i++)
			if (piece[(x1 + (i * x0 * z_x))][(y1 + (i * y0 * z_y))] != NULL)
				return 0;
	}
	else
		return 0;
	return 1;
}
/*_______________________________________________________________________________
			  check_pawn  function from Board class
			  returns a value to xy_mojaz function
_________________________________________________________________________________*/
int Board::check_pawn(int x1, int y1, int x2, int y2)
{
	int abs_x = (x2 - x1) * piece[x1][y1]->color();
	int abs_y = (y2 - y1) * piece[x1][y1]->color();
	if (abs_x == 2 && abs_y == 0 && piece[x2][y2] == NULL)
		if (piece[x1][y1]->first_move() != 0)
			return 0;
		else
			return (check_rook(x1, y1, x2, y2));
	if (abs_x == 1 && abs(abs_y) == 1) // for zadan
		if (piece[x2][y2] != NULL)
		{
			if (x2 == 0 || x2 == 7)
				change_pawn(x1, y1, piece[x1][y1]->color());
			return 1;
		}
		else
			return (inpassing(x1, y1, x2, y2));
	if (abs_x == 1 && abs_y == 0 && piece[x2][y2] == NULL)
	{
		if (x2 == 0 || x2 == 7)
			change_pawn(x1, y1, piece[x1][y1]->color());
		return 1;
	}
	return 0;
}
/*_______________________________________________________________________________
			  check_knight  function from Board class
			  returns a value to xy_mojaz function
_________________________________________________________________________________*/
int Board::check_knight(int x1, int y1, int x2, int y2)
{
	if (!((x1 == x2 + 2) && y1 == (y2 + 1) ||
		  (x1 == x2 - 2 && y1 == y2 + 1) ||
		  (x1 == x2 + 2 && y1 == y2 - 1) ||
		  (x1 == x2 - 2 && y1 == y2 - 1) ||
		  (x1 == x2 + 1 && y1 == y2 + 2) ||
		  (x1 == x2 - 1 && y1 == y2 + 2) ||
		  (x1 == x2 + 1 && y1 == y2 - 2) ||
		  (x1 == x2 - 1 && y1 == y2 - 2)))
		return 0;
	return 1;
}
/*_______________________________________________________________________________
	 inpassing  function from Board class checks the correctness of pawn move
	 inorder to find does it inpass another or not
_________________________________________________________________________________*/
int Board::inpassing(int x1, int y1, int x2, int y2)
{
	x2 = x2 + 1 - 1; // for warning
	int x1_last, x2_last, y1_last, y2_last;
	Piece *p;
	if (piece[x1][y2] != NULL)
		if (piece[x1][y2]->type() == 'P' && piece[x1][y2]->color() != piece[x1][y1]->color())
			if (st.del(x1_last, y1_last, x2_last, y2_last, &p)) // ??
			{
				st.add(x1_last, y1_last, x2_last, y2_last, p);
				if (x1 == x2_last && y2 == y2_last && abs(x1_last - x2_last) == 2)
				{
					st.add(x1_last, y1_last, x2_last, y2, piece[x1][y2]);
					piece[x1][y2] = NULL;
					if (!case_logical_move)
						graphic.clean_home(x1, y2);
					return 1;
				}
			}
	return 0;
}
/*_______________________________________________________________________________
	 change_pawn  function from Board class checks if pawn is at 7th rank
	 and want to increase it's rank it returns to check_move function
_________________________________________________________________________________*/
void Board::change_pawn(int x2, int y2, int c)
{
	int cho;
	st.add(x2, y2, x2, y2, p);
	if (case_logical_move)
	{
		piece[x2][y2] = new queen(x2, y2, c);
		return;
	}
	cho = graphic.graph_change_pawn(c);
	switch (cho)
	{
	case 1:
		piece[x2][y2] = new queen(x2, y2, c);
		break;
	case 2:
		piece[x2][y2] = new rook(x2, y2, c);
		break;
	case 3:
		piece[x2][y2] = new bishop(x2, y2, c);
		break;
	case 4:
		piece[x2][y2] = new knight(x2, y2, c);
		break;
	}
}
/*_______________________________________________________________________________
	  legal_moves function from Board class which counts legal moves
	  of one inorder to find two positions mate & stealmate
	  it is called from main function
_________________________________________________________________________________*/
int Board::legal_moves(Queue *list_of_moves)
{
	int t, cod[4];
	int total_move = 0;
	graphic.graph_enabel(0);
	case_logical_move = 1;
	for (cod[0] = 0; cod[0] < 8; cod[0]++)
		for (cod[1] = 0; cod[1] < 8; cod[1]++)
			if (piece[cod[0]][cod[1]] != NULL)
				for (cod[2] = 0; cod[2] < 8; cod[2]++)
					for (cod[3] = 0; cod[3] < 8; cod[3]++)
						if (move(cod[0], cod[1], cod[2], cod[3], t) == 1)
						{
							total_move++;
							list_of_moves->add(cod);
							undo();
						}
	case_logical_move = 0;
	graphic.graph_enabel(1);
	return total_move;
}
/*_________________________________________________________________________________

___________________________________________________________________________________*/
int Board::best_logical_move(int n, int *adress_move)
{
	int i, adress[4], number_move, arzesh_move;
	Queue list_of_moves;
	graphic.graph_enabel(0);
	case_logical_move = 1;
	arzesh_move = best_logical_move_number(n, &number_move);
	legal_moves(&list_of_moves);
	for (i = 0; i <= number_move; i++)
		list_of_moves.del(adress);
	adress_move[0] = adress[0];
	adress_move[1] = adress[1];
	adress_move[2] = adress[2];
	adress_move[3] = adress[3];
	graphic.graph_enabel(1);
	case_logical_move = 0;
	return arzesh_move;
}
/*_________________________________________________________________________________

___________________________________________________________________________________*/
int Board::best_logical_move_number(int n, int *number_move)
{
	if (n == 1)
		return value_board();
	Queue list_of_moves;
	char move_adress_char[4];
	int min_max, sum_move = 0, number;
	int emtiyaz_bazy, i;
	int halat;
	int adress[4];
	sum_move = legal_moves(&list_of_moves);
	if ((n % 2))
		min_max = -1000;
	else
		min_max = 1000;
	for (i = 0; i < sum_move; i++)
	{
		list_of_moves.del(adress);
		case_logical_move = 1;
		graphic.graph_enabel(0);
		move(adress[0], adress[1], adress[2], adress[3], halat);
		// if (...)
		//	continue;
		emtiyaz_bazy = best_logical_move_number(n - 1, &number);
		//	??????????????
		if (i == 0)
		{
			min_max = emtiyaz_bazy;
			*number_move = sum_move / 2;
		}
		//	??????????????
		if ((n % 2))
		{
			if (emtiyaz_bazy > min_max)
			{
				min_max = emtiyaz_bazy;
				*number_move = i;
			}
		}
		else
		{
			if (emtiyaz_bazy < min_max)
			{
				min_max = emtiyaz_bazy;
				*number_move = i;
			}
		}
		undo();
	}
	return min_max;
}
/*_________________________________________________________________________________

___________________________________________________________________________________*/
int Board::value_board(void)
{
	int t, sq;
	register int m, n;
	for (m = 0; m < 8; m++)
		for (n = 0; n < 8; n++)
			if (piece[m][n] != NULL)
			{
				if (check_turn(piece[m][n]->color()))
					sq = 1;
				else
					sq = -1;
				switch (piece[m][n]->type())
				{
				case 'P':
					t += (sq * 1);
					break;
				case 'R':
					t += (sq * 4);
					break;
				case 'B':
					t += (sq * 3);
					break;
				case 'Q':
					t += (sq * 9);
					break;
				case 'N':
					t += (sq * 2);
					break;
				case 'K':
					t += (sq * 0);
					break;
				}
			}
	return t;
}
/*_________________________________________________________________________________

___________________________________________________________________________________*/
class Display_chess_board
{
	Board *board_pointer;
	Graphic graphic;

public:
	Display_chess_board(void)
	{
	}
	Display_chess_board(Board *bp) : board_pointer(bp)
	{
	}
	void display_init(Board *b)
	{
		board_pointer = b;
	}
	void display_pointer(int, int, int set = 0);
	void display_board(void);
	void display_mated(char *);
	void display_checked(char *);
	void display_stealmate(void);
	void display_masseg(char *);
};

/*___________________________________________________________________________

_____________________________________________________________________________*/
void Display_chess_board::display_masseg(char *masseg)
{
	graphic.end_out_move_adress_in_graphic_board(masseg);
}
/*_____________________________________________________________________________

_______________________________________________________________________________*/
void Display_chess_board::display_pointer(int x, int y, int set)
{
	graphic.graph_pointer(x, y, !board_pointer->check_turn(1), set);
}
/*___________________________________________________________________________
				 DISPLAY FUNCTION
_____________________________________________________________________________*/

void Display_chess_board::display_board(void)
{
	register int m, n;
	graphic.graph_board();
	for (m = 0; m < 8; m++)
		for (n = 0; n < 8; n++)
			if (board_pointer->piece[m][n] != NULL)
				graphic.graph_piece_in_board(m, n,
											 board_pointer->piece[m][n]->type(),
											 board_pointer->piece[m][n]->color());
}
/*_____________________________________________________________________________

_______________________________________________________________________________*/
void Display_chess_board::display_mated(char *color)
{
	char masseg[30];
	strcpy(masseg, color);
	strcat(masseg, " is checked & mated!!");
	graphic.out_masseg_in_graphic_board(masseg);
	sound(3500);
	delay(50);
	sound(3000);
	delay(100);
	sound(2500);
	delay(200);
	sound(2000);
	delay(300);
	sound(1500);
	delay(400);
	sound(1000);
	delay(500);
	sound(1500);
	delay(400);
	sound(2000);
	delay(300);
	sound(2500);
	delay(200);
	sound(3000);
	delay(100);
	sound(3500);
	delay(50);
	nosound();
	graphic.end_out_masseg_in_graphic_board();
}
/*__________________________________________________________________________________

___________________________________________________________________________________*/
void Display_chess_board::display_checked(char *color)
{
	char masseg[40];
	strcpy(masseg, color);
	strcat(masseg, " is checked!!");
	graphic.out_masseg_in_graphic_board(masseg);
	sound(700);
	delay(1000);
	nosound();
	graphic.end_out_masseg_in_graphic_board();
}
/*__________________________________________________________________________________

___________________________________________________________________________________*/

void Display_chess_board::display_stealmate(void)
{
	graphic.out_masseg_in_graphic_board("Stealmate !");
	sound(900);
	delay(500);
	sound(200);
	delay(100);
	sound(900);
	delay(500);
	nosound();
	graphic.end_out_masseg_in_graphic_board();
}
/*______________________________________________________________________________

_________________________________________________________________________________*/
class Play
{
	Board *board_pointer;
	Display_chess_board *dis;
	Config *config;
	void standard_move(int *, char *);
	void cod_move(char *, int *);
	void random_paly_adress(char *);
	// void read_move_adress_of_file(fstream,char *);
	void read_move_adress_of_keyboard(char *);
	int check_board_and_display_masseg(int);
	void show_legal_move(void);
	void new_game(void);
	void get_load_file_name(char *);
	int view_data_book(char *);

public:
	Play(void)
	{
		board_pointer = new Board;
		dis = new Display_chess_board;
		config = new Config;
		dis->display_init(board_pointer);
	}
	~Play(void)
	{
		delete board_pointer;
		delete dis;
		delete config;
	}
	int view_last_game(char *);
	int central_play(void);
};

void Play::get_load_file_name(char *file_name)
{
	gets(file_name);
}
void Play::new_game(void)
{
	delete board_pointer;
	delete dis;
	delete config;
	display_init();
	board_pointer = new Board;
	dis = new Display_chess_board;
	config = new Config;
	dis->display_init(board_pointer);
	dis->display_board();
}

/*__________________________________________________________________________________
   STANDARD_MOVE function change an move in int form to logical notation
			example: 7150 = b1c3
______________________________________________________________________________________*/
void Play::standard_move(int *cod_move, char *decod_move)
{
	decod_move[0] = cod_move[1] + 'a';
	decod_move[2] = cod_move[3] + 'a';
	decod_move[1] = '0' + 8 - cod_move[0];
	decod_move[3] = '0' + 8 - cod_move[2];
}
/*__________________________________________________________________________________

___________________________________________________________________________________*/
void Play::cod_move(char *decod_move, int *cod_move)
{
	cod_move[1] = decod_move[0] - 'a';
	cod_move[3] = decod_move[2] - 'a';
	cod_move[0] = '0' + 8 - decod_move[1];
	cod_move[2] = '0' + 8 - decod_move[3];
}
/*______________________________________________________________________________
	 RANDOM_PLAY function gets board and finds a random move
		 and store it in move_adress.
_________________________________________________________________________________*/
void Play::random_paly_adress(char *move_adress)
{
	Queue q;
	int random_palay_number, cod[4];
	int total_move;
	randomize();
	total_move = board_pointer->legal_moves(&q);
	random_palay_number = 1 + random((total_move - 1));
	for (int i = 0; i < random_palay_number; i++)
		q.del(cod);
	standard_move(cod, move_adress);
}
/*________________________________________________________________________________

_________________________________________________________________________________*/
int Play::central_play(void)
{
	int cod[4], react;
	char move_adress[5], load_file_name[20], exit = 'v', ch;
	move_adress[4] = '\0';
	fstream databook_file;
	databook_file.open("databook.txt", ios::in);
	if (!databook_file)
	{
		cout << "Noat find Databook.\nHalt !\n";
		getch();
		// exit='o';
	}
	dis->display_board(); // <<==
	while ((!(exit == 'n' || exit == 'q')) && config->config_check())
	{
		switch (config->operations_elective)
		{
		case 'l':
		case 'r':
			if (config->tern_of_move == 'u')
				read_move_adress_of_keyboard(move_adress);
			else if (config->tern_of_move == 'w' && board_pointer->check_turn(1))
				read_move_adress_of_keyboard(move_adress);
			else if (config->tern_of_move == 'b' && board_pointer->check_turn(-1))
				read_move_adress_of_keyboard(move_adress);
			else
				switch (config->operations_elective)
				{
				case 'l':
					board_pointer->best_logical_move(4, cod);
					standard_move(cod, move_adress);
					break;
				case 'r':
					random_paly_adress(move_adress);
					break;
				}
			break;
		case 'u':
			board_pointer->undo();
			config->operations_elective = 'l'; //  <<==
			if (!board_pointer->check_undo())
				config->options_menu_txet[0][0] = '-';
			break;
		case 'p':
			show_legal_move();
			config->operations_elective = 'l';
			break;
		case 'd':
			dis->display_board();
			config->operations_elective = 'l';
			break;
		case 'q':
			exit = 'q';
			continue;
			break;
		case 'n':
			new_game();
			continue;
			break;
		case 'v':
			get_load_file_name(load_file_name);
			view_data_book(load_file_name);
			// view_last_game(load_file_name);
			config->operations_elective = 'l';
			continue;
			break;
		}
		if (move_adress[0] == 'q')
			continue;
		cod_move(move_adress, cod);
		if (board_pointer->move(cod[0], cod[1], cod[2], cod[3], react) == 1)
		{
			dis->display_masseg(move_adress);
			config->options_menu_txet[0][0] = ' ';
		}
		if (check_board_and_display_masseg(react) == 0)
		{
			getch();
			new_game();
		}
		move_adress[0] = 'q';
	}
	if (exit == 'n')
		return 1;
	return 0;
}
/*________________________________________________________________________________

_________________________________________________________________________________*/
int Play::view_data_book(char *last_game_file_name)
{
	fstream chess_file;
	int cod[4], react, s = 0, p;
	char move_adress[5], exit = 'v', ch, char_file;
	move_adress[4] = '\0';
	chess_file.open(last_game_file_name, ios::in);
	if (!chess_file)
	{
		cout << "\nfile not find!\n";
		return 0;
	}
	new_game();
	while (config->config_check() && exit != 'q')
	{
		// read_move_adress_of_file(chess_file,move_adress);
		chess_file.get(char_file);
		printf("%c", char_file);
		s %= 4;
		move_adress[s] = char_file;
		if (char_file == '+')
		{
			getch();
			new_game();
			s = 0;
			continue;
		}
		else if (char_file == '{')
		{
			p = 1;
			while (p != 0)
			{
				chess_file.get(char_file);
				printf("%c", char_file);
				if (char_file == '}')
					p = 0;
			}
			// chess_file.get(char_file);
			// printf("%c",char_file);
			s = 0;
			continue;
		}
		else if (char_file == ' ' || char_file == '\r' || char_file == '\n')
		{
			s = 0;
			continue;
		}
		if (move_adress[0] == 'q' || move_adress[0] == 'Q')
		{
			// dis->display_masseg("End of saved game.\n     Quit or continue (q=quit) : ");
			exit = 'q';
			continue;
		}
		if (s == 3)
		{
			// printf(" *%s* ",move_adress);
			cod_move(move_adress, cod);
			// dis->display_board();
			// dis->display_masseg(move_adress);
			// cout<<"******"<<cod[0]<<cod[1]<<cod[2]<<cod[3];
			if (board_pointer->move(cod[0], cod[1], cod[2], cod[3], react) == 1)
				if (check_board_and_display_masseg(react) == 0)
					exit = 'q';
		}
		s++;
	}
	chess_file.close();
	return 1;
}
/*________________________________________________________________________________

_________________________________________________________________________________*/
int Play::view_last_game(char *last_game_file_name)
{
	fstream chess_file;
	int cod[4], react;
	char move_adress[5], exit = 'v', ch;
	move_adress[4] = '\0';
	chess_file.open(last_game_file_name, ios::in);
	if (!chess_file)
	{
		cout << "\nfile not find!\n";
		return 0;
	}
	new_game();
	while (config->config_check() && exit != 'q')
	{
		// read_move_adress_of_file(chess_file,move_adress);
		chess_file.get(move_adress[0]);
		chess_file.get(move_adress[1]);
		// chess_file.get(ch);
		chess_file.get(move_adress[2]);
		chess_file.get(move_adress[3]);
		chess_file.get(ch);
		if (move_adress[0] == 'q' || move_adress[0] == 'Q')
		{
			// dis->display_masseg("End of saved game.\n     Quit or continue (q=quit) : ");
			exit = 'q';
			continue;
			/*
			else
			   {
				//logical_play();//edamey bazy
				exit='q';
				continue;
			   }
			*/
		}
		else if (move_adress[0] == 'u' || move_adress[0] == 'U')
		{
			// dis->display_masseg("Next move : Undo");
			// dis->display_masseg("\n     Play OR view next move (v for view) ? ");
			// exit=getche();
			// if(!(exit=='v' || exit=='V'))
			//	continue;
			board_pointer->undo();
			// dis->display_masseg("\x07");
			// continue;
		}
		/*
		else
			{
			 dis->display_masseg("Next move : ");
			 dis->display_masseg(move_adress);
			 dis->display_masseg("\n     Play OR view next move (v for view) ? ");
			 exit=getche();
			 if(!(exit=='v' || exit=='V'))
				{
				 //logical_play();
				 continue;
				}
			}
		   */
		cod_move(move_adress, cod);
		// dis->display_board();
		// dis->display_masseg(move_adress);
		// cout<<"******"<<cod[0]<<cod[1]<<cod[2]<<cod[3];
		if (board_pointer->move(cod[0], cod[1], cod[2], cod[3], react) == 1)
			if (check_board_and_display_masseg(react) == 0)
				exit = 'q';
	}
	chess_file.close();
	return 1;
}
/*______________________________________________________________________________________

_______________________________________________________________________________________*/
/*
void Play::read_move_adress_of_file(fstream file_pointer,char *move_adress)
		{
		 char ch;
		 file_pointer.get(move_adress[0]);
		 file_pointer.get(move_adress[1]);
		 //chess_file.get(ch);
		 file_pointer.get(move_adress[2]);
		 file_pointer.get(move_adress[3]);
		 file_pointer.get(ch);
		}
*/
/*_____________________________________________________________________________

_________________________________________________________________________________*/
void Play::read_move_adress_of_keyboard(char *move_adress)
{
	int tedad_enter = 0, cont_char = 0;
	int cod[4], m = 0;
	char key = 'm', char_adress[5];
	char_adress[4] = '\0';
	static int pointr_x = 0, pointr_y = 7;
	dis->display_pointer(pointr_y, pointr_x);
	move_adress[0] = '\0';
	while (config->config_check() && config->operations_elective != 'u')
	{
		while (m != 1)
		{
			m = check_keyboard();
			if (m == 2)
				if (config->config_check())
				{
					move_adress[0] = 'q';
					return;
				}
		}
		key = getch();
		config->config_check(key);
		if (key == 0)
		{
			key = getch();
			switch (key)
			{
			case 77:
				if (pointr_x < 7)
					dis->display_pointer(pointr_y, ++pointr_x);
				break;
			case 75:
				if (pointr_x > 0)
					dis->display_pointer(pointr_y, --pointr_x);
				break;
			case 80:
				if (pointr_y < 7)
					dis->display_pointer(++pointr_y, pointr_x);
				break;
			case 72:
				if (pointr_y > 0)
					dis->display_pointer(--pointr_y, pointr_x);
				break;
			case 45:
				config->ch_exit();
				break;
			}
		}
		else if (key == 13)
		{
			dis->display_pointer(pointr_y, pointr_x, 1);
			if (tedad_enter)
			{
				cod[3] = pointr_x;
				cod[2] = pointr_y;
				standard_move(cod, move_adress);
				return;
			}
			else
			{
				cod[1] = pointr_x;
				cod[0] = pointr_y;
				tedad_enter++;
			}
		}
		else
		{
			char_adress[cont_char++] = key;
			if (cont_char == 4)
			{
				strcpy(move_adress, char_adress);
				return;
			}
		}
	}
	move_adress[0] = 'q';
}
/*_____________________________________________________________________________

_________________________________________________________________________________*/
int Play::check_board_and_display_masseg(int react)
{
	Queue q;
	int total_move = board_pointer->legal_moves(&q);
	switch (react)
	{
	case -1:
		dis->display_checked("Illegal move white");
		// cout<<"Illegal move white is checked!!";
		return 1;
		break;
	case -2:
		dis->display_checked("Illegal move black");
		// cout<<"Illegal move black is checked!!";
		return 1;
		break;
	case 1:
		if (total_move == 0)
		{
			dis->display_mated("White");
			return 0;
		}
		else
		{
			dis->display_checked("White");
			return 1;
		}

		break;
	case 2:
		if (total_move == 0)
		{
			dis->display_mated("Black");
			return 0;
		}
		else
		{
			dis->display_checked("Black");
			return 1;
		}
		break;
	default:
		if (total_move == 0)
		{
			dis->display_stealmate();
			return 0;
		}
	}
	return 1;
}
/*___________________________________________________________________________

_____________________________________________________________________________*/

void Play::show_legal_move(void)
{
	Queue q;
	int total_move, cod[4], t;
	char decod[5];
	decod[4] = '\0';
	total_move = board_pointer->legal_moves(&q);
	for (int i = 0; i < total_move; i++)
	{
		q.del(cod);
		standard_move(cod, decod);
		dis->display_masseg(decod); //  <<=
		board_pointer->move(cod[0], cod[1], cod[2], cod[3], t);
		getch(); // <<==
		board_pointer->undo();
		getch(); // <<==
	}
}

/*___________________________________________________________________________
				 THE MAIN OF CHESS PROGRAM
_____________________________________________________________________________*/
void main(void)
{
	void titel(void);
	void menu(void);
	// titel();
	// menu();
	int x = 1;
	Play *play;
	while (x)
	{
		display_init();
		play = new Play;
		if (!(play->central_play()))
			x = 0;
		delete play;
	}
}
/*________________________________________________________________________________
		MENU function shows first choices of user
__________________________________________________________________________________*/
void menu(void)
{
	clrscr();
	cout << "\n\n\n\n";
	cout << "\n\tv : view last game.";
	cout << "\n\tr : random paly.";
	cout << "\n\tp or other key : play (2 player)";
	cout << "\n\n\n\tChoose a key : ";
}
/*_______________________________________________________________________________
	   titel function is called from main and shows a picture
	   which is not supplied in all systems .
	   if you have a problem with graphic mode bring out lines
	   4 to 11.
_______________________________________________________________________________________*/
void titel(void)
{
	int gdriver = DETECT;
	int gmode;
	int check_keyboard(void);
	clrscr();
	initgraph(&gdriver, &gmode, "");
	settextstyle(4, 0, 10);
	setcolor(9);
	outtextxy(15, 5 * (10 + 1), "chess game");
	getch();
	closegraph();
	clrscr();
	gotoxy(4, 4);
	textcolor(9);
	cprintf("AUTHORS :");
	gotoxy(13, 5);
	textcolor(2);
	cprintf("EHSAN AMINI                  SI=(77323287)");
	gotoxy(32, 6);
	textcolor(15);
	cprintf("&&");
	gotoxy(13, 7);
	textcolor(4);
	cprintf("KAYVAN HAJ HASSAN TEHRANI    SI=(77323358)");
	gotoxy(35, 13);
	textcolor(3);
	cprintf("CHESS GAME");
	textcolor(5);
	gotoxy(29, 20);
	cprintf("Press any key to continue");
	gotoxy(4, 23);
	textcolor(13);
	for (int i = 10; i < 30; i++)
	{
		sound(1 * 10 * i);
		delay(220);
		sound(2 * 10 * i);
		delay(120);
		if (check_keyboard())
		{
			nosound();
			break;
		}
		sound(3 * 10 * i);
		delay(110);
		if (check_keyboard())
		{
			nosound();
			break;
		}
		sound(4 * 10 * i);
		delay(20);
		sound(5 * 10 * i);
		delay(290);
		if (check_keyboard())
		{
			nosound();
			break;
		}
		sound(6 * 10 * i);
		delay(460);
		sound(7 * 10 * i);
		delay(657);
		if (check_keyboard())
		{
			nosound();
			break;
		}
		nosound();
	}
	getch();
}
/*_______________________________________________________________________________
	   check_keyboard function is called from titel function ,uses dos
	   interrupt 21H to check keyboard palses.
_______________________________________________________________________________________*/
int check_keyboard(void)
{
	static int old_keyborde_status = 0;
	int key;
	union REGS in, out;
	in.h.ah = 2;
	int86(0x16, &in, &out);
	if (int(out.h.al) != old_keyborde_status)
	{
		old_keyborde_status = out.h.al;
		return 2;
	}
	in.h.ah = 0xb;
	intdos(&in, &out);
	if (out.h.al)
		return (1);
	return 0;
}
/************************************************************************************
________________________________END OF CHESS PROGRAM_________________________________
				 ..................
************************************************************************************/
