#include "Header.h"

void Display()
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	
	printf("Start Render...\n");

	for (i = 0; i < NFormas; i++)
		DesenhaForma(formas[i], 0);

	DefinePalette(0, 0, wSize, 30);
	DefinePalette2(0, hSize, wSize, (hSize/20));


	DesenhaPalette2();
	DesenhaPalette();
	glFlush();
}