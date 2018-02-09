//**************************************************************//
// Projeto - Paint						                        //
// Data- 02/12/2016                                             //
// U.C. - Computação Gráfica                                    //
// Docente - Luís Baptista                                      //
// Álvaro Benjamim - 16372                                      //
// Iterator.h                                                   //
//**************************************************************//

#pragma once

#include "list.h"

template <class Item>
class Iterator
{
private:

public:
	Iterator();
	Iterator(const Iterator<Item>&);
	~Iterator();

	void init(Lista<Item>&);
	void last(Lista<Item>&);

	void forward();
	Item& getElement() const;
	int getPos();
	bool end() const;
	No<Item> *_iterator;


};

template <class Item>
Iterator<Item>::Iterator()
{
	_iterator = 0;
}

template <class Item>
Iterator<Item>::~Iterator()
{

}

template <class Item>
void Iterator<Item>::init(Lista<Item> &Lista)
{
	_iterator = Lista._first;
}

template <class Item>
void Iterator<Item>::last(Lista<Item> &Lista)
{
	_iterator = Lista._last;
}


template <class Item>
void Iterator<Item>::forward()
{
	_iterator = _iterator->_next;
}


template <class Item>
Item& Iterator<Item>::getElement() const
{
	return _iterator->getItem();
}

template <class Item>
int Iterator<Item>::getPos()
{
	return _iterator->get_pos();
}

template <class Item>
bool Iterator<Item>::end() const
{
	return (_iterator == 0);
}

