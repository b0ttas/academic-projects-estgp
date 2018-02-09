//**************************************************************//
// Projeto - Paint						                        //
// Data- 02/12/2016                                             //
// U.C. - Computação Gráfica                                    //
// Docente - Luís Baptista                                      //
// Álvaro Benjamim - 16372                                      //
// Lista.h                                                      //
//**************************************************************//

#pragma once

#include <iostream>
#include "No.h"

using namespace std;


template <class Item>
class Lista
{
private:
	No<Item> *_first, *_last;
	int _size;

public:
	Lista();
	Lista(const Lista<Item>&);
	~Lista();

	void setFirst(No<Item>* no);

	void insertFirst(Item&);
	void insert(Item&, int);
	void insertLast(Item&);

	void exch(Item no1, Item no2);


	void removeFirst();
	void remove(int);
	void removeLast();

	No<Item>* getFirst();
	No<Item>& getLast() const;
	No<Item>& getElement(int) const;

	No<Item>* getSize();


	bool empty() const;

	void printT(ostream&) const;

	template <class Item> friend class Iterator;
};


template <class Item>
No<Item> *Lista<Item>::getSize()
{
	return _size;
}

template <class Item>
Lista<Item>::Lista()
{
	_first = 0;
	_last = 0;
	_size = 0;
}


template <class Item>
Lista<Item>::Lista(const Lista<Item>& Lista)
{
	_first = 0;
	_last = 0;
	_size = 0;

	No<Item> *aux;
	aux = Lista._first;

	while (aux != 0) {
		insertLast(aux->getItem());
		aux = aux->_next;
	}
}


template <class Item>
Lista<Item>::~Lista()
{
	No<Item> *aux;

	while (_first != 0) {
		aux = _first->_next;
		delete _first;
		_first = aux;
	}
	_size = 0;
}

template <class Item>
void Lista<Item>::insertLast(Item& item)
{
	No<Item> *novo = new No < Item >;
	novo->_item = &item;

	if (_first == 0) {
		_first = novo;
		_last = novo;
		_size = 0;
		novo->_pos = 0;

	}
	else {
		_last->_next = novo;
		_last = novo;
		_size = _size + 1;
		novo->_pos = _size;
	}

}

template <class Item>
void Lista<Item>::exch(Item no1, Item no2) {
	Item aux;

	aux = no1;
	no1 = no2;
	no2 = aux;

}

template <class Item>
void Lista<Item>::printT(ostream& os) const
{
	if (empty())
	{
		os << "Lista Vazia" << endl;

	}
	else {
		No<Item> *aux = _first;

		while (aux != 0) {
			os << aux->getItem() << endl;
			aux = aux->_next;
		}

	}
}

template <class Item>
void Lista<Item>::removeFirst()
{
	if (empty())
		return;
	if (_first == _last)
	{
		delete _first;
		_first = _last = 0;
	}

	else
	{
		Iterator<Item> *aux = new Iterator < Item >;

		aux->_iterator = new No < Item >;
		aux->_iterator = _first;
		_first = _first->_next;
		delete aux;

	}
	_size--;
}

template <class Item>
void Lista<Item>::removeLast()
{
	if (empty())
		return;
	if (_first == _last)
	{
		delete _last;
		_first = _last = 0;
		_size = 0;
	}

	else
	{
		No <Item> *removed = _last;
		No <Item> * aux = _first;

		while (aux->_next != removed)
			aux = aux->_next;


		_last = aux;
		aux->_next = 0;
		delete removed;

		_size--;


	}

}

template <class Item>
bool Lista<Item>::empty() const
{
	return (_first == 0);
}

template <class Item>
void Lista<Item>::remove(int pos)
{
	if (empty())
	{
		cout << "Lista Vazia";
		return;
	}

	if (pos > _size)
	{
		cout << "Erro";
		return;
	}

	if (pos == 0)
	{
		removeFirst();
		return;
	}

	if (pos == _size)
	{
		removeLast();
		return;
	}
	else
	{
		No<Item> *aux = _first;
		No<Item> *removed = new No < Item >;
		for (int i = 0; i < pos - 1; i++)
		{
			aux = aux->_next;
			cout << i;
		}

		removed = aux->_next;
		aux->_next = removed->_next;
		delete removed;

	}
	_size--;

}
