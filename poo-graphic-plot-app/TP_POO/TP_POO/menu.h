#ifndef MENU_H
#define MENU_H

#include "draw.h"
#include "Registo.h"
#include "Ficheiro.h"
#include "Internos.h"
#include <stdio.h>
#include <iostream>

class Menu
{
public:
	Menu();
	virtual ~Menu();

	void menu();
	void menu_plot();
};
#endif