#include "Header.h"


struct Forma* CriaForma(int tipo, int xinicial, int yinicial, int xfinal, int yfinal)
{	
	struct Forma *F = (struct Forma*) malloc(sizeof(struct Forma));
	
	F->Tipo = tipo;
	if (F->Tipo == PolRegNaoConvexo)
		F->Num_Lados = NumPontasPolNaoConvexo;
	else if (F->Tipo == PolRegConvexo)
		F->Num_Lados = NumSidesPolConvexo;
	else if (F->Tipo == Circulo)
		F->Num_Lados = 100;
	
	F->Angulo = 0.0;
	
	F->r = ActiveColor[0];
	F->g = ActiveColor[1];
	F->b = ActiveColor[2];

	F->rc = 0;
	F->gc = 0;
	F->bc = 0;

	F->xinicial = xinicial;
	F->yinicial = yinicial;
	F->xfinal = xfinal;
	F->yfinal = yfinal;

	return F;
}

struct Forma * CriaVerificaTipo(int Tipo, int xInicial, int yInicial, int xFinal, int yFinal)
{	
	if (Tipo == Retangulo)
	{
		return CriaForma(Tipo, xInicial, yInicial, xFinal, yFinal);
	}
	else if (Tipo == Quadrado)
	{
		return CriaForma(Tipo, xInicial, yInicial, xFinal, yFinal);
	}
	else if (Tipo == Triangulo)
	{
		return CriaForma(Tipo, xInicial, yInicial, xFinal, yFinal);
	}
	else if (Tipo == PolRegNaoConvexo)
	{
		return CriaForma(Tipo, xInicial, yInicial, xFinal, yFinal);
	}
	else if (Tipo == Circulo)
	{
		return CriaForma(Tipo, xInicial, yInicial, xFinal, yFinal);
	}
	else if (Tipo == PolRegConvexo)
	{
		return CriaForma(Tipo, xInicial, yInicial, xFinal, yFinal);
	}
	else if (Tipo == Linha)
	{
		return CriaForma(Tipo, xInicial, yInicial, xFinal, yFinal);
	}
}

void DesenhaForma(struct Forma *F, int xorType)
{
	switch (F->Tipo)
	{
	case Retangulo: 
		DesenhaRetangulo(F, xorType);
		break;
	case Quadrado:
		DesenhaQuadrado(F, xorType);
		break;
	case Triangulo:
		DesenhaTriangulo(F, xorType);
		break;
	case PolRegNaoConvexo:
		DesenhaPoligonoRegNaoConvexo(F, xorType);
		break;
	case Circulo:
		DesenhaPoligonoRegConvexo(F, xorType);
		break;
	case PolRegConvexo:
		DesenhaPoligonoRegConvexo(F, xorType);
		break;
	case Linha:
		DesenhaLinha(F, xorType);
		break;
	default:
		break;
	}
}

void DesenhaRetangulo(struct Forma * F, int xorType)
{
	float xDelta = (F->xinicial + F->xfinal) / 2;
	float yDelta = (F->yinicial + F->yfinal) / 2;

	glPushMatrix();

	glTranslatef(xDelta, yDelta, 0);
	glRotatef(F->Angulo, 0, 0, 1);
	glTranslatef(-xDelta, -yDelta, 0);

	if (xorType)	glLogicOp(GL_XOR);

	glColor3ub(F->r, F->g, F->b);
	glBegin (GL_POLYGON);
		glVertex2i(F->xinicial, F->yinicial);
		glVertex2i(F->xinicial, F->yfinal);
		glVertex2i(F->xfinal, F->yfinal);
		glVertex2i(F->xfinal, F->yinicial);
	glEnd ();

	
	glColor3ub(F->rc, F->gc, F->bc);
	glBegin (GL_LINE_LOOP);
		glVertex2i(F->xinicial, F->yinicial);
		glVertex2i(F->xinicial, F->yfinal);
		glVertex2i(F->xfinal, F->yfinal);
		glVertex2i(F->xfinal, F->yinicial);
	glEnd ();

	glFlush();
	
	if (xorType)	glLogicOp(GL_COPY);
	
	glPopMatrix();
}

void DesenhaQuadrado(struct Forma * F, int xorType)
{
	if (F->yfinal >= F->yinicial && F->xfinal > F->xinicial)
	{
		F->yfinal = ((F->xfinal - F->xinicial) + F->yinicial);
	}
	else if (F->yfinal <= F->yinicial && F->xfinal > F->xinicial)
	{
		F->yfinal = (F->yinicial - (F->xfinal - F->xinicial));
	}
	else if (F->yfinal <= F->yinicial && F->xfinal < F->xinicial)
	{
		F->yfinal = (F->yinicial - (F->xfinal - F->xinicial)*(-1));
	}
	else if (F->yfinal >= F->yinicial && F->xfinal < F->xinicial)
	{
		F->yfinal = ((-1)*(F->xfinal - F->xinicial) + F->yinicial);
	}
	
	if (F->yfinal > hSize)
	{	
		if (F->xfinal > F->xinicial)
		{
			F->xfinal -= (F->yfinal - hSize);
		}
		else if (F->xfinal < F->xinicial)
		{
			F->xfinal += (F->yfinal - hSize);
		}
	}

	else if (F->yfinal < 0)
	{
		if (F->xfinal > F->xinicial)
		{
			F->xfinal += (F->yfinal );
		}
		else if (F->xfinal < F->xinicial)
		{
			F->xfinal -= (F->yfinal);
		}
	}

	float xDelta = (F->xinicial + F->xfinal) / 2;
	float yDelta = (F->yinicial + F->yfinal) / 2;

	glPushMatrix();

	glTranslatef(xDelta, yDelta, 0);
	glRotatef(F->Angulo, 0, 0, 1);
	glTranslatef(-xDelta, -yDelta, 0);

	if (xorType)	glLogicOp(GL_XOR);

	glColor3ub(F->r, F->g, F->b);
	glBegin(GL_POLYGON);
	glVertex2i(F->xinicial, F->yinicial);
	glVertex2i(F->xinicial, F->yfinal);
	glVertex2i(F->xfinal, F->yfinal);
	glVertex2i(F->xfinal, F->yinicial);
	glEnd();

	glColor3ub(F->rc, F->gc, F->bc); 
	glBegin(GL_LINE_LOOP);
	glVertex2i(F->xinicial, F->yinicial);
	glVertex2i(F->xinicial, F->yfinal);
	glVertex2i(F->xfinal, F->yfinal);
	glVertex2i(F->xfinal, F->yinicial);
	glEnd();

	glFlush();

	if (xorType)	glLogicOp(GL_COPY);

	glPopMatrix();
}	

void DesenhaTriangulo(struct Forma *F, int xorType)
{
	float xDelta = (F->xinicial + F->xfinal) / 2;
	float yDelta = (F->yinicial + F->yfinal) / 2;

	glPushMatrix();

	glTranslatef(xDelta, yDelta, 0);
	glRotatef(F->Angulo, 0, 0, 1);
	glTranslatef(-xDelta, -yDelta, 0);

	if (xorType)	glLogicOp(GL_XOR);

	glColor3ub(F->r, F->g, F->b);
	glBegin(GL_POLYGON);
	glVertex2i(F->xinicial, F->yinicial);
	glVertex2i(F->xfinal, F->yinicial);
	glVertex2i((F->xinicial+F->xfinal)/2, F->yfinal);
	glEnd();

	glColor3ub(F->rc, F->gc, F->bc);
	glBegin(GL_LINE_LOOP);
	glVertex2i(F->xinicial, F->yinicial);
	glVertex2i(F->xfinal, F->yinicial);
	glVertex2i((F->xinicial + F->xfinal) / 2, F->yfinal);
	glEnd();

	glFlush();

	if (xorType)	glLogicOp(GL_COPY);

	glPopMatrix();
}

void DesenhaPoligonoRegNaoConvexo(struct Forma * F, int xorType)
{
	float Raio,x,y;
	int Counter = 1;
	int i;
	const float DegToRad = (3.14159265358979323846 / 180);
	
	if (F->yfinal >= F->yinicial && F->xfinal > F->xinicial)
	{
		F->yfinal = ((F->xfinal - F->xinicial) + F->yinicial);
	}
	else if (F->yfinal <= F->yinicial && F->xfinal > F->xinicial)
	{
		F->yfinal = (F->yinicial - (F->xfinal - F->xinicial));
	}
	else if (F->yfinal <= F->yinicial && F->xfinal < F->xinicial)
	{
		F->yfinal = (F->yinicial - (F->xfinal - F->xinicial)*(-1));
	}
	else if (F->yfinal >= F->yinicial && F->xfinal < F->xinicial)
	{
		F->yfinal = ((-1)*(F->xfinal - F->xinicial) + F->yinicial);
	}

	if (F->yfinal > hSize)
	{
		if (F->xfinal > F->xinicial)
		{
			F->xfinal -= (F->yfinal - hSize);
		}
		else if (F->xfinal < F->xinicial)
		{
			F->xfinal += (F->yfinal - hSize);
		}
	}

	else if (F->yfinal < 0)
	{
		if (F->xfinal > F->xinicial)
		{
			F->xfinal += (F->yfinal);
		}
		else if (F->xfinal < F->xinicial)
		{
			F->xfinal -= (F->yfinal);
		}
	}

	x = ((float)F->xinicial + F->xfinal) / 2;
	y = ((float)F->yinicial + F->yfinal) / 2;
	Raio = (F->xfinal-F->xinicial)/2;

	float xDelta = (F->xinicial + F->xfinal) / 2;
	float yDelta = (F->yinicial + F->yfinal) / 2;

	glPushMatrix();

	glTranslatef(xDelta, yDelta, 0);
	glRotatef(F->Angulo, 0, 0, 1);
	glTranslatef(-xDelta, -yDelta, 0);

	if (xorType)	glLogicOp(GL_XOR);

	glColor3ub(F->r, F->g, F->b);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x , y);
	for ( i = 0; i <= (F->Num_Lados * 2); i ++)
	{
		float DegInRad = i * 360.0 / (F->Num_Lados * 2) * DegToRad;

		if (Counter % 2 != 0)
		{
			glVertex2f((x + cos(DegInRad) * Raio), (y + sin(DegInRad) * Raio));
		}
		else
		{
			glVertex2f((x + cos(DegInRad) * Raio / 2), (y + sin(DegInRad) * Raio / 2));
		}
		Counter++;
	}
	glEnd();

	Counter = 1;

	glColor3ub(F->rc, F->gc, F->bc);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= (F->Num_Lados * 2); i++)
	{
		float DegInRad = i * 360.0 / (F->Num_Lados * 2) * DegToRad;

		if (Counter % 2 != 0)
		{
			glVertex2f((x + cos(DegInRad) * Raio), (y + sin(DegInRad) * Raio));
		}
		else
		{
			glVertex2f((x + cos(DegInRad) * Raio / 2), (y + sin(DegInRad) * Raio / 2));
		}
		Counter++;
	}
	glEnd();

	glFlush();

	if (xorType)	glLogicOp(GL_COPY);

	glPopMatrix();
}

void DesenhaPoligonoRegConvexo(struct Forma *F, int xorType)
{
	const double PI = 3.14159265358979323846;
	float Raio, x, y;
	
	if (F->yfinal >= F->yinicial && F->xfinal > F->xinicial)
	{
		F->yfinal = ((F->xfinal - F->xinicial) + F->yinicial);
	}
	else if (F->yfinal <= F->yinicial && F->xfinal > F->xinicial)
	{
		F->yfinal = (F->yinicial - (F->xfinal - F->xinicial));
	}
	else if (F->yfinal <= F->yinicial && F->xfinal < F->xinicial)
	{
		F->yfinal = (F->yinicial - (F->xfinal - F->xinicial)*(-1));
	}
	else if (F->yfinal >= F->yinicial && F->xfinal < F->xinicial)
	{
		F->yfinal = ((-1)*(F->xfinal - F->xinicial) + F->yinicial);
	}
	if (F->yfinal > hSize)
	{
		if (F->xfinal > F->xinicial)
		{
			F->xfinal -= (F->yfinal - hSize);
		}
		else if (F->xfinal < F->xinicial)
		{
			F->xfinal += (F->yfinal - hSize);
		}
	}

	else if (F->yfinal < 0)
	{
		if (F->xfinal > F->xinicial)
		{
			F->xfinal += (F->yfinal);
		}
		else if (F->xfinal < F->xinicial)
		{
			F->xfinal -= (F->yfinal);
		}
	}

	x = ((float)F->xinicial + F->xfinal) / 2;
	y = ((float)F->yinicial + F->yfinal) / 2;
	Raio = (F->xfinal - F->xinicial) / 2;

	glPushMatrix();

	glTranslatef(x, y, 0);
	glRotatef(F->Angulo, 0, 0, 1);
	glTranslatef(-x, -y, 0);

	if (xorType)	glLogicOp(GL_XOR);

	glColor3ub(F->r, F->g, F->b);
	
	glBegin(GL_POLYGON);
	for (int i = 0; i < F->Num_Lados; i++)
	{
		float angle = i * 2 * PI / F->Num_Lados;
		glVertex2f(x + Raio*cos(angle),y + Raio*sin(angle));
	}
	glEnd();

	glColor3ub(F->rc, F->gc, F->bc);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < F->Num_Lados; i++)
	{
		float angle = i * 2 * PI / F->Num_Lados;
		glVertex2f(x + Raio*cos(angle),y + Raio*sin(angle));
	}
	glEnd();

	glFlush();

	if (xorType)	glLogicOp(GL_COPY);

	glPopMatrix();
}

void DesenhaLinha(struct Forma *F, int xorType)
{
	float xDelta = (F->xinicial + F->xfinal) / 2;
	float yDelta = (F->yinicial + F->yfinal) / 2;

	glPushMatrix();

	glTranslatef(xDelta, yDelta, 0);
	glRotatef(F->Angulo, 0, 0, 1);
	glTranslatef(-xDelta, -yDelta, 0);

	if (xorType)	glLogicOp(GL_XOR);

	glColor3ub(F->r, F->g, F->b);
	glBegin(GL_LINES);
	glVertex2i(F->xinicial, F->yinicial);
	glVertex2i(F->xfinal, F->yfinal);
	glEnd();

	glFlush();

	if (xorType)	glLogicOp(GL_COPY);

	glPopMatrix();
}

int PickForma(int x, int y)
{
	int i;

	for (i = NFormas - 1; i >= 0; i--)
		if (DentroForma(x, y, formas[i]))
		{
			getPixel(x, y, rgba);
			if(formas[i]->r == rgba[0] && formas[i]->g == rgba[1] && formas[i]->b == rgba[2])
				return i;
		}

	return i;
}

int DentroForma(int x, int y, struct Forma * F)
{
	return (x >= CheckMinimo(F->xinicial, F->xfinal) &&	
			x <= CheckMaximo(F->xinicial, F->xfinal) && 
			y >= CheckMinimo(F->yinicial, F->yfinal) && 
			y <= CheckMaximo(F->yinicial, F->yfinal));
}

int CheckMaximo(int a, int b) 
{ 
	return a>b ? a : b; 
}

int CheckMinimo(int a, int b) 
{
	return a>b ? b : a;
}

void ApagaForma(struct Forma * f)
{
	free(f);
}

void UpdateForma(struct Forma * F, int xDeslocamento, int yDeslocamento)
{
	F->xinicial += xDeslocamento;
	F->yinicial += yDeslocamento;
	F->xfinal += xDeslocamento;
	F->yfinal += yDeslocamento;
}

void IncrementoAngulo(struct Forma * F)
{
	F->Angulo += Angulo;
}

void MudaContornoForma(struct Forma * F)
{
	F->rc = ActiveColor[0];
	F->gc = ActiveColor[1];
	F->bc = ActiveColor[2];
}

void getPixel(int x, int y, GLubyte *color) {
	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	rgba[0] = color[0];
	rgba[1] = color[1];
	rgba[2] = color[2];
	rgba[3] = color[3];
}