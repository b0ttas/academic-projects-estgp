#include "Header.h"
void Init()
{
	hSize = Wsize;
	wSize = Wsize;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, Wsize, 0, Wsize);

	glMatrixMode(GL_MODELVIEW);
	glClearColor (1.0, 1.0, 1.0, 1.0);
	//glColor3f (0.0, 1.0, 0.0);
	glEnable (GL_COLOR_LOGIC_OP);
	

	glLogicOp(GL_COPY);

	NumTools = 16;

	NumColors = 10;
	CoresPaletteRGB[0][0] = 255;
	CoresPaletteRGB[0][1] = 255;
	CoresPaletteRGB[0][2] = 255;
	CoresPaletteRGB[1][0] = 255;
	CoresPaletteRGB[1][1] = 255;
	CoresPaletteRGB[1][2] = 0;
	CoresPaletteRGB[2][0] = 255;
	CoresPaletteRGB[2][1] = 128;
	CoresPaletteRGB[2][2] = 0;
	CoresPaletteRGB[3][0] = 255;
	CoresPaletteRGB[3][1] = 0;
	CoresPaletteRGB[3][2] = 0;
	CoresPaletteRGB[4][0] = 255;
	CoresPaletteRGB[4][1] = 0;
	CoresPaletteRGB[4][2] = 128;
	CoresPaletteRGB[5][0] = 128;
	CoresPaletteRGB[5][1] = 0;
	CoresPaletteRGB[5][2] = 128;
	CoresPaletteRGB[6][0] = 0;
	CoresPaletteRGB[6][1] = 255;
	CoresPaletteRGB[6][2] = 0;
	CoresPaletteRGB[7][0] = 0;
	CoresPaletteRGB[7][1] = 0;
	CoresPaletteRGB[7][2] = 255;
	CoresPaletteRGB[8][0] = 128;
	CoresPaletteRGB[8][1] = 64;
	CoresPaletteRGB[8][2] = 0;
	CoresPaletteRGB[9][0] = 0;
	CoresPaletteRGB[9][1] = 0;
	CoresPaletteRGB[9][2] = 0;
	
	
	Mode = InsertMode;
	ActiveForm = Quadrado;
	NumSidesPolConvexo = 5;
	NumPontasPolNaoConvexo = 5;
	NFormas = 0;
	FlagDraw = 0;
	MovePosicao = -1;
	FlagRotate = -1;
	Angulo = 1;
	ActiveColor[0] = CoresPaletteRGB[7][0] ;
	ActiveColor[1] = CoresPaletteRGB[7][1] ;
	ActiveColor[2] = CoresPaletteRGB[7][2] ;
}

void Janela(int w, int h)
{
	wSize = w;
	hSize = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(0.0, 1.0, 0.0);
	glEnable(GL_COLOR_LOGIC_OP);
}