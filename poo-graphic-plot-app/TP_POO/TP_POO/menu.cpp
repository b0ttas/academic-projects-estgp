#include "menu.h"
Draw plot;

using namespace std;

void Menu::menu_plot() {
	
	int choice;
	
	plot.sub_print();
	int p = 0;
	double freq = 0, a = 0, vert_off = 0;

	while (1)
	{

		scanf_s("%i", &choice);
		switch (choice)
		{
		default:
			cout << "\n\t Invalido, Tente Novamente.\n\t";
			break;
		case(1): //Ficheiro
			
			cout << "\n\t Escolha um Ficheiro:\n";

			cout << "\n\t\t 1 - POO_201617_DAT01.csv";
			cout << "\n\t\t 2 - POO_201617_DAT02.csv";
			cout << "\n\t\t 3 - POO_201617_DAT03.csv\n\n\t";

				int ch;

				scanf_s("%i", &ch);
				switch (ch) 
				{
				default:
					cout << "\n\t Invalido, Tente Novamente.\n\t";
					break;
				case(1): //escolha do Ficheiro a ler
				case(2): //caminho do Ficheiro em D:\\Desktop
				case(3):
					plot.ClearScreen();
					plot.draw_graph();
					plot.draw_info(ch);

					int chfunc;

					scanf_s("%i", &chfunc);

					if (chfunc == 0) {
						plot.ClearScreen();
						menu();
					}

					else
					{
						cout << "\n\t Invalido, Tente Novamente.\n\t";
						scanf_s("%i", &chfunc);
					}
					break;
			}

		case(2): //sin
			cout << "Nr. de Periodos: ";
			cin >> p;

			cout << "Frequencia: ";
			cin >> freq;

			cout << "Amplitude (pico a pico): ";
			cin >> a;

			cout << "Offset: ";
			cin >> vert_off;

			plot.ClearScreen();
			plot.draw_graph();
			plot.draw_info_int(0, p, freq, a, vert_off);

			int ch0;

			scanf_s("%i", &ch0);

			if (ch0 == 0) {
				plot.ClearScreen();
				menu();
			}

			else
			{
				cout << "\n\t Invalido, Tente Novamente.\n\t";
				scanf_s("%i", &ch0);
			}

			break;

		case(3): //tri
			cout << "Nr. de Periodos: ";
			cin >> p;

			cout << "Frequencia: ";
			cin >> freq;

			cout << "Amplitude (pico a pico): ";
			cin >> a;

			cout << "Offset: ";
			cin >> vert_off;

			plot.ClearScreen();
			plot.draw_graph();
			plot.draw_info_int(1, p, freq, a, vert_off);

			int ch1;

			scanf_s("%i", &ch1);

			if (ch1 == 0) {
				plot.ClearScreen();
				menu();
			}

			else
			{
				cout << "\n\t Invalido, Tente Novamente.\n\t";
				scanf_s("%i", &ch1);
			}

			break;

		case(4): //quad
			cout << "Nr. de Periodos: ";
			cin >> p;

			cout << "Frequencia: ";
			cin >> freq;

			cout << "Amplitude (pico a pico): ";
			cin >> a;

			cout << "Offset: ";
			cin >> vert_off;

			plot.ClearScreen();
			plot.draw_graph();
			plot.draw_info_int(2, p, freq, a, vert_off);

			int ch2;

			scanf_s("%i", &ch2);

			if (ch2 == 0) {
				plot.ClearScreen();
				menu();
			}
			
			else
			{
				cout << "\n\t Invalido, Tente Novamente.\n\t";
				scanf_s("%i", &ch2);
			}

			break;

		case(0):
			plot.ClearScreen();
			menu();
			break;
		}
	}

}
void Menu::menu()
{
	int choice;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << '\n';
	cout << "| \t Graphic Plotting Program - TP POO" << "\t\t\t\t\t\t\t\t\t" << "a18013|";
	cout << '\n' << "|      \t\t\t\t\t\t\t\t\t\t\t\t\t\t      |";
	cout << '\n' << "-----------------------------------------------------------------------------------------------------------------------";

	cout << "\n\n\n\t" << " Escolha uma opcao:" << "\n\n";

	cout << "\n\t\t" << " 1 - Desenhar Grafico";
	cout << "\n\t\t" << " 2 - Ver Registo";
	cout << "\n\t\t" << " 3 - Exportar";

	cout << "\n\t\t" << " 0 - Sair" << "\n\n\t";


	while (1)
	{
		scanf_s("%i", &choice);
		switch (choice)
		{
		default:
			cout << "\n\t" << " Invalido, Tente Novamente." << "\n\t";
			break;
		case(1): //menu draw
			plot.ClearScreen();
			menu_plot();

			break;
		case(2): //menu registo
			plot.ClearScreen();
			plot.reg_print();
			plot.ClearScreen();
			menu();

		case(3): //exportar
			plot.ClearScreen();
			plot.export_reg_print();
			plot.ClearScreen();
			menu();
			break;
		case(0):
			exit(0);
			break;
		}
	}
}

Menu::Menu()
{
}

Menu::~Menu()
{
}
