#pragma once
#ifndef NODE_H
#define NODE_H

template <class T>
class Node
{
public:
	T data;
	Node<T>* next;

	Node(T data, Node<T>* next = nullptr);
};
template <class T>
Node<T>::Node(T data, Node<T>* next)
{
	this->data = data;
	this->next = next;
}
#endif // !NODE_H
