#include "Tools.h"

Lista <Tools> Toolbar;

Tools::Tools()
{
	Point* Init = new Point(5, 5);
	int y = 0;
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	for (int i = 0; i < Tools_all; i++) 
	{
		
		if (i < Tools_square) {
			if (i % 2 == 0) {
				x1 = 5;
				x2 = 5 + Tam_square;
				y1 = 5 + y + Tam_square* i;
				y2 = 5 + y + Tam_square* (i + 1);
			}
			else {
				x1 = 55;
				x2 = 55 + Tam_square ;

			}
		}
		else {
			x1 = 5;
			x2 = 5 + Tam_rect;
			y1 = 5 + y + Tam_rect* i;
			y2 = 5 + y + Tam_rect* (i + 1);
		}
		
		Point* a = new Point(x1, y1);
		Point* b = new Point(x2, y2);
		Tools* Tool_option = new Tools(*a,*b);
		Toolbar.insertLast(*Tool_option);
			y = 10;
	}

}

Tools::Tools(Point a, Point b){
	A = a;
	B = b;
}

Tools::~Tools()
{
}

Point Tools::Get_A()
{
	return A;
}

Point Tools::Get_B()
{
	return B;
}


void Draw_Tools() {
	Tools();
	Iterator<Tools> *itDAF = new Iterator < Tools >;
	int i = 0;
	for (itDAF->init(Toolbar); !itDAF->end(); itDAF->forward()) {
		
			glBegin(GL_QUADS);
				glVertex2i(itDAF->getElement().Get_A().GetX(), itDAF->getElement().Get_A().GetY());
				glVertex2i(itDAF->getElement().Get_A().GetX(), itDAF->getElement().Get_B().GetY());
				glVertex2i(itDAF->getElement().Get_B().GetX(), itDAF->getElement().Get_B().GetY());
				glVertex2i(itDAF->getElement().Get_B().GetX(), itDAF->getElement().Get_A().GetY());
			glEnd();
		
		i++;
	}
}