//**************************************************************//
// Projeto - Paint						                        //
// Data- 02/12/2016                                             //
// U.C. - Computação Gráfica                                    //
// Docente - Luís Baptista                                      //
// Álvaro Benjamim - 16372                                      //
// No.h                                                         //
//**************************************************************//

#pragma once

template <class Item>
class No
{
private:
	Item *_item;
	No<Item> *_next;
	No<Item> *_prev;
	int _pos;

public:
	No();
	No(const Item&);
	No(const No<Item>&);
	~No();

	void setItem(const Item&);

	void setNext(No<Item>*);
	Item& getItem() const;
	No<Item>* getNext() const;
	No<Item>* getPrev() const;
	int get_pos();

	template <class Item> friend class Lista;
	template <class Item> friend class Iterator;
};
template <class Item>
int No<Item>::get_pos() {
	return _pos;
}
template <class Item>
No<Item>::No()
{
	_item = 0;
	_next = 0;
	_prev = 0;
	_pos = 0;
}
template <class Item>
No<Item>::No(const Item& item)
{
	_item = &item;
	_next = 0;
	_prev = 0;
	_pos = 0;

}

template <class Item>
No<Item>::No(const No<Item>& no)
{
	_item = no._item;
	_next = no._next;
	_prev = no._prev;
	_pos = no._item;
}

template <class Item>
No<Item>::~No()
{

}

template <class Item>
void No<Item>::setItem(const Item& item)
{
	_item = &item;
}



template <class Item>
void No<Item>::setNext(No<Item>* next)
{
	_next = next;
}

template <class Item>
Item& No<Item>::getItem() const
{
	return *_item;
}

template <class Item>
No<Item>* No<Item>::getNext() const
{
	return _next;
}

template <class Item>
No<Item>* No<Item>::getPrev() const
{
	return _prev;
}