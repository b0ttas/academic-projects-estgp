#include "Header.h"

void main(int argc, char **argv)
{	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(Wsize, Wsize);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Paint");
	glutDisplayFunc(Display);
	glutMouseFunc(Rato);
	glutPassiveMotionFunc(MoveRato);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Janela);
	Init();
	glutMainLoop();
}