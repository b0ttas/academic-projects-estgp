#include "Registo.h"

using namespace std;

void Registo::SetReg(int nopts, int file_org, double xmax, double ymax, double xmin, double ymin, double vmedio, double vquad, double mov)
{
	if (i == 10) //caso o proximo reg seja o 11o
	{
		i = 0;
	}

	if (i < 10) {
		registry[i].reg_NO = i+1; //marca o nr do reg

		//guarda os valores importantes na struct
		registry[i].func_VALS = nopts; 
		registry[i].Reg_xMax = xmax;
		registry[i].Reg_yMax = ymax;
		registry[i].Reg_xMin = xmin;
		registry[i].Reg_yMin = ymin;

		registry[i].Reg_vmedio = vmedio;
		registry[i].Reg_vquad = vquad;
		registry[i].Reg_mov = mov;



		if (file_org == 0)
		{
			registry[i].reg_ORIGIN = "Ficheiro";
			
		}

		if (file_org == 1)
		{
			registry[i].reg_ORIGIN = "Interno";
		}


		//grab da timestamp
		time_t rawtime;
		struct tm timeinfo;
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		ostringstream oss;
		oss << std::put_time(&timeinfo, "%d-%m-%Y %H-%M-%S");
		string time_str = oss.str();

		registry[i].time_str = time_str;
	}
	i++;
}

void Registo::reg_PRINT()
{
		//exibicao dos dados do registo no ecra

		if (i == 0) //caso não existam registos
		{
			int choice;
			cout << "\n\n\t Nao existem registos a mostrar, experiemente fazer o plot de algumas funcoes.";
			cout << "\n\tPrima 0 para sair para o menu.\n\n\t";
			cin >> choice;

			if (choice == 0)
			{
				return;
			}
		}
		else {
			//print do array reg

			for (int j = 0; j < 10; j++) {
				if (registry[j].reg_NO != 0) 
				{
					cout << "  ____________________________________________ \n";
					cout << " |                                            |\n";
					if (registry[j].reg_NO != 10)
					{
						cout << " |    Registo " << registry[j].reg_NO << "				      |\n"; //print nr do registo
					}
					else
					{
						cout << " |    Registo " << registry[j].reg_NO << "				     |\n"; //print nr do registo
					}
					
					cout << " |                                            |\n";
					cout << " |    Origem: " << registry[j].reg_ORIGIN << " 		              |\n";   //print origem do reg
					cout << " |    Numero de valores: " << registry[j].func_VALS << " 	              |\n";//print nr vals da funcao
					cout << " |____________________________________________|\n\n";
					cout << "  Maximos (x,y) " << registry[j].Reg_xMax << ", " << registry[j].Reg_yMax << "\n";
					cout << "  Minimos (x,y) " << registry[j].Reg_xMin << ", " << registry[j].Reg_yMin << "\n";

					cout << "  Valor Medio " << registry[j].Reg_vmedio << "\n";
					cout << "  Media Quadratica " << registry[j].Reg_vquad << "\n";
					cout << "  Media Movel " << registry[j].Reg_mov << "\n";

					cout << "  TimeStamp: " << registry[j].time_str << "\n"; //print data associada ao registo	
					//filtro med movel, definir x interval em input
					//vmedio e media quad
					//export ficheiro
					cout << "\n";
					char ch = '1';

					do
					{													 ///mais detalhes como média, etc aqui
						cout << "\n\tPrima 0 para continuar\n";
						cin >> ch;
					} while (ch != '0');

				}
			}

		}
}

int Registo::reg_EXPORT()
{
	//criacao do log.txt com os dados manipulados exportados
	if (i == 0)
	{
		int choice;
		cout << "\n\n\t Nao existem registos a exportar, experiemente fazer o plot de algumas funcoes.";
		cout << "\n\tPrima 0 para sair para o menu.\n\n\t";
		cin >> choice;

		if (choice == 0)
		{
			return 0;
		}
	}
	else {

		ofstream fout("log.txt");
		if (!fout) {
			cerr << "Could not open file." << endl;
			return 1;
		}
		for (int j = 0; j < 10; j++) {
			if (registry[j].reg_NO != 0)
			{
				fout << "  ____________________________________________ \n";
				fout << " |                                            |\n";
				if (registry[j].reg_NO != 10)
				{
					fout << " |    Registo " << registry[j].reg_NO << "				      |\n"; //print nr do registo
				}
				else
				{
					fout << " |    Registo " << registry[j].reg_NO << "				     |\n"; //print nr do registo
				}

				fout << " |                                            |\n";
				fout << " |    Origem: " << registry[j].reg_ORIGIN << " 		              |\n";   //print origem do reg
				fout << " |    Numero de valores: " << registry[j].func_VALS << " 	              |\n";//print nr vals da funcao
				fout << " |____________________________________________|\n\n";
				fout << "  Maximos (x,y) " << registry[j].Reg_xMax << ", " << registry[j].Reg_yMax << "\n";
				fout << "  Minimos (x,y) " << registry[j].Reg_xMin << ", " << registry[j].Reg_yMin << "\n";

				fout << "  Valor Medio " << registry[j].Reg_vmedio << "\n";
				fout << "  Media Quadratica " << registry[j].Reg_vquad << "\n";
				fout << "  Media Movel " << registry[j].Reg_mov << "\n";

				fout << "  TimeStamp: " << registry[j].time_str << "\n";
				fout << "\n";
			}
		}
		fout.close();
		
		int choice;

		cout << "\n\n\t Ficheiro exportado com sucesso.";
		cout << "\n\tPrima 0 para sair para o menu.\n\n\t";
		cin >> choice;

		if (choice == 0)
		{
			return 0;
		}
	}
	return 0;
}

Registo::Registo()
{
	reg registry[10] = {0};
	int i = 0;
}

Registo::~Registo()
{
	reg registry[10] = {0};
	int i = 0;
}