#ifndef PALETTE_H
#define PALETTE_H

struct ColorsPalette{
	int GridSize;
	int xBoxSize, yBoxSize;
	int xInicial, yInicial;
	int xSize, ySize;
} CPalette;

void DefinePalette(int, int, int, int);
void DesenhaPalette();
int InsidePalette(int, int);
int *GetColorPalette(int, int);
void AlteraCor(int, int);

struct ToolsPalette {
	int GridSize;
	int xBoxSize, yBoxSize;
	int xInicial, yInicial;
	int xSize, ySize;
} TPalette;

void DefinePalette(int, int, int, int);
void DesenhaPalette();
int InsidePalette(int, int);
int *GetColorPalette(int, int);
void AlteraCor(int, int);

void DefinePalette2(int, int, int, int);
void DesenhaPalette2();
int InsidePalette2(int, int);
int GetToolPalette(int, int);

#endif //PALETTE_H