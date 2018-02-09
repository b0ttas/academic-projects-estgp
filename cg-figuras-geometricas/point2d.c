#include <stdio.h>
#include <stdlib.h>
#include "point2d.h"

POINT2D* createPoint2D(float x, float y){
	POINT2D* point = NULL;

	point = (POINT2D*) malloc(sizeof(POINT2D));
	point->x = x;
	point->y = y;

	return point;
}

float getX(POINT2D* point){
	return point->x;
}

float getY(POINT2D* point){
	return point->y;
}

void changePoint2D(POINT2D* point, float x, float y){
	point->x = x;
	point->y = y;
}

void deletePoint2D(POINT2D* point){
	free(point);
}
