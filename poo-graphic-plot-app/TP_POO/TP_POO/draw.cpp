#include "draw.h"

using namespace std;

Ficheiro file;
Registo reg;
Internos intern;

Draw::Draw()
{
}

Draw::~Draw()
{
}

void Draw::draw_graph()
{
	int i, j;
	
	for (i = 25; i >= 0; i--) //eixo yy, max chrs ->26
	{
		goto_xy(2, 27 - i + 1);	//col, lin
		if (i % 5 == 0)
		{
			cout << i; //nums em yy

			for (j = 0; j < 38; j++) //eixo xx, linhas aux
			{
				cout << "---";
			}
		}
		else
			cout << " |"; //marcacoes em  yy
	}

	for (i = 0; i <= 21; i++) //eixo xx, max chrs -> 114
	{
		goto_xy(4 + 5 * (i), 28); //eixo xx, marcacoes
		cout << "----+";

		goto_xy(7 + 5 * (i), 29); //escala xx, numeracao

		int k = i * 5 + 5;

		cout << k;  //indicadores dos valores da escala

	}

	fflush(stdout);
}
void Draw::draw_values(double xx_scl, double yy_scl, double curr_X, double curr_Y, double min_X, double min_Y, double max_X, double max_Y, int no_pts)
{
	int graph_pos_x, graph_pos_y;
	double interval_max_x = min_X + xx_scl, interval_max_y = min_Y + yy_scl; //limite de cada intervalo

	for (graph_pos_x = 0; graph_pos_x <= 114; graph_pos_x++)
	{
		//rotina para calcular as posições no graph
		//igual em yy, verifica se o valor e menor que o max do intervalo a verificar
		//pertencendo ao intervalo trava, caso false, pesquisa o prox intervalo
		if (curr_X <= interval_max_x)
		{
			break;
		}
		
		else
		{
			interval_max_x = interval_max_x + xx_scl;
		}
	}

	for (graph_pos_y = 0; graph_pos_y <= 25; graph_pos_y++)
	{
		//yy
		if (curr_Y <= interval_max_y)
		{
			break;
		}

		else
		{
			interval_max_y = interval_max_y + yy_scl;
		}
	}

	goto_xy(graph_pos_x + 3, 4 - graph_pos_y + 24);

	

	cout << "*";
}

void Draw::center(int line, int column, const char *s)
{
	//centra a string recebida
	goto_xy(line, column);
	printf("%*s%s%*s", 30 - (int)(strlen(s) / 2), " ", s, 30 - (int)(strlen(s) / 2), " ");

}

void Draw::draw_info(int ch)
{

	if (file.getFile(ch) == 1)
	{
		cout << "\n\n Ficheiro nao encontrado. Prima 0 para sair.";
		return;
	}

	file.lstComms(); //guarda os valores importantes da lista

	char buffer[80];
	double xx_scl, yy_scl;


	//calculo do intervalo da escala de acordo com os dados presentes na lista
	xx_scl = (file.max_X - file.min_X) / 114; //114 - number of available graph chrs
	yy_scl = (file.max_Y - file.min_Y) / 25; //ditto

	goto_xy(0, 0);
	cout << "\t Valores iniciais [X] " << file.min_X << " [Y] " << file.min_Y << " Escala(x,y) - " << xx_scl << ", " <<yy_scl;

	while (file.finish_flag != 1)
	{
		//vai buscar o ponto a desenhar
		file.lst_it();
		//print do cabeçalho
		sprintf_s(buffer, "Ponto a desenhar: %f xx , %f yy \t Estado: %i", file.curr_X, file.curr_Y, file.finish_flag);

		center(10, 1, buffer); //centra o cabeçalho

		Sleep(100); //desenha os pontos em intervalos
		draw_values(xx_scl, yy_scl, file.curr_X, file.curr_Y, file.min_X, file.min_Y, file.max_X, file.max_Y, file.no_pts); //marca os pontos no graph
	}

	file.lstComms(); //atualiza os valores importantes da lista

	goto_xy(0, 30);

	int vini, vfin;

	cout << "\n\tFiltro Media Movel - Existem " << file.no_pts << " valores para definir como intervalo\n";
	cout << "\tDefina os valores Inicial e Final do Intervalo\n\n";
	cout << "\tValor Inicial: ";
	cin >> vini;
	cout << "\tValor Final: ";
	cin >> vfin;

	file.mov_calc(vini, vfin); //envia os valores donde e calculada a media movel
	reg.SetReg(file.no_pts, file.file_org, file.max_X, file.max_Y, file.min_X, file.min_Y, file.vmedio, file.vquad, file.mov); //envia valores para a criacao do reg



	cout << "Valor Definido no Registo. Prima 0 para sair.";

	file.~Ficheiro(); //destroi os dados temporarios na classe ficheiro e lista, e faz o reset das flags
}

