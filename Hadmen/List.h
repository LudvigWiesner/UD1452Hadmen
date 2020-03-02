#pragma once
#ifndef LIST_H
#define LIST_H
#include "Node.h"

template <class T>
class List
{
private:
	Node<T>* head;
	Node<T>* tail;
	int size;
	void deepCopy(const List &otherList);
public:
	List();
	virtual ~List();
	List(const List &otherList);
	List& operator=(const List &otherList);
	void insertAt(int pos, const T &data); // throw(...);
	T getAt(int pos)const; //throw(...)
	void removeAt(int pos); //throw(...)
	bool removeElement(const T &data);
	bool findElement(const T &toFind);
	int length()const;
	void getAll(T arr[], int cap); //throw(...)
};
template <class T>
List<T>::List()
{
	this->size = 0;
	this->head = nullptr;
	this->tail = nullptr;
}
template <class T>
List<T>::~List()
{
	Node<T>* current = head;
	Node<T>* trail = nullptr;
	while (current != nullptr)
	{
		trail = current;
		current = current->next;
		delete trail;
	}
}
template <class T>
List<T>::List(const List &otherList)
{
	if (otherList.head != nullptr)
	{
		this->deepCopy(otherList);
	}
	else
	{
		this->size = 0;
		this->head = nullptr;
		this->tail = nullptr;
	}
}
template <class T>
List<T>& List<T>::operator=(const List &otherList)
{
	if (this != &otherList)
	{
		if (size > 0)
		{
			Node<T>* current = head;
			Node<T>* trail = nullptr;
			while (current != nullptr)
			{
				trail = current;
				current = current->next;
				delete trail;
			}
			this->size = 0;
		}
		if (otherList.head != nullptr)
		{
			this->deepCopy(otherList);
		}
		else
		{
			this->size = 0;
			this->head = nullptr;
			this->tail = nullptr;
		}
	}
	return *this;
}
template <class T>
void List<T>::deepCopy(const List &otherList)
{
	this->size = otherList.size;
	Node<T>* current = otherList.head;
	Node<T>* trail = nullptr;

	head = new Node<T>(current->data);
	trail = head;
	current = current->next;
	while (current != nullptr)
	{
		Node<T>* newOne = new Node<T>(current->data);
		trail->next = newOne;
		trail = newOne;
		current = current->next;
	}
	tail = trail;
}
template <class T>
void List<T>::insertAt(int pos, const T &data)
{
	if (head == nullptr)
	{
		Node<T>* newOne = new Node<T>(data);
		head = newOne;
		tail = head;
		size++;

	}
	else if (head->next == nullptr && pos != 0)
	{
		Node<T>* newOne = new Node<T>(data);
		head->next = newOne;
		tail = head->next;
		size++;
	}
	else if (pos == 0 || pos < 0)
	{
		Node<T>* newOne = new Node<T>(data);
		newOne->next = this->head;
		this->head = newOne;
		size++;
	}
	else if (size < pos)
	{
		Node<T>* newOne = new Node<T>(data);
		tail->next = newOne;
		tail = tail->next;
		size++;
	}
	else
	{
		Node<T>* current = head;
		Node<T>* trail = nullptr;

		for (int i = 0; i < pos; i++)
		{
			trail = current;
			current = current->next;
		}
		 Node<T>* newOne = new Node<T>(data, current);
		 trail->next = newOne;
		 this->size++;
	}
}
template <class T>
T List<T>::getAt(int pos)const
{
	if (pos < size && pos >= 0)
	{
		Node<T>* current = head;
		for (int i = 0; i < pos; i++)
		{
			current = current->next;
		}
		return current->data;
	}
}
template <class T>
void List<T>::removeAt(int pos)
{
	if (pos < size && pos >= 0)
	{
		Node<T>* current = head;
		Node<T>* trail = nullptr;
		if (pos == 0)
		{
			head = head->next;
			delete current;
			size--;
		}
		else if (current->next == nullptr)
		{
			for (int i = 0; i < pos; i++)
			{
				trail = current;
				current = current->next;
			}
			tail = trail;
			trail->next = nullptr;
			delete current;
			size--;
		}
		else 
		{
			for (int i = 0; i < pos; i++)
			{
				trail = current;
				current = current->next;
			}
			trail->next = current->next;
			delete current;
			size--;
		}
	}
}
template <class T>
bool List<T>::removeElement(const T &data)
{
	bool success = false;
	Node<T>* current = head;
	if (size > 0)
	{
		if (current->data == data)
		{
			head = head->next;
			delete current;
			size--;
			success = true;
		}
		else
		{
			Node<T>* trail = nullptr;
			while (current->next != nullptr)
			{
				trail = current;
				current = current->next;
				if (current->data == data)
				{
					if (current == this->tail)
					{
						tail = trail;
						tail->next = nullptr;
						delete current;
						size--;
					}
					else
					{
						trail->next = current->next;
						delete current;
						size--;
						success = true;
					}
					break;
				}
			}
		}
	}
	return success;
}
template <class T>
bool List<T>::findElement(const T &toFind)
{
	bool success = false;
	Node<T>* current = head;
	while (current != nullptr)
	{
		if (current->data == toFind)
		{
			success = true;
			break;
		}
		current = current->next;
	}
	return success;
}
template <class T>
int List<T>::length()const
{
	return this->size;
}
template <class T>
void List<T>::getAll(T arr[], int cap)
{
	if (cap >= size && size > 0)
	{
		Node<T>* current = head;
		int counter = 0;
		while (current != nullptr)
		{
			arr[counter] = current->data;
			current = current->next;
			counter++;
		}
	}
}
#endif // !LIST_H
