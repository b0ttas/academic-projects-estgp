#include "Header.h"

void Keyboard(unsigned char Key, int x, int y)
{
	if (FlagDraw == 0 && MovePosicao == -1)
	{
		switch (Key)
		{
		case 27:
			exit(1);
			break;
		case '1':
			ActiveColor[0] = 255;
			ActiveColor[1] = 255;
			ActiveColor[2] = 255;
			glutPostRedisplay();
			printf("\tCor Ativa -> Branco.\n");
			break;
		case '2':
			ActiveColor[0] = 255;
			ActiveColor[1] = 255;
			ActiveColor[2] = 0;
			glutPostRedisplay();
			printf("\tCor Ativa -> Amarelo.\n");
			break;
		case '3':
			ActiveColor[0] = 255;
			ActiveColor[1] = 128;
			ActiveColor[2] = 0;
			glutPostRedisplay();
			printf("\tCor Ativa -> Laranja.\n");
			break;
		case '4':
			ActiveColor[0] = 255;
			ActiveColor[1] = 0;
			ActiveColor[2] = 0;
			glutPostRedisplay();
			printf("\tCor Ativa -> Vermelho.\n");
			break;
		case '5':
			ActiveColor[0] = 255;
			ActiveColor[1] = 0;
			ActiveColor[2] = 128;
			glutPostRedisplay();
			printf("\tCor Ativa -> Rosa.\n");
			break;
		case '6':
			ActiveColor[0] = 128;
			ActiveColor[1] = 0;
			ActiveColor[2] = 128;
			glutPostRedisplay();
			printf("\tCor Ativa -> Roxo.\n");
			break;
		case '7':
			ActiveColor[0] = 0;
			ActiveColor[1] = 255;
			ActiveColor[2] = 0;
			glutPostRedisplay();
			printf("\tCor Ativa -> Verde.\n");
			break;
		case '8':
			ActiveColor[0] = 0;
			ActiveColor[1] = 0;
			ActiveColor[2] = 255;
			glutPostRedisplay();
			printf("\tCor Ativa -> Azul.\n");
			break;
		case '9':
			ActiveColor[0] = 128;
			ActiveColor[1] = 64;
			ActiveColor[2] = 0;
			glutPostRedisplay();
			printf("\tCor Ativa -> Castanho.\n");
			break;
		case '0':
			ActiveColor[0] = 0;
			ActiveColor[1] = 0;
			ActiveColor[2] = 0;
			glutPostRedisplay();
			printf("\tCor Ativa -> Preto.\n");
			break;
		case 43:
			if (ActiveForm == PolRegConvexo && Mode == InsertMode)
			{
				NumSidesPolConvexo++;
				if (NumSidesPolConvexo == 101) NumSidesPolConvexo = 100;
				printf("\t%i Lados para Poligonos Regulares Convexos.\n", NumSidesPolConvexo);
			}
			else if (ActiveForm == PolRegNaoConvexo && Mode == InsertMode)
			{
				NumPontasPolNaoConvexo++;
				if (NumPontasPolNaoConvexo == 101) NumPontasPolNaoConvexo = 100;
				printf("\t%i Pontas para Poligonos Regulares Nao Convexos.\n", NumPontasPolNaoConvexo);
			}
			else if (Mode == RotateMode)
			{
				Angulo++;
				if (Angulo == 361)	Angulo = 1;
				printf("\tRotacao de %f Graus.\n", Angulo);
			}
			else
			{
				printf("\tNao e Possivel fazer alteracoes de momento.\n");
			}
			break;
		case 'c':
		case 'C':
			printf("\tModo Contorno Ativado.\n");
			printf("\t1 Clique para Mudar Contorno da Figura Selecionada para Cor Ativa.\n");
			Mode = OutlineMode;
			break;
		case 'd':
		case 'D':
			printf("\tFiguras Apagadas.\n");
			for (int i = (NFormas -1); i >= 0; i--)
			{
				ApagaForma(formas[i]);
				NFormas--;
			}
			glutPostRedisplay();
			break;
		case 45:
			if (ActiveForm == PolRegConvexo && Mode == InsertMode)
			{
				NumSidesPolConvexo--;
				if (NumSidesPolConvexo == 4) NumSidesPolConvexo = 5;
				printf("\t%i Lados para Poligonos Regulares Convexos.\n", NumSidesPolConvexo);
			}
			else if (ActiveForm == PolRegNaoConvexo && Mode == InsertMode)
			{
				NumPontasPolNaoConvexo--;
				if (NumPontasPolNaoConvexo == 3) NumPontasPolNaoConvexo = 4;
				printf("\t%i Pontas para Poligonos Regulares Nao Convexos.\n", NumPontasPolNaoConvexo);
			}
			else if (Mode == RotateMode)
			{
				Angulo --;
				if (Angulo == -361)	Angulo = -1;
				printf("\tRotacao de %f Graus.\n", Angulo);
			}
			else
			{
				printf("\tNao e Possivel fazer alteracoes de momento.\n");
			}
			break;
		default:
			printf("Carregou numa Tecla Desconhecida...\n");
			break;
		}
	}
}