#include "Internos.h"

using namespace std;
LinkedList int_lst;

void Internos::getFunc(int ch, int p, double freq, double a, double vert_off)
{
	x = 0; //ponto inicial na escala temporal
	double const pi = 3.14;

	if (ch == 0) //sin
	{
		for (int i = 0; i < 114; i++)
		{
			double ang_freq;

			ang_freq = freq * 2 * pi; //frequencia angular segundo o periodo

			//calculo dos valores de y atraves da funcao seno
			y = a * sin((ang_freq * x)) + vert_off;

			double pd = 2 * pi / ang_freq; //periodo da funcao seno

			int_lst.file_org = 1; //definicao da flag p/ origem dos valores na lista
			int_lst.appendNodeOrder(x, y); //envio dos valores para a lista


			x = x + p*(pd / 114); //incremento de x de acordo com o num de periodos definido e a area de desennho
		}
	}

	else if (ch == 1)//tri
	{
		for (int i = 0; i < 114; i++)
		{
			double pd = (1 / freq); //periodo da funcao

			//calculo dos valores de y atraves da funcao triangular
			y = (((2*a) / pi)*asin(sin((2*pi*x )/ pd))) + vert_off;

			int_lst.file_org = 1; //definicao da flag p/ origem dos valores na lista
			int_lst.appendNodeOrder(x, y); //envio dos valores para a lista


			x = x + p*(pd / 114); //incremento de x de acordo com o num de periodos definido e a area de desennho
		}
	}

	else if (ch == 2)//quad
	{
		x = 1;

		for (int i = 0; i < 114; i++) 
		{
			double pd = (1 / freq);//periodo da funcao

			//calculo dos valores de y atraves da funcao quadrada
			y = (a * (1/sin((2 * pi*x)/ pd)) * abs(sin((2 * pi*x) / pd))) + vert_off;

			int_lst.file_org = 1; //definicao da flag p/ origem dos valores na lista
			int_lst.appendNodeOrder(x, y); //envio dos valores para a lista


			x = x + p*(pd / 114); //incremento de x de acordo com o num de periodos definido e a area de desennho
		}
	}
}

void Internos::lstComms()
{
	//redefinicao de variaveis, para facilitar o codigo

	curr_X = int_lst.curr_X;
	curr_Y = int_lst.curr_Y;
	min_X = int_lst.min_X;
	min_Y = int_lst.min_Y;
	max_X = int_lst.max_X;
	max_Y = int_lst.max_Y;
	no_pts = int_lst.nopts;
	finish_flag = int_lst.finish_flag;
	file_org = int_lst.file_org;
	vmedio = int_lst.vmedio;
	vquad = int_lst.vquad;
	mov = int_lst.mov;
}

void Internos::mov_calc(int vini, int vfin)
{
	//recebe os valores para o calculo da media movel
	int_lst.dispNodesGap(vini, vfin);
	lstComms();
}

void Internos::lst_it()
{
	//recebe o node comos valores a desenhar
	int_lst.ReceiveNode();
	lstComms();
}
Internos::Internos()
{
	x = 0;
	y = 0;
}
Internos::~Internos()
{
	int_lst.nopts = 0;
	int_lst.finish_flag = 0;
	int_lst.~LinkedList();
}