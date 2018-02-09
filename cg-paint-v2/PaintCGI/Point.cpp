#include "Point.h"



Point::Point()
{
}


Point::~Point()
{
}

void Point::SetX(int n)
{
	x = n;
}

void Point::SetY(int n)
{
	y = n;
}

int Point::GetX()
{
	return x;
}

int Point::GetY()
{
	return y;
}

Point::Point(int n, int m)
{
	x = n;
	y = m;
}