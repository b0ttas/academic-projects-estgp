#include "Figura.h"



Figura::Figura()
{
}


Figura::~Figura()
{
}

Figura::Figura(Point a, Point b, Point c, Color col_line, Color col_fill, int type)
{
	A = a;
	B = b;
	C = c;
	Col_line = col_line;
	Col_fill = col_fill;
	Type = type;
	selected = false;
}
