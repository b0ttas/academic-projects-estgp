#ifndef INT_H
#define INT_H

#include "list.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <math.h>

class Internos
{
public:

	Internos();
	~Internos();

	void getFunc(int ch, int p, double freq, double a, double vert_off);
	void lstComms();
	void mov_calc(int vini, int vfin);
	void lst_it();

	double x;
	double y;

	double curr_X;
	double curr_Y;
	double min_X;
	double min_Y;
	double max_X;
	double max_Y;
	double vmedio;
	double vquad;
	double mov;

	int no_pts;
	int finish_flag;
	int file_org;

	std::string line, xx, yy;
};
#endif

