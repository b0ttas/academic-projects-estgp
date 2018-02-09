#include "Color.h"



Color::Color()
{
}


Color::~Color()
{
}

void Color::SetR(GLint r)
{
	R = r;
}

void Color::SetG(GLint g)
{
	G = g;
}

void Color::SetB(GLint b)
{
	B = b;
}

GLint Color::GetR()
{
	return R;
}

GLint Color::GetG()
{
	return G;
}

GLint Color::GetB()
{
	return B;
}

Color::Color(GLint r, GLint g, GLint b)
{
	R = r;
	G = g;
	B = b;
}
