#pragma once
#include "GL/glut.h"
class Color
{
public:
	Color();
	~Color();

	void SetR(GLint);
	void SetG(GLint);
	void SetB(GLint);

	GLint GetR();
	GLint GetG();
	GLint GetB();

	Color(GLint, GLint, GLint);

protected:
	
	GLint R;
	GLint G;
	GLint B;

};

