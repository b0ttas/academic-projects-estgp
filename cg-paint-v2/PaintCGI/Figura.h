#include "Color.h"
#include "Point.h"

#define QUAD 1
#define TRI 2
#define REC 3
#define CIR 4
#define DOT 5
#define LIN 6

class Figura
{
public:
	Figura();
	~Figura();

	Figura(Point a, Point b, Point c, Color col, Color col_fill, int type);

protected:

	Point A;
	Point B;
	Point C;

	Color Col_line;
	Color Col_fill;

	int Type;

	bool selected;
};

