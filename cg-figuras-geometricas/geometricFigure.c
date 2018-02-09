#include <stdio.h>
#include <stdlib.h>
#include <GL\glut.h>

#include "geometricFigure.h"
#include "list.h"
#include "point2d.h"

GEOMETRICFIGURE* createGeometricFigure(){
	GEOMETRICFIGURE* figure = NULL;

	figure = (GEOMETRICFIGURE*) malloc(sizeof(GEOMETRICFIGURE));
	figure->vertices = createList();
	figure->type = 0x0000;
	figure->cor = createColor(0.0, 0.0, 0.0);

	return figure;
}

COR* createColor(float r, float g, float b){
	COR* color = NULL;

	color = (COR*) malloc(sizeof(COR));
	color->redColor = r;
	color->greenColor = g;
	color->blueColor = b;

	return color;
}

void insertVertex(GEOMETRICFIGURE* figure, POINT2D* vertex){
	insertOnEnd(figure->vertices, vertex);
}

void setColor(GEOMETRICFIGURE* figure, COR* cor){
	figure->cor = cor;
}

void setType(GEOMETRICFIGURE* figure, GLenum type){
	figure->type = type;
}

COR* getColor(GEOMETRICFIGURE* figure){
	return figure->cor;
}

float getRed(COR* cor){
	return cor->redColor;
}

float getGreen(COR* cor){
	return cor->greenColor;
}

float getBlue(COR* cor){
	return cor->blueColor;
}

void drawGeometricFigure(GEOMETRICFIGURE* figure, int xor){
	POINT2D* vertex;

	ITERATOR* iterator = NULL;
	iterator = initIterator(figure->vertices, 0);
	
	glColor3f(figure->cor->redColor, figure->cor->greenColor, figure->cor->blueColor);

	if(xor == 1) glLogicOp(GL_XOR);

	glBegin(figure->type);
	while(itIsEnd(iterator) != 1){
		vertex = (POINT2D*) itGetItem(iterator);
		glVertex2f(vertex->x, vertex->y);
		itGoNext(iterator);
	}
	glEnd();
	glFlush();

	if(xor == 1) glLogicOp(GL_COPY);
}

void deleteGeometricFigure(GEOMETRICFIGURE* figure){
	ITERATOR* iterator = NULL;
	iterator = initIterator(figure->vertices, 0);
	while(itIsEnd(iterator) != 1){
		deletePoint2D((POINT2D*) itGetItem(iterator));
		itGoNext(iterator);
	}
	deleteList(figure->vertices);
}
