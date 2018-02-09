#ifndef POINT_2D_H
#define POINT_2D_H

#include <stdio.h>
#include <stdlib.h>

typedef struct point2D POINT2D;

struct point2D{
	float x;
	float y;
};

POINT2D* createPoint2D(float x, float y);
float getX(POINT2D* point);
float getY(POINT2D* point);
void changePoint2D(POINT2D* point, float x, float y);
void deletePoint2D(POINT2D* point);

#endif