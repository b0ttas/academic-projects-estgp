#include "Ficheiro.h"

using namespace std;
LinkedList file_lst;

int Ficheiro::getFile(int ch)
{

	if (ch == 1)
	{
		ifstream myfile("D:\\Desktop\\POO_201617_DAT01.csv");

		if (myfile.is_open())
		{
			while (getline(myfile, line)) //leitura linha
			{
				string delimiter = ";";
				xx = line.substr(0, line.find(delimiter)); //obtem xx
				yy = line.substr(line.find(delimiter) + 1); //obtem yy

				//std::replace, pega na string, e substitui 'a', por 'b'
				//substituiu-se ',' por '.' devido ás condições de importação
				//decimais são expressos por '.' quando não está definido um locale apropriado

				replace(xx.begin(), xx.end(), ',', '.');
				replace(yy.begin(), yy.end(), ',', '.');

				x = stod(xx);
				y = stod(yy);

				file_lst.file_org = 0;
				file_lst.appendNodeOrder(x, y);
			}
			myfile.close();
			return 0;
		}

		else
			return 1;
	}

	if (ch == 2)
	{
		ifstream myfile("D:\\Desktop\\POO_201617_DAT02.csv");

		if (myfile.is_open())
		{
			while (getline(myfile, line)) //leitura linha
			{
				string delimiter = ";";
				xx = line.substr(0, line.find(delimiter)); //obtem xx
				yy = line.substr(line.find(delimiter) + 1); //obtem yy

				//std::replace, pega na string, e substitui 'a', por 'b'
				replace(xx.begin(), xx.end(), ',', '.');
				replace(yy.begin(), yy.end(), ',', '.');

				x = stod(xx);
				y = stod(yy);

				file_lst.file_org = 0;
				file_lst.appendNodeOrder(x, y);
			}
			myfile.close();
			return 0;
		}

		else
			return 1;
	}

	if (ch == 3)
	{
		ifstream myfile("D:\\Desktop\\POO_201617_DAT03.csv");

		if (myfile.is_open())
		{
			while (getline(myfile, line)) //leitura linha
			{
				string delimiter = ";";
				xx = line.substr(0, line.find(delimiter)); //obtem xx
				yy = line.substr(line.find(delimiter) + 1); //obtem yy

				//std::replace, pega na string, e substitui 'a', por 'b'
				replace(xx.begin(), xx.end(), ',', '.');
				replace(yy.begin(), yy.end(), ',', '.');

				x = stod(xx);
				y = stod(yy);

				file_lst.file_org = 0;
				file_lst.appendNodeOrder(x, y);
			}
			myfile.close();
			return 0;
		}

		else
			return 1;
	}
	return 0;
}

void Ficheiro::lstComms()
{
	//grab dos valores na lista criada para variaveis em Ficheiro
	curr_X = file_lst.curr_X;
	curr_Y = file_lst.curr_Y;
	min_X = file_lst.min_X;
	min_Y = file_lst.min_Y;
	max_X = file_lst.max_X;
	max_Y = file_lst.max_Y;
	no_pts = file_lst.nopts;
	finish_flag = file_lst.finish_flag;
	file_org = file_lst.file_org;
	vmedio = file_lst.vmedio;
	vquad = file_lst.vquad;
	mov = file_lst.mov;
}

void Ficheiro::mov_calc(int vini, int vfin)
{
	//envia valores recebidos para o calculo da fmmóvel
	file_lst.dispNodesGap(vini, vfin);
	//atualiza os valores guardados da lista
	lstComms();
}

void Ficheiro::lst_it()
{
	//recebe o node com o ponto a desenhar
	file_lst.ReceiveNode();
	//atualiza os valores guardados
	lstComms();
}
Ficheiro::Ficheiro()
{
	x = 0;
	y = 0;
}
Ficheiro::~Ficheiro()
{
	//destrutor com a limpeza das flags, vars, e chamada ao destrutor da lista
	file_lst.nopts = 0;
	file_lst.finish_flag = 0;
	file_lst.~LinkedList();
}