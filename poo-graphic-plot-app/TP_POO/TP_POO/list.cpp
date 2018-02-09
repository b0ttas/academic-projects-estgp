#include "list.h"

using namespace std;

//void LinkedList::appendNodeFront(int x, int y)
//{
//	Node *n = new Node(x, y);
//	if (front == NULL)
//	{
//		front = n;
//		back = n;
//	}
//	else
//	{
//		front->P = n;
//		n->N = front;
//		front = n;
//	}
//}
//void LinkedList::appendNodeBack(int x, int y)
//{
//	Node *n = new Node(x, y);
//	if (back == NULL)
//	{
//		front = n;
//		back = n;
//	}
//	else
//	{
//		back->N = n;
//		n->P = back;
//		back = n;
//	}
//}

void LinkedList::appendNodeOrder(double x, double y)
{
	Node *n = new Node(x, y);

	Node *temp = front; //grabs 1st node
	
	if (back == NULL) //mete um node no fim
	{
		front = n;
		back = n;
	}
	else
	{
		back->N = n;
		n->P = back;
		back = n;
	}

	//int num = 1;

	while (temp != NULL) //define max e min xy, vmedio
	{
		if (temp->value_y > max_Y)
		{
			max_Y = temp->value_y;
		}

		if (temp->value_y < min_Y)
		{
			min_Y = temp->value_y;
		}

		if (temp->value_x > max_X) 
		{ 
			max_X = temp->value_x;
		}
		
		if (temp->value_x < min_X)
		{
			min_X = temp->value_x;
		}

		temp = temp->N; //goes to next node
	 }
		nopts++;
}

//void LinkedList::dispNodesForward()
//{
//	Node *temp = front;
//	cout << "\n\nNodes in forward order:" << endl;
//	while (temp != NULL)
//	{
//		cout << temp->value_x << "   ";
//		cout << temp->value_y << "   ";
//		cout << '\n';
//		temp = temp->N;
//	}
//}
//void LinkedList::dispNodesReverse()
//{
//	Node *temp = back;
//	cout << "\n\nNodes in reverse order :" << endl;
//	while (temp != NULL)
//	{
//		cout << temp->value_x << "   ";
//		cout << temp->value_y << "   ";
//		cout << '\n';
//		temp = temp->P;
//	}
//}

void LinkedList::dispNodesGap(int vini, int vfin)
{
		Node* temp = front;
		
		int i = 1; //situa o node em vini

		while (i != vini) {
			temp = temp->N;
			i++;
		}

		while (i != vfin)
		{
			sum_mov = sum_mov + temp->value_y;
			temp = temp->N;
			i++;
		}

		sum_mov = sum_mov + temp->value_y;
		mov = (sum_mov) / (vfin - vini + 1);
}

void LinkedList::destroyList()
{
	Node* T = back;
	while (T != NULL)
	{
		Node* T2 = T;
		T = T->P;
		delete T2;
	}
	front = NULL;
	back = NULL;

	max_X = 0;
	max_Y = 0;
	min_X = 0;
	min_Y = 0;
	vmedio = 0;
	vquad = 0;
	mov = 0;
	sum = 0;
	sum_quad = 0;
	sum_mov = 0;
	nopts = 0;
	finish_flag = 0;
	call_flag = 0;
	file_org = 0;
	curr_X = 0;
	curr_Y = 0;
}

void LinkedList::ReceiveNode()
{
	//grabs head node, senquences nodes till current is found
	Node *temp = front;

	int i = call_flag; //call_flag initiallized 0 in header

	while (i != 0) {
		temp = temp->N;
		i--;
	}

	//sets curr vals of x & y for grab
	if (temp != NULL)
	{
		curr_X = temp->value_x;
		curr_Y = temp->value_y;
		sum = sum + curr_Y;
		sum_quad = sum_quad + (curr_Y * curr_Y);

	}
	//flag checked when reading over
		else if (temp == NULL)
	{
		finish_flag = 1;
		call_flag = -1;
		vmedio = sum / nopts;
		vquad = sqrt(sum_quad / nopts);

	}
	
	call_flag++;
}