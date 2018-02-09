#ifndef	ASCIIESC_H
#define	ASCIIESC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <strings.h>
//#include <unistd.h>
#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h> 
//#include <arpa/inet.h>
//#include <pthread.h>
#include <time.h>


#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37

#define MAXBUF 100

#define client_max 5


void clear_display();
void set_color(int color);
void set_background_color(int color);
void set_cursor_position(int line, int column);
void set_boldon();
void set_blink();
void clear_attr();

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

void exit();
#endif
