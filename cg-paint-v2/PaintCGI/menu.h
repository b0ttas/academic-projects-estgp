#include <stdlib.h>
#include <stdio.h>
#include "Figura.h"
#include "list.h"

void insert(Point a, Point b, Point c, Color col, int type);
void draw();
void preview();
void mouse_clk(int button, int state, int x, int y);
void mouse_hover(int x, int y);
void display();