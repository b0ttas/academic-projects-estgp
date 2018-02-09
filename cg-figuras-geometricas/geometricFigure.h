#ifndef GEOMETRIC_FIGURE_H
#define GEOMETRIC_FIGURE_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "list.h"
#include "point2d.h"

typedef struct geometricFigure GEOMETRICFIGURE;
typedef struct colorGeo COR;

struct colorGeo{
	float redColor;
	float greenColor;
	float blueColor;
};

struct geometricFigure{
	LIST* vertices;
	GLenum type;
	COR* cor;
};

//funções da figura geometrica
GEOMETRICFIGURE* createGeometricFigure();
COR* createColor(float r, float g, float b);
void insertVertex(GEOMETRICFIGURE* figure, POINT2D* vertex);
void setColor(GEOMETRICFIGURE* figure, COR* cor);
void setType(GEOMETRICFIGURE* figure, GLenum type);
COR* getColor(GEOMETRICFIGURE* figure);
float getRed(COR* cor);
float getGreen(COR* cor);
float getBlue(COR* cor);
void drawGeometricFigure(GEOMETRICFIGURE* figure, int xor);
void deleteGeometricFigure(GEOMETRICFIGURE* figure);

#endif