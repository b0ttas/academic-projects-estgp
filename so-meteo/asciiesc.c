#include "asciiesc.h"

//clear screen
void clear_display()
{
	printf("\033[2J");
}
//range color [30-37]
void set_color(int color)
{
	printf("\033[%dm",color);
}
//range color [40-47] --color +10--
void set_background_color(int color)
{
	printf("\033[%dm",color+10);
}

void set_cursor_position(int line, int column)
{
	printf("\033[%d;%dH",line,column);
}

void set_boldon()
{
	printf("\033[1m");	
}

void set_blink()
{
	printf("\033[5m");
}

void clear_attr()
{
	printf("\033[0m");
}