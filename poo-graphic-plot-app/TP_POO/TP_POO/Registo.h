#ifndef REG_H
#define REG_H

#include "Ficheiro.h"

#include <iostream>
#include <fstream>
#include <string>

#include <iomanip>
#include <ctime>
#include <sstream>
#include <stdio.h>

class Registo
{
public:
	Registo();
	virtual ~Registo();

	void SetReg(int nopts, int file_org, double xmax, double ymax, double xmin, double ymin, double vmedio, double vquad, double mov);
	void reg_PRINT();
	int reg_EXPORT();

	struct reg //estrutura p/ registo com dados
	{
		int reg_NO;
		int func_VALS;
		double Reg_xMax, Reg_yMax, Reg_xMin, Reg_yMin, Reg_vmedio, Reg_vquad, Reg_mov;
		std::string reg_ORIGIN;
		std::string time_str;
	};
	//inicia o array da estrutura a 0
	int i = 0;
	reg registry[10] = {0};
};
#endif