#include "Header.h"

void Rato(GLint Button, GLint State, GLint x, GLint y)
{
	switch (Mode)
	{
		case InsertMode:
			RatoCriaForma (Button, State, x, y);
			break;
		case DeleteMode:
			RatoApagaForma (Button, State, x, y);
			break;
		case MoveMode:
			RatoMoveForma(Button, State, x, y);
			break;
		case RotateMode:
			RatoRotateForma(Button, State, x, y);
			break;
		case OutlineMode:
			RatoContornoForma(Button, State, x, y);
			break;
		default:
			break;
	}
}

void MoveRato(int x, int y)
{
	y = hSize - y;
	
	if (Mode == MoveMode && MovePosicao != -1)
	{
		DesenhaForma(formas[MovePosicao], 1);
		UpdateForma(formas[MovePosicao], x - xMove, y - yMove);
		DesenhaForma(formas[MovePosicao], 1);
		xMove = x;
		yMove = y;
	}
	if (FlagDraw == 1)
	{
		DesenhaForma(formas[NFormas], 1);
		formas[NFormas]->xfinal = x;
		formas[NFormas]->yfinal = y;
		DesenhaForma(formas[NFormas], 1);
	}
}

void RatoCriaForma(GLint Button, GLint State, GLint x, GLint y)
{
	if (Button == GLUT_LEFT_BUTTON && State==GLUT_DOWN && InsidePalette(x, hSize - y) == 1)
	{
		printf("\tDentro da Palette de Cores.\n");
		if (FlagDraw == 0)
		{
			AlteraCor(x, hSize - y);
			glutPostRedisplay();
		}
	}
	else if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN && InsidePalette2(x, hSize - y) == 1)
	{
		printf("\tDentro da Palette de Tools.\n");
		if (FlagDraw == 0)
		{
			AlteraTool(x, hSize - y);
			glutPostRedisplay();
		}
	}
	else if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		if (FlagDraw == 0)
		{
			if (NFormas < NMaxFormas)
			{
				formas[NFormas] = CriaVerificaTipo(ActiveForm, x, hSize-y, x, hSize-y);
				printf("\tForma Iniciada na Posicao (%i,%i).\n", x, hSize - y);
				FlagDraw = 1;
				DesenhaForma (formas[NFormas], 1);
			}
			else
			{
				printf("\t\tImpossivel Inserir mais Formas.Experimente Apagar Algumas.\n");
			}
		}
		else
		{	
			if(formas[NFormas]->xfinal == formas[NFormas]->xinicial || formas[NFormas]->yfinal == formas[NFormas]->yinicial)
			{
				printf("Posicao Final Invalida.\n");
			}
			else
			{	
				DesenhaForma(formas[NFormas], 1);
				printf("\tForma Terminada na Posicao (%i,%i).\n", x, hSize - y);
				NFormas++;
				FlagDraw = 0;
				glutPostRedisplay();
			}
		}
	}
}

void RatoApagaForma(GLint Button, GLint State, GLint x, GLint y)
{
	int ApagarForma = -1;
	int i;

	y = hSize - y;

	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN && InsidePalette(x, y) == 1)
	{
		printf("\tDentro da Palette de Cores.\n");
		AlteraCor(x, y); 
		glutPostRedisplay();
	}
	else if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN && InsidePalette2(x, y) == 1)
	{
		printf("\tDentro da Palette de Tools.\n");
		AlteraTool(x, y); 
		glutPostRedisplay();
	}
	else if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		ApagarForma = PickForma(x, y);

		if (ApagarForma != -1)
		{
			printf("Forma %i Apagada.\n", ApagarForma+1);
			
			ApagaForma(formas[ApagarForma]);
			
			for (i = ApagarForma; i<NFormas - 1; i++)
				formas[i] = formas[i + 1];
			
			NFormas--;
			
			glutPostRedisplay();
		}
		else
			printf("\tNenhuma forma seleccionada.\n");
	}
}

void RatoMoveForma(GLint Button, GLint State, GLint x, GLint y)
{
	y = hSize - y;

	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN && InsidePalette(x, y) == 1)
	{
		printf("\tDentro da Palette de Cores.\n");
		if (MovePosicao == -1)
		{
			AlteraCor(x, y);
			glutPostRedisplay();
		}
	}
	else if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN && InsidePalette2(x, y) == 1)
	{
		printf("\tDentro da Palette de Tools.\n");
		if (MovePosicao == -1)
		{
			AlteraTool(x, y);
			glutPostRedisplay();
		}
	}
	else if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		if (MovePosicao == -1)
		{
			MovePosicao = PickForma(x, y);
			
			if (MovePosicao != -1)
			{
				xMove = x;
				yMove = y;
				DesenhaForma(formas[MovePosicao], 1);
				printf("\tForma %i Seleccionada para Mover.\n", MovePosicao+1);
			}
			else
				printf("Nenhuma forma seleccionada!\n");
		}
		else
		{
			DesenhaForma(formas[MovePosicao], 1);
			UpdateForma(formas[MovePosicao], x - xMove, y - yMove);
			
			printf("Forma %i Movida para a Posicao Final.\n", MovePosicao+1);
			
			MovePosicao = -1;
			glutPostRedisplay();
		}
	}
}

void RatoRotateForma(GLint Button, GLint State, GLint x, GLint y)
{
	y = hSize - y;
	
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN && InsidePalette(x, y) == 1)
	{
		printf("\tDentro da Palette de Cores.\n");
		if (FlagRotate == -1)
		{
			AlteraCor(x, y);
			glutPostRedisplay();
		}
	}
	else if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN && InsidePalette2(x, y) == 1)
	{
		printf("\tDentro da Palette de Tools.\n");
		if (FlagRotate == -1)
		{
			AlteraTool(x, y);
			glutPostRedisplay();
		}
	}
	else if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		if (FlagRotate == -1)
		{
			FlagRotate = PickForma(x, y);

			if (FlagRotate != -1)
			{
				DesenhaForma(formas[FlagRotate], 1);
				printf("\tForma %i Seleccionada para Rodar.\n", FlagRotate + 1);
			}
			else
				printf("Nenhuma Forma Seleccionada!\n");
		}
		else
		{
			FlagRotate = -1;
			printf("\tA Forma Nao esta mais Selecionada para Rodar.\n");
		}
	}
	if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)
	{
		if(FlagRotate != -1)
		{
			DesenhaForma(formas[FlagRotate], 1);
			IncrementoAngulo(formas[FlagRotate]);
			printf("\tForma %i Rodada.\n", MovePosicao + 1);
			glutPostRedisplay();
		}
	}
}

void RatoContornoForma(GLint Button, GLint State, GLint x, GLint y)
{
	int MudaContorno = -1;
	int i;

	y = hSize - y;

	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN && InsidePalette(x, y) == 1)
	{
		printf("\tDentro da Palette de Cores.\n");
		AlteraCor(x, y);
		glutPostRedisplay();
	}
	else if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN && InsidePalette2(x, y) == 1)
	{
		printf("\tDentro da Palette de Tools.\n");
		AlteraTool(x, y);
		glutPostRedisplay();
	}
	else if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		MudaContorno = PickForma(x, y);

		if (MudaContorno != -1)
		{
			printf("Contorno Forma %i Alterado.\n", MudaContorno + 1);

			MudaContornoForma(formas[MudaContorno]);
			glutPostRedisplay();
		}
		else
			printf("\tNenhuma forma seleccionada.\n");
	}
}