void Draw::draw_info_int(int ch, int p, double freq, double a, double vert_off)
{

	intern.getFunc(ch, p, freq, a, vert_off);

	char buffer[80];
	double xx_scl, yy_scl;

	intern.lstComms();

	//calculo do intervalo da escala de acordo com os dados presentes na lista
	xx_scl = (intern.max_X - intern.min_X) / 114; //114 - number of available graph chrs
	yy_scl = (intern.max_Y - intern.min_Y) / 25; //ditto

	goto_xy(0, 0);
	cout << "\t Valores iniciais [X] " << intern.min_X << " [Y] " << intern.min_Y << " Escala(x,y) - " << xx_scl << ", " << yy_scl;

	while (intern.finish_flag != 1)
	{
		//vai buscar o ponto a desenhar
		intern.lst_it();
		//print do cabeçalho
		sprintf_s(buffer, "Ponto a desenhar: %f xx , %f yy \t Estado: %i", intern.curr_X, intern.curr_Y, intern.finish_flag);

		center(10, 1, buffer); //centra o cabeçalho

		Sleep(100); //desenha os pontos em intervalos
		draw_values(xx_scl, yy_scl, intern.curr_X, intern.curr_Y, intern.min_X, intern.min_Y, intern.max_X, intern.max_Y, intern.no_pts); //marca os pontos no graph
	}

	intern.lstComms(); //atualiza os valores importantes da lista

	goto_xy(0, 30); 

	int vini, vfin;

	cout << "\n\tFiltro Media Movel - Existem " << intern.no_pts << " valores para definir como intervalo\n";
	cout << "\tDefina os valores Inicial e Final do Intervalo\n\n";
	cout << "\tValor Inicial: ";
	cin >> vini;
	cout << "\tValor Final: ";
	cin >> vfin;

	intern.mov_calc(vini, vfin); // envio dos parametros para o fmmovel
	reg.SetReg(intern.no_pts, intern.file_org, intern.max_X, intern.max_Y, intern.min_X, intern.min_Y, intern.vmedio, intern.vquad, intern.mov); //envia valores para a criacao do reg



	cout << "Valor Definido no Registo. Prima 0 para sair.";
	intern.~Internos(); //destroi os valores em Internos e LinkedList, faz reset as flags
}

void Draw::ClearScreen()
{
	//forked from stackoverflow
	//utilizacao dos comandos da consola para limpar todas as celulas da janela
	//enchendo-as com ' ', alternativa ao system("cls")

	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) 
		return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
		return;
	
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) 
		return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) 
		return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void Draw::reg_print()
{
	//chama a funcao de Registo que exibe os valores registados
	reg.reg_PRINT();
}

void Draw::export_reg_print()
{
	//chama a funcao de Registo que exporta os valores registados para um .txt
	reg.reg_EXPORT();
}
void Draw::sub_print()
{
	//print menu secundario
	cout << "-----------------------------------------------------------------------------------------------------------------------" << '\n';
	cout << "| \t Graphic Plotting Program - TP2 POO" << "\t\t\t\t\t\t\t\t\t" << "a18013|";
	cout << '\n' << "|      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      |";
	cout << '\n' << "-----------------------------------------------------------------------------------------------------------------------";

	cout << "\n\n\n\t Escolha uma opcao:\n\n";

	cout << "\n\t\t 1 - Ficheiro";
	cout << "\n\t\t 2 - SIN";
	cout << "\n\t\t 3 - TRI";
	cout << "\n\t\t 4 - QUAD";

	cout << "\n\t\t 0 - Voltar\n\n\t ";
}

void Draw::goto_xy(signed int x, signed int y)
{
	//utilizacao dos comandos da consola para
	//reposicionar o cursor segundo um sistema de coordenadas xy

	//forked
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}