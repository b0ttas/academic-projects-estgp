#include "menu.h"

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3i(0.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	
	glutInitWindowSize(500, 500); //DE_Width, DE_Height
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Paint");
	glutReshapeFunc(reshape);
	myInit();
	glutDisplayFunc(display);

	glutPassiveMotionFunc(mouse_hover);
	glutMouseFunc(mouse_clk); //Inputs Mouse Function In Use
	

	glutMainLoop();
}
