#include "Header.h"

void DefinePalette(int x, int y, int xSize, int ySize)
{
	CPalette.xInicial = x;
	CPalette.yInicial = y;
	CPalette.xSize = xSize;
	CPalette.ySize = ySize;
	CPalette.GridSize = CPalette.xSize / NumColors;
	CPalette.xBoxSize = CPalette.GridSize;
	CPalette.yBoxSize = ySize;
}

void DesenhaPalette()
{
	int i;

	for (i = 0; i < NumColors; i++) {

		glColor3ub(CoresPaletteRGB[i][0],CoresPaletteRGB[i][1],CoresPaletteRGB[i][2]);

		glBegin(GL_POLYGON);
		glVertex2i(CPalette.xInicial + (i*CPalette.GridSize), CPalette.yInicial);
		glVertex2i(CPalette.xInicial + (i*CPalette.GridSize), CPalette.yInicial + CPalette.yBoxSize);
		glVertex2i(CPalette.xInicial + CPalette.xBoxSize + (i*CPalette.GridSize), CPalette.yInicial + CPalette.yBoxSize);
		glVertex2i(CPalette.xInicial + CPalette.xBoxSize + (i*CPalette.GridSize), CPalette.yInicial);
		glEnd();
		glColor3ub(0, 0, 128);
		glBegin(GL_LINE_LOOP);
		glVertex2i(CPalette.xInicial + (i*CPalette.GridSize), CPalette.yInicial);
		glVertex2i(CPalette.xInicial + (i*CPalette.GridSize), CPalette.yInicial + CPalette.yBoxSize);
		glVertex2i(CPalette.xInicial + CPalette.xBoxSize + (i*CPalette.GridSize), CPalette.yInicial + CPalette.yBoxSize);
		glVertex2i(CPalette.xInicial + CPalette.xBoxSize + (i*CPalette.GridSize), CPalette.yInicial);
		glEnd();
		glFlush();
	}
}

int InsidePalette(int x , int y)
{
	if (x >= CPalette.xInicial && x <= CPalette.xSize && y >= CPalette.yInicial && y <= CPalette.ySize)	return 1;
	else return -1;
}

int *GetColorPalette(int x, int y)
{
	int i;

	for (i = 0; i < NumColors; i++)
	{
		if ((x > CPalette.xInicial + (i*CPalette.GridSize)) && 
			(x < CPalette.xInicial + CPalette.xBoxSize + (i*CPalette.GridSize)) &&
			(y > CPalette.yInicial) && 
			(y < CPalette.yInicial + CPalette.yBoxSize))
			return CoresPaletteRGB[i];
	}
	return NULL;
}

void AlteraCor(int x, int y)
{
	int *Cor = GetColorPalette(x, y);
	int i;

	if (Cor == NULL) return;

	for (i = 0; i < 3; i++)
	{
		ActiveColor[i] = Cor[i];
	}
}

void DefinePalette2(int x, int y, int xSize, int ySize)
{
	TPalette.xInicial = x;
	TPalette.yInicial = y;
	TPalette.xSize = xSize;
	TPalette.ySize = ySize;
	TPalette.GridSize = TPalette.xSize / NumTools;
	TPalette.xBoxSize = TPalette.GridSize;
	TPalette.yBoxSize = ySize;
}

void DesenhaPalette2()
{
	int i;
	const double PI = 3.14159265358979323846;
	int Counter = 0;
	const float DegToRad = (3.14159265358979323846 / 180);

	for (i = 0; i < NumTools; i++)
	{
		glColor3ub(255, 255, 255);
		glBegin(GL_POLYGON);
		glVertex2i(TPalette.xInicial + (i*TPalette.GridSize), TPalette.yInicial);
		glVertex2i(TPalette.xInicial + (i*TPalette.GridSize), TPalette.yInicial - TPalette.yBoxSize);
		glVertex2i(TPalette.xInicial + TPalette.xBoxSize + (i*TPalette.GridSize), TPalette.yInicial - TPalette.yBoxSize);
		glVertex2i(TPalette.xInicial + TPalette.xBoxSize + (i*TPalette.GridSize), TPalette.yInicial);
		glEnd();
		glColor3ub(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(TPalette.xInicial + (i*TPalette.GridSize), TPalette.yInicial);
		glVertex2i(TPalette.xInicial + (i*TPalette.GridSize), TPalette.yInicial - TPalette.yBoxSize);
		glVertex2i(TPalette.xInicial + TPalette.xBoxSize + (i*TPalette.GridSize), TPalette.yInicial - TPalette.yBoxSize);
		glVertex2i(TPalette.xInicial + TPalette.xBoxSize + (i*TPalette.GridSize), TPalette.yInicial);
		glEnd();
		
		if (i == 0)
		{
			glColor3ub(ActiveColor[0], ActiveColor[1], ActiveColor[2]);
			glBegin(GL_POLYGON);
			glVertex2i(TPalette.xInicial + (i*TPalette.GridSize), TPalette.yInicial);
			glVertex2i(TPalette.xInicial + (i*TPalette.GridSize), TPalette.yInicial - TPalette.yBoxSize);
			glVertex2i(TPalette.xInicial + TPalette.xBoxSize + (i*TPalette.GridSize), TPalette.yInicial - TPalette.yBoxSize);
			glVertex2i(TPalette.xInicial + TPalette.xBoxSize + (i*TPalette.GridSize), TPalette.yInicial);
			glEnd();
			glColor3ub(0, 0, 128);
			glBegin(GL_LINE_LOOP);
			glVertex2i(TPalette.xInicial + (i*TPalette.GridSize), TPalette.yInicial);
			glVertex2i(TPalette.xInicial + (i*TPalette.GridSize), TPalette.yInicial - TPalette.yBoxSize);
			glVertex2i(TPalette.xInicial + TPalette.xBoxSize + (i*TPalette.GridSize), TPalette.yInicial - TPalette.yBoxSize);
			glVertex2i(TPalette.xInicial + TPalette.xBoxSize + (i*TPalette.GridSize), TPalette.yInicial);
			glEnd();
		}
		else if (i == 1)
		{
			if (Mode == InsertMode)
			{
				glColor3ub(0, 255, 0);
				glBegin(GL_LINE_LOOP);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize / 2);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize / 2);
				glEnd();
				glBegin(GL_LINE_LOOP);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - TPalette.yBoxSize *0.1);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - TPalette.yBoxSize *0.9);
				glEnd();
			}
			else if (Mode == DeleteMode)
			{
				glColor3ub(255, 0, 0);
				glBegin(GL_LINE_LOOP);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize *0.1);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize *0.9);
				glEnd();
				glBegin(GL_LINE_LOOP);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize *0.9);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize *0.1);
				glEnd();
			}
			else if (Mode == MoveMode)
			{
				glColor3ub(0, 0, 255);
				glBegin(GL_LINE_LOOP);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize / 2);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize / 2);
				glEnd();
				glBegin(GL_LINE_LOOP);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - TPalette.yBoxSize / 4);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize / 2);
				glEnd();
				glBegin(GL_LINE_LOOP);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - (TPalette.yBoxSize / 4) * 3);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize / 2);
				glEnd();
			}
			else if (Mode == RotateMode)
			{
				glColor3ub(128, 0, 128);
				glBegin(GL_LINE_LOOP);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - (TPalette.yBoxSize / 4) * 3);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - (TPalette.yBoxSize / 4) * 3);
				glEnd();
				glBegin(GL_LINE_LOOP);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - (TPalette.yBoxSize / 4) * 3);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize / 4);
				glEnd();
				glBegin(GL_LINE_LOOP);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize / 4);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - TPalette.yBoxSize / 4);
				glEnd();
				glBegin(GL_LINE_LOOP);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.7), hSize - TPalette.yBoxSize / 8);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - TPalette.yBoxSize / 4);
				glEnd();
				glBegin(GL_LINE_LOOP);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.7), hSize - (TPalette.yBoxSize / 4)*1.5);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - TPalette.yBoxSize / 4);
				glEnd();
			}
		}
		else if (i == 2)
		{
			if (ActiveForm == Quadrado)
			{
				glColor3ub(0, 0, 0);
				if (wSize <= 700)
				{
					glBegin(GL_POLYGON);
					glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize*0.1);
					glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize*0.8);
					glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize*0.8);
					glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize*0.1);
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.3), hSize - TPalette.yBoxSize*0.05);
					glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.3), hSize - TPalette.yBoxSize*0.85);
					glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.7), hSize - TPalette.yBoxSize*0.85);
					glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.7), hSize - TPalette.yBoxSize*0.05);
					glEnd();
				}
			}
			else if (ActiveForm == Linha)
			{
				glColor3ub(0, 0, 0);
				glBegin(GL_LINE_LOOP);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize / 2);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize / 2);
				glEnd();
			}
			else if (ActiveForm == Triangulo)
			{
				glColor3ub(0, 0, 0);
				glBegin(GL_POLYGON);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize*0.8);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - TPalette.yBoxSize*0.2);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize*0.8);
				glEnd();
			}
			else if (ActiveForm == Retangulo)
			{
				glColor3ub(0, 0, 0);
				glBegin(GL_POLYGON);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize*0.3);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize*0.7);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize*0.7);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize*0.3);
				glEnd();
			}
			else if (ActiveForm == Circulo)
			{
				glColor3ub(0, 0, 0);
				glBegin(GL_POLYGON);
				for (int j = 0; j < 100; j++)
				{
					float angle = j * 2 * PI / 100;
				
					if (wSize <= 700)
						glVertex2f((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + (TPalette.xBoxSize*0.3)*cos(angle), (hSize - TPalette.yBoxSize*0.5) + (TPalette.xBoxSize*0.3)*sin(angle));
					else
						glVertex2f((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + (TPalette.xBoxSize*0.2)*cos(angle), (hSize - TPalette.yBoxSize*0.5) + (TPalette.xBoxSize*0.2)*sin(angle));
				}
				glEnd();
			}
			else if (ActiveForm == PolRegConvexo)
			{
				glColor3ub(0, 0, 0);
				glBegin(GL_POLYGON);
				for (int j = 0; j < 5; j++)
				{
					float angle = j * 2 * PI / 5;
						

					if (wSize <= 700)
						glVertex2f((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + (TPalette.xBoxSize*0.3)*cos(angle), (hSize - TPalette.yBoxSize*0.5) + (TPalette.xBoxSize*0.3)*sin(angle));
					else
						glVertex2f((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + (TPalette.xBoxSize*0.2)*cos(angle), (hSize - TPalette.yBoxSize*0.5) + (TPalette.xBoxSize*0.2)*sin(angle));
				}
				glEnd();
			}
			else if (ActiveForm == PolRegNaoConvexo)
			{
				glColor3ub(0, 0, 0);
				glBegin(GL_TRIANGLE_FAN);
				for (int j = 0; j < 5 * 2; j++)
				{
					float DegInRad = j * 360.0 / 5 * 2 * DegToRad;

					if (Counter % 2 != 0)
					{
						if (wSize <= 700)
							glVertex2f(((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + cos(DegInRad) * (TPalette.xBoxSize*0.4)), ((hSize - TPalette.yBoxSize*0.5) + sin(DegInRad) * (TPalette.xBoxSize*0.4)));
						else
							glVertex2f(((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + cos(DegInRad) * (TPalette.xBoxSize*0.3)), ((hSize - TPalette.yBoxSize*0.5) + sin(DegInRad) * (TPalette.xBoxSize*0.3)));
					}
					else
					{
						if (wSize <= 700)
							glVertex2f(((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + cos(DegInRad) * (TPalette.xBoxSize*0.4) / 2), ((hSize - TPalette.yBoxSize*0.5) + sin(DegInRad) * (TPalette.xBoxSize*0.4) / 2));
						else
							glVertex2f(((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + cos(DegInRad) * (TPalette.xBoxSize*0.25) / 2), ((hSize - TPalette.yBoxSize*0.5) + sin(DegInRad) * (TPalette.xBoxSize*0.25) / 2));

					}
					Counter++;
				}
				glEnd();
			}
		}
		else if (i == 3)
		{
			glColor3ub(255, 255, 255);
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) , hSize - TPalette.yBoxSize);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize), hSize - TPalette.yBoxSize);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize), hSize );
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize), hSize);
			glEnd();
		}
		else if (i == 4)
		{
			glColor3ub(0, 255, 0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize-TPalette.yBoxSize/2);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize-TPalette.yBoxSize/2);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - TPalette.yBoxSize *0.1);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - TPalette.yBoxSize *0.9);
			glEnd();
		}
		else if (i == 5)
		{
			glColor3ub(255, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize *0.1);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize *0.9);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize *0.9);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize *0.1);
			glEnd();
		}
		else if (i == 6)
		{
			glColor3ub(0, 0, 255);
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize / 2);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize / 2);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - TPalette.yBoxSize / 4);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize / 2);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - (TPalette.yBoxSize / 4)*3);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize / 2);
			glEnd();
		}
		else if (i == 7)
		{
			glColor3ub(128, 0, 128);
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - (TPalette.yBoxSize / 4)*3);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - (TPalette.yBoxSize / 4)*3);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - (TPalette.yBoxSize / 4)*3);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize / 4);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize / 4);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - TPalette.yBoxSize / 4);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.7), hSize - TPalette.yBoxSize / 8);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - TPalette.yBoxSize / 4);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.7), hSize - (TPalette.yBoxSize / 4)*1.5);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - TPalette.yBoxSize / 4);
			glEnd();
		}
		else if (i == 8)
		{
			glColor3ub(255, 255, 255);
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize), hSize - TPalette.yBoxSize);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize), hSize - TPalette.yBoxSize);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize), hSize);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize), hSize);
			glEnd();
		}
		else if (i == 9)
		{
			glColor3ub(0, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize / 2);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize / 2);
			glEnd();
		}
		else if (i == 10)
		{
			glColor3ub(0, 0, 0);
			if (wSize <= 700)
			{
				glBegin(GL_POLYGON);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize*0.1);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize*0.8);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize*0.8);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize*0.1);
				glEnd();
			}
			else
			{
				glBegin(GL_POLYGON);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.3), hSize - TPalette.yBoxSize*0.05);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.3), hSize - TPalette.yBoxSize*0.85);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.7), hSize - TPalette.yBoxSize*0.85);
				glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.7), hSize - TPalette.yBoxSize*0.05);
				glEnd();
			}
		}
		else if (i == 11)
		{
			glColor3ub(0, 0, 0);
			glBegin(GL_POLYGON);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize*0.8);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5), hSize - TPalette.yBoxSize*0.2);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize*0.8);
			glEnd();
		}
		else if (i == 12)
		{
			glColor3ub(0, 0, 0);
			glBegin(GL_POLYGON);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize*0.3);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.2), hSize - TPalette.yBoxSize*0.7);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize*0.7);
			glVertex2f(TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.8), hSize - TPalette.yBoxSize*0.3);
			glEnd();
		}
		else if (i == 13)
		{
			glColor3ub(0, 0, 0);
			glBegin(GL_POLYGON);
			for (int j = 0; j < 100; j++)
			{
				float angle = j * 2 * PI / 100;
				
				if (wSize <= 700)
					glVertex2f((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + (TPalette.xBoxSize*0.3)*cos(angle), (hSize - TPalette.yBoxSize*0.5) + (TPalette.xBoxSize*0.3)*sin(angle));
				else 
					glVertex2f((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + (TPalette.xBoxSize*0.2)*cos(angle), (hSize - TPalette.yBoxSize*0.5) + (TPalette.xBoxSize*0.2)*sin(angle));
			}
			glEnd();
		}
		else if (i == 14)
		{
			glColor3ub(0, 0, 0);
			glBegin(GL_POLYGON);
			for (int j = 0; j < 5; j++)
			{
				float angle = j * 2 * PI / 5;
				
				if (wSize <= 700)
					glVertex2f((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + (TPalette.xBoxSize*0.3)*cos(angle), (hSize - TPalette.yBoxSize*0.5) + (TPalette.xBoxSize*0.3)*sin(angle));
				else
					glVertex2f((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + (TPalette.xBoxSize*0.2)*cos(angle), (hSize - TPalette.yBoxSize*0.5) + (TPalette.xBoxSize*0.2)*sin(angle));
			}
			glEnd();
		}
		else if (i == 15)
		{
			glColor3ub(0, 0, 0);
			glBegin(GL_TRIANGLE_FAN);
			for (int j = 0; j < 5 * 2; j++)
			{
				float DegInRad = j * 360.0 / 5 * 2 * DegToRad;

				if (Counter % 2 != 0)
				{	
					if (wSize <= 700)
						glVertex2f(((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + cos(DegInRad) * (TPalette.xBoxSize*0.4)), ((hSize - TPalette.yBoxSize*0.5) + sin(DegInRad) * (TPalette.xBoxSize*0.4)));
					else 
						glVertex2f(((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + cos(DegInRad) * (TPalette.xBoxSize*0.3)), ((hSize - TPalette.yBoxSize*0.5) + sin(DegInRad) * (TPalette.xBoxSize*0.3)));
				}
				else
				{
					if (wSize <= 700)
						glVertex2f(((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + cos(DegInRad) * (TPalette.xBoxSize*0.4) / 2), ((hSize - TPalette.yBoxSize*0.5) + sin(DegInRad) * (TPalette.xBoxSize*0.4) / 2));
					else
						glVertex2f(((TPalette.xInicial + (i*TPalette.GridSize) + (TPalette.xBoxSize*0.5)) + cos(DegInRad) * (TPalette.xBoxSize*0.25) / 2), ((hSize - TPalette.yBoxSize*0.5) + sin(DegInRad) * (TPalette.xBoxSize*0.25) / 2));
				}
				Counter++;
			}
			glEnd();
		}

		glFlush();
	}
}

int InsidePalette2(int x, int y)
{
	if (x >= TPalette.xInicial && x <= TPalette.xSize && y <= TPalette.yInicial && y >= hSize -TPalette.ySize)	return 1;
	else return -1;
}

void AlteraTool(int x, int y)
{
	int Tool = GetToolPalette(x, y);
	int i;
	if (Tool == 0)
	{
		printf("\tEsta Seccao Mostra a Cor Ativa.\n");
	}
	else if (Tool == 1)
	{
		printf("\tEsta Seccao Mostra a Modo Ativo.\n");
	}
	else if (Tool == 2)
	{
		printf("\tEsta Seccao Mostra a Figura Ativa.\n");
	}
	else if (Tool == 4)
	{
		printf("\tModo Inserir Ativado.\n");
		printf("\t1 Clique para Iniciar Figura, 1 Clique para Terminar Figura.\n");
		Mode = InsertMode;
	}
	else if (Tool == 5)
	{
		printf("\tModo Apagar Ativado.\n");
		printf("\t1 Clique para Apagar Figura.\n");
		Mode = DeleteMode;
	}
	else if (Tool == 6)
	{
		printf("\tModo Mover Ativado.\n");
		printf("\t1 Clique para Selecionar Figura, 1 Clique para Terminar Move.\n");
		Mode = MoveMode;
	}
	else if (Tool == 7)
	{
		printf("\tModo Rodar Ativado.\n");
		printf("\t1 Clique para Selecionar Figura, 1 Clique para Terminar Rotacao.\n");
		printf("\t1 Clique Direito para Rodar Figura.\n");
		printf("\t+/- para Alterar Angulo de Rotacao.\n");
		Mode = RotateMode;
	}
	else if (Tool == 9)
	{	
		printf("\tForma Ativa -> Linha.\n");
		ActiveForm = Linha;
	}
	else if (Tool == 10)
	{
		printf("\tForma Ativa -> Quadrado.\n");
		ActiveForm = Quadrado;
	}
	else if (Tool == 11)
	{
		printf("\tForma Ativa -> Triangulo.\n");
		ActiveForm = Triangulo;
	}
	else if (Tool == 12)
	{
		printf("\tForma Ativa -> Retangulo.\n");
		ActiveForm = Retangulo;
	}
	else if (Tool == 13)
	{
		printf("\tForma Ativa -> Circulo.\n");
		ActiveForm = Circulo;
	}
	else if (Tool == 14)
	{
		printf("\tForma Ativa -> Poligono Regular Convexo.\n");
		printf("\t+/- em Modo Inserir para Mudar Numero de Lados.\n");
		ActiveForm = PolRegConvexo;
	}
	else if (Tool == 15)
	{
		printf("\tForma Ativa -> Poligono Regular Nao Convexo.\n");
		printf("\t+/- em Modo Inserir para Mudar Numero de Pontas.\n");
		ActiveForm = PolRegNaoConvexo;
	}
	else return;
}

int GetToolPalette(int x, int y)
{
	int i;

	for (i = 0; i < NumTools; i++)
	{
		if ((x > TPalette.xInicial + (i*TPalette.GridSize)) &&
			(x < TPalette.xInicial + TPalette.xBoxSize + (i*TPalette.GridSize)) &&
			(y < TPalette.yInicial) &&
			(y > hSize - (TPalette.yInicial + TPalette.yBoxSize)))
			return i;
	}
	return NULL;
}