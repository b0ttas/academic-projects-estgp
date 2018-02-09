#include "menu.h"
#include "Tools.h"
Point ini;
Point mid;
Point end;


GLint Color_Temp[3];

int typ;


Color *A = new Color(0, 0, 0);

Lista < Figura >  Linked_List;

void insert(Point a, Point b, Point c, Color col, Color col1, int type)
{
	Figura *A = new Figura(a, b, c, col ,col1, type);
	Linked_List.insertLast(*A);
}

void draw()
{

}

void preview()
{

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	draw();
	preview();

	//// Toolbox 
	//glColor3f(0.5, 0.5, 0.5);
	//glBegin(GL_POLYGON);
	//glVertex2i(0, 0);
	//glVertex2i(100, 0);
	//glVertex2i(100, glutGet(GLUT_WINDOW_HEIGHT));
	//glVertex2i(0, glutGet(GLUT_WINDOW_HEIGHT));
	//glEnd();


	//// 1 linha
	//glColor3f(1, 0, 0);
	//glBegin(GL_POLYGON);
	//glVertex2i( 5, 5);
	//glVertex2i(45, 5);
	//glVertex2i(45, 45);
	//glVertex2i(5, 45);
	//glEnd();

	//glColor3f(1, 1, 0);
	//glBegin(GL_POLYGON);
	//glVertex2i(55, 5);
	//glVertex2i(95, 5);
	//glVertex2i(95, 45);
	//glVertex2i(55, 45);
	//glEnd();
	//
	////2 linha
	//glColor3f(0, 1, 0);
	//glBegin(GL_POLYGON);
	//glVertex2i(5, 55);
	//glVertex2i(45, 55);
	//glVertex2i(45, 95);
	//glVertex2i(5, 95);
	//glEnd();

	//glColor3f(0, 1, 1);
	//glBegin(GL_POLYGON);
	//glVertex2i(55, 55);
	//glVertex2i(95, 55);
	//glVertex2i(95, 95);
	//glVertex2i(55, 95);
	//glEnd();

	////3a linha
	//glColor3f(0, 0, 1);
	//glBegin(GL_POLYGON);
	//glVertex2i(5, 105);
	//glVertex2i(45, 105);
	//glVertex2i(45, 145);
	//glVertex2i(5, 145);
	//glEnd();

	//glColor3f(1, 0, 1);
	//glBegin(GL_POLYGON);
	//glVertex2i(55, 105);
	//glVertex2i(95, 105);
	//glVertex2i(95, 145);
	//glVertex2i(55, 145);
	//glEnd();

	////4a linha
	//glColor3f(0, 0, 0);
	//glBegin(GL_POLYGON);
	//glVertex2i(5, 155);
	//glVertex2i(45, 155);
	//glVertex2i(45, 195);
	//glVertex2i(5, 195);
	//glEnd();

	//glColor3f(1, 1, 1);
	//glBegin(GL_POLYGON);
	//glVertex2i(55, 155);
	//glVertex2i(95, 155);
	//glVertex2i(95, 195);
	//glVertex2i(55, 195);
	//glEnd();

	////Current Color
	//glColor3i(A->GetR(), A->GetG(), A->GetB()); //bleh
	//glBegin(GL_POLYGON);
	//glVertex2i(5, 205);
	//glVertex2i(95, 205);
	//glVertex2i(95, 245);
	//glVertex2i(5, 245);
	//glEnd();

	////Square
	//glColor3f(1, 1, 1); //bleh
	//glBegin(GL_POLYGON);
	//glVertex2i(5, 255);
	//glVertex2i(45, 255);
	//glVertex2i(45, 295);
	//glVertex2i(5, 295);
	//glEnd();

	////Triangle
	//glColor3f(1, 1, 1); //bleh
	//glBegin(GL_POLYGON);
	//glVertex2i(55, 255);
	//glVertex2i(95, 255);
	//glVertex2i(95, 295);
	//glVertex2i(55, 295);
	//glEnd();

	////Lines
	//glColor3f(1, 1, 1); //bleh
	//glBegin(GL_POLYGON);
	//glVertex2i(5, 255);
	//glVertex2i(45, 255);
	//glVertex2i(45, 295);
	//glVertex2i(5, 295);
	//glEnd();

	////Dots
	//glColor3f(1, 1, 1); //bleh
	//glBegin(GL_POLYGON);
	//glVertex2i(55, 255);
	//glVertex2i(95, 255);
	//glVertex2i(95, 295);
	//glVertex2i(55, 295);
	//glEnd();

	////Rectangles
	//glColor3f(1, 1, 1); //bleh
	//glBegin(GL_POLYGON);
	//glVertex2i(5, 255);
	//glVertex2i(45, 255);
	//glVertex2i(45, 295);
	//glVertex2i(5, 295);
	//glEnd();

	////Circle
	//glColor3f(1, 1, 1); //bleh
	//glBegin(GL_POLYGON);
	//glVertex2i(55, 255);
	//glVertex2i(95, 255);
	//glVertex2i(95, 295);
	//glVertex2i(55, 295);
	//glEnd();

	////Polygon
	//glColor3f(1, 1, 1); //bleh
	//glBegin(GL_POLYGON);
	//glVertex2i(55, 255);
	//glVertex2i(95, 255);
	//glVertex2i(95, 295);
	//glVertex2i(55, 295);
	//glEnd();
	Draw_Tools();
	glFlush();
	glutSwapBuffers();
}

void mouse_clk(int button, int state, int x, int y) {
	
	//escolhe opção
	if (x <= 100) {
		if (x >= 5 && x <= 45) {
			if (y >= 5 && y <= 45) {
				Color *A = new Color(Color_Temp[0], Color_Temp[1], Color_Temp[2]);
			}

			else if (y >= 55 && y <= 95) {
				//cor
			}

			else if (y >= 105 && y <= 145) {
				//cor
			}
			
			else if (y >= 155 && y <= 195) {
				//cor
			}
			
			else if (y >= 205 && y <= 255) {

			}
		}

		if (x >= 55 && x <= 95) {
			if (y >= 5 && y <= 45) {
				//cor
			}
			
			else if (y >= 55 && y <= 95) {
				//cor
			}

			else if (y >= 105 && y <= 145) {
				//cor
			}

			else if (y >= 155 && y <= 195) {
				//cor
			}
		}

	}
	else
	{
		//insert figure(A.....,typ)
	}
	/* maior que 100 (x)
	ponto init = x,y =med&end
	tyoe ponto chama insert
	senao count++ */

}

void mouse_hover(int x, int y) {
	if (x >= 5 && x <= 45) {
		if (y >= 5 && y <= 45) {
			glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_RGB, GL_INT, &Color_Temp);//Reads the selected pixel		}
		}
	}
}