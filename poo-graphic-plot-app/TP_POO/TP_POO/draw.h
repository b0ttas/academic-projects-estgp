#ifndef DRAW_H
#define DRAW_H

//#include "list.h"
#include "Registo.h"
#include "Ficheiro.h"
#include "Internos.h"

#include <iostream>
#include <stdlib.h>
#include <math.h>

#include <Windows.h>
#include <iostream>
#include <string.h>

class Draw
{
public:	
	Draw();
	virtual ~Draw();

	void draw_graph();
	void draw_values(double xx_scl, double yy_scl, double curr_X, double curr_Y, double min_X, double min_Y, double max_X, double max_Y, int no_pts);
	void center(int line, int column, const char * s);
	void draw_info(int ch);
	void draw_info_int(int ch, int p, double freq, double a, double vert_off);
	void ClearScreen();
	void reg_print();
	void export_reg_print();
	void sub_print();
	void goto_xy(signed int x, signed int y);
};


#endif