#ifndef LIST_H
#define LIST_H

#include <iostream>

struct Node
{
	double value_x, value_y;
	Node *N, *P;
	Node(double x, double y)
	{
		value_x = x;
		value_y = y;

		N = P = NULL;

	}
};

class LinkedList
{
	Node *front;
	Node *back;

public:
	LinkedList()
	{
		front = NULL; back = NULL;
	}
	~LinkedList() { destroyList(); }
	//void appendNodeFront(int x, int y);
	//void appendNodeBack(int x, int y);
	void appendNodeOrder(double x, double y);
	void dispNodesGap(int vini, int vfin);
	//void dispNodesForward();
	//void dispNodesReverse();
	void destroyList();
	void ReceiveNode();

	double max_X;
	double max_Y;
	double min_X;
	double min_Y;
	double vmedio, vquad, mov;
	double sum, sum_quad, sum_mov;
	int nopts = 0;

	int finish_flag = 0, call_flag = 0;
	int file_org;
	double curr_X;
	double curr_Y;
};
#endif