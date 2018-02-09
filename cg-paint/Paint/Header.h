#ifndef HEADER_H
#define HEADER_H
#include "Palette.h"
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define NMaxFormas 20
#define Wsize 600
#define InsertMode 4
#define MoveMode 5
#define DeleteMode 6
#define RotateMode 7
#define OutlineMode 16

#define Linha 9
#define Quadrado 10
#define Triangulo 11
#define Retangulo 12
#define Circulo 13
#define PolRegConvexo 14
#define PolRegNaoConvexo 15

struct Forma
{
	int xinicial, yinicial;
	int xfinal, yfinal;
	int Tipo;
	int Num_Lados;
	float Angulo;
	GLubyte r, g, b;
	GLubyte rc, gc, bc;
};

struct Forma* formas[NMaxFormas];

int Mode;
int ActiveForm;
int NFormas,NumTools;
int FlagDraw;
int MovePosicao, xMove, yMove;
int FlagRotate;
int ActiveColor[3];
int NumSidesPolConvexo;
int NumPontasPolNaoConvexo;
float Angulo;
int CoresPaletteRGB[10][3];
int NumColors;
GLubyte rgba[4];

int wSize, hSize;
void Janela(int, int);

void Init ();
void Display ();
void Keyboard (unsigned char, int, int);
void Rato (GLint, GLint, GLint, GLint);
void RatoCriaForma (GLint, GLint, GLint, GLint);
void RatoApagaForma(GLint, GLint, GLint, GLint);
void RatoMoveForma(GLint, GLint, GLint, GLint);
void RatoRotateForma(GLint, GLint, GLint, GLint);
void RatoContornoForma(GLint, GLint, GLint, GLint);
void MoveRato(int,int);

struct Forma *CriaForma (int, int, int, int, int);
struct Forma *CriaVerificaTipo (int, int, int ,int, int);

void DesenhaForma (struct Forma *,int);
void DesenhaRetangulo (struct Forma *, int);
void DesenhaQuadrado (struct Forma *, int);
void DesenhaTriangulo (struct Forma *, int);
void DesenhaPoligonoRegNaoConvexo(struct Forma *, int);
void DesenhaPoligonoRegConvexo(struct Forma *, int);
void DesenhaLinha(struct Forma *F, int xorType);

int PickForma (int, int);
int DentroForma (int, int, struct Forma *);
void ApagaForma (struct Forma *);
int CheckMaximo (int, int);
int CheckMinimo (int, int);
void getPixel(int, int, GLubyte *);

void UpdateForma(struct Forma *, int, int);
void IncrementoAngulo(struct Forma *);
void MudaContornoForma(struct Forma *);


#endif //HEADER_H