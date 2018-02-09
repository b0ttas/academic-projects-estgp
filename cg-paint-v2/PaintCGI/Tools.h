#pragma once

#include "Point.h"
#include "list.h"
#include "Iterator.h"
#include <GL/glut.h>

#define Tools_square 12
#define Tools_all 14
#define Tam_square 40
#define Tam_rect 80

class Tools
{
public:
	Tools();
	~Tools();
	Tools::Tools(Point a, Point b);
	Point Get_A();
	Point Get_B();


private:
	Point A, B;
};

void Draw_Tools();