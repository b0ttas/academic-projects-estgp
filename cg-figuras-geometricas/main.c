#include <stdio.h>
#include <stdlib.h>
#include <GL\glut.h>

#include <string.h>

#include "list.h."
#include "geometricFigure.h"
#include "point2d.h"

#define WSIZE 1024
#define HSIZE 680

//variaveis globais
LIST* figures;
GEOMETRICFIGURE* selectColor[3];
GEOMETRICFIGURE* currentColor;
GLenum type;
int drawState, wSize, hSize, fig, triagulo;
float red, green, blue;
char bufferColor[1024];

//funções
void myInit();
void display(void);
void mouseClick(GLint button, GLint state, GLint x, GLint y);
void mouseMove(int x, int y);
void reshape(int w, int h);
void keyPress(unsigned char key, int x, int y);
void printString(char* s);

float convertColor(int x);

//main
void main(int argc, char **argv){
	glutInit(&argc, argv);
	myInit();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(wSize, hSize);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Figuras Geometricas 2");
	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mouseMove);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPress);
	glutMainLoop();
}

//init
void myInit(){
	int i = 2, p = 0;

	wSize = WSIZE;
	hSize = HSIZE;
	red = green = blue = 0.0;
	type = GL_POLYGON;
	fig = 0;
	triagulo = 0;
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,wSize, 0, hSize);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(red, green, blue);
	glEnable(GL_COLOR_LOGIC_OP);

	sprintf(bufferColor, "Red: %1.1f Green: %1.1f Blue: %1.1f", red, green, blue);

	drawState = 0;

	figures = createList();

	currentColor = createGeometricFigure();
	insertOnEnd(currentColor->vertices, createPoint2D(2, 62));
	insertOnEnd(currentColor->vertices, createPoint2D(2, 82));
	insertOnEnd(currentColor->vertices, createPoint2D(22, 82));
	insertOnEnd(currentColor->vertices, createPoint2D(22, 62));
	setColor(currentColor, createColor(red, green, blue));
	setType(currentColor, GL_POLYGON);

	for(i = 2, p = 0; i>=0; i--,p++){
		selectColor[i] = createGeometricFigure();
		insertOnEnd(selectColor[i]->vertices, createPoint2D(2, (p*20)+2));
		insertOnEnd(selectColor[i]->vertices, createPoint2D(wSize-2, (p*20)+2));
		insertOnEnd(selectColor[i]->vertices, createPoint2D(wSize-2, ((p*20)+2)+20));
		insertOnEnd(selectColor[i]->vertices, createPoint2D(2, ((p*20)+2)+20));
		switch(i){
		case 0:
			setColor(selectColor[i], createColor(1.0, 0.0, 0.0));break;
		case 1:
			setColor(selectColor[i], createColor(0.0, 1.0, 0.0));break;
		case 2:
			setColor(selectColor[i], createColor(0.0, 0.0, 1.0));break;
		default:
			break;
		}
		setType(selectColor[i], GL_POLYGON);
	}
}

void display(void){
	int i = 0;
	ITERATOR* it;
	
	glClear(GL_COLOR_BUFFER_BIT);

	//if(!drawState){
		it = initIterator(figures, 0);
		while(itIsEnd(it) != 1){
			drawGeometricFigure((GEOMETRICFIGURE*) itGetItem(it), 0);
			itGoNext(it);
		}
	//}
	
	glColor3f(0.0, 0.0, 1.0);
	switch(type){
	case GL_POLYGON:
		if(fig == 0)
			sprintf(bufferColor, "Red: %1.1f Green: %1.1f Blue: %1.1f   |   Tipo Selecionado: Poligonos   |   F:Poligonos Q:Quadrados T:Triagulos L:Linhas P:Pontos A:Lapis", red, green, blue);
		else if(fig == 1)
			sprintf(bufferColor, "Red: %1.1f Green: %1.1f Blue: %1.1f   |   Tipo Selecionado: Quadrados   |   F:Poligonos Q:Quadrados T:Triagulos L:Linhas P:Pontos A:Lapis", red, green, blue);
		break;
	case GL_TRIANGLES:
		sprintf(bufferColor, "Red: %1.1f Green: %1.1f Blue: %1.1f   |   Tipo Selecionado: Triagulos   |   F:Poligonos Q:Quadrados T:Triagulos L:Linhas P:Pontos A:Lapis", red, green, blue);
		break;
	case GL_LINES:
		sprintf(bufferColor, "Red: %1.1f Green: %1.1f Blue: %1.1f   |   Tipo Selecionado: Linhas   |   F:Poligonos Q:Quadrados T:Triagulos L:Linhas P:Pontos A:Lapis", red, green, blue);
		break;
	case GL_POINTS:
		if(fig == 4)
			sprintf(bufferColor, "Red: %1.1f Green: %1.1f Blue: %1.1f   |   Tipo Selecionado: Pontos   |   F:Poligonos Q:Quadrados T:Triagulos L:Linhas P:Pontos A:Lapis", red, green, blue);
		else if(fig == 5)
			sprintf(bufferColor, "Red: %1.1f Green: %1.1f Blue: %1.1f   |   Tipo Selecionado: Lapis   |   F:Poligonos Q:Quadrados T:Triagulos L:Linhas P:Pontos A:Lapis", red, green, blue);
		break;
	default:
		sprintf(bufferColor, "Red: %1.1f Green: %1.1f Blue: %1.1f   |   Tipo Selecionado: Poligonos   |   F:Poligonos Q:Quadrados T:Triagulos L:Linhas P:Pontos A:Lapis", red, green, blue);
		break;
	}
	glRasterPos2f(26, 70);
	printString(bufferColor);

	drawGeometricFigure(currentColor, 0);

	for(i=0; i<3; i++){
		drawGeometricFigure(selectColor[i], 0);
	}

	glutSwapBuffers();
}

void mouseClick(GLint button, GLint state, GLint x, GLint y){
	GEOMETRICFIGURE* figure;

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(drawState){
			if(y<=hSize-82){
				switch(fig){
				case 0:
					figure = (GEOMETRICFIGURE*) getOnEnd(figures);
					insertOnEnd(figure->vertices, createPoint2D(x, hSize-y));
					break;
				case 1:
				case 3:
				case 5:
					drawState = 0;
					glutPostRedisplay();
					break;
				case 2:
					figure = (GEOMETRICFIGURE*) getOnEnd(figures);
					insertOnEnd(figure->vertices, createPoint2D(x, hSize-y));
					if(triagulo==1)
						triagulo++;
					else if(triagulo==2){
						triagulo = 0;
						drawState = 0;
						glutPostRedisplay();
					}
					break;
				}
			}
		}
		else{
			if((x>2 && x<wSize-2) && (y<=hSize-2 && y>hSize-62)){
				if(y<=hSize-42 && y>hSize-62){
					red = convertColor(x);
				}else if(y<=hSize-22 && y>hSize-42){
					green = convertColor(x);
				}else if(y<=hSize-2 && y>hSize-22){
					blue = convertColor(x);
				}
				setColor(currentColor, createColor(red, green, blue));
				glutPostRedisplay();
			}
			else if(y<=hSize-82){
				figure = createGeometricFigure();
				setColor(figure, createColor(red, green, blue));
				setType(figure, type);
				switch(fig){
				case 2:
					triagulo = 1;
				case 0:
				case 3:
					insertOnEnd(figure->vertices, createPoint2D(x, hSize-y));
					insertOnEnd(figure->vertices, createPoint2D(x, hSize-y));
					insertOnEnd(figures, figure);
					drawState = 1;
					break;
				case 1:
					insertOnEnd(figure->vertices, createPoint2D(x, hSize-y));
					insertOnEnd(figure->vertices, createPoint2D(x, hSize-y));
					insertOnEnd(figure->vertices, createPoint2D(x, hSize-y));
					insertOnEnd(figure->vertices, createPoint2D(x, hSize-y));
					insertOnEnd(figures, figure);
					drawState = 1;
					break;
				case 5:
					drawState = 1;
				case 4:
					insertOnEnd(figure->vertices, createPoint2D(x, hSize-y));
					insertOnEnd(figures, figure);
					glutPostRedisplay();
					break;
				}
			}
			else if((x>2 && x<=22) && (y<=hSize-62 && y>hSize-82)){
				deleteList(figures);
				figures = createList();
				glutPostRedisplay();
			}
		}
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
		if(drawState){
			if(y<=hSize-82){
				switch(fig){
				case 0:
					figure = (GEOMETRICFIGURE*) getOnEnd(figures);
					insertOnEnd(figure->vertices, createPoint2D(x, hSize-y));
					drawState = 0;
					glutPostRedisplay();
					break;
				case 1:
				case 3:
				case 5:
					drawState = 0;
					glutPostRedisplay();
					break;
				case 2:
					if(triagulo == 2){
						figure = (GEOMETRICFIGURE* ) getOnEnd(figures);
						insertOnEnd(figure->vertices, createPoint2D(x, hSize-y));
						triagulo = 0;
						drawState = 0;
						glutPostRedisplay();
					}
					break;
				}
			}
		}
	}
}

void mouseMove(int x, int y){
	GEOMETRICFIGURE* figure;
	if(drawState){
		switch(fig){
		case 0:
		case 2:
		case 3:
			figure = (GEOMETRICFIGURE*) getOnEnd(figures);
			changePoint2D((POINT2D*) getOnEnd(figure->vertices), x, hSize-y);
			glutPostRedisplay();
			break;
		case 1:
			figure = (GEOMETRICFIGURE*) getOnEnd(figures);
			changePoint2D((POINT2D*) getOnPosition(figure->vertices, 1), getX((POINT2D*) getOnStart(figure->vertices)), hSize-y);
			changePoint2D((POINT2D*) getOnPosition(figure->vertices, 2), x, hSize-y);
			changePoint2D((POINT2D*) getOnEnd(figure->vertices), x, getY((POINT2D*) getOnStart(figure->vertices)));
			glutPostRedisplay();
			break;
		case 5:
			figure = (GEOMETRICFIGURE*) getOnEnd(figures);
			insertOnEnd(figure->vertices, createPoint2D(x, hSize-y));
			glutPostRedisplay();
			break;
		}
	}
}

void keyPress(unsigned char key, int x, int y){
	if(!drawState){
		switch(key){
		case 'F':
		case 'f':
			type = GL_POLYGON;
			fig = 0;
			break;
		case 'Q':
		case 'q':
			type = GL_POLYGON;
			fig = 1;
			break;
		case 'T':
		case 't':
			type = GL_TRIANGLES;
			fig = 2;
			break;
		case 'L':
		case 'l':
			type = GL_LINES;
			fig = 3;
			break;
		case 'P':
		case 'p':
			type = GL_POINTS;
			fig = 4;
			break;
		case 'a':
		case 'A':
			type = GL_POINTS;
			fig = 5;
			break;
		default:
			type = GL_POLYGON;
			fig = 0;
			break;
		}
		glutPostRedisplay();
	}
}

float convertColor(int x){
	float val;

	val = (float) (((float)x/(float)wSize));

	return val;
}

void printString(char* s){
	int i = 0;
	
	for(i=0; i<strlen(s);i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
	}
}

void reshape(int w, int h){
	POINT2D* point1;
	POINT2D* point2;
	int i = 0;

	wSize = w;
	hSize = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,w,0,h);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	for(i=0;i<3;i++){
		point1 = (POINT2D*) getOnPosition(selectColor[i]->vertices, 1);
		point2 = (POINT2D*) getOnPosition(selectColor[i]->vertices, 2);
		point1->x = wSize-2;
		point2->x = wSize-2;
	}
}