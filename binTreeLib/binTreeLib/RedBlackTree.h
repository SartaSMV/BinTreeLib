#pragma once

#include <map>
#include <string>

#include "BinaryTree.h"

using std::map;
using std::string;

template <class T>
class RedBlackTree : public BinarySearchTree<T>
{
private:
	Node<T> *rotSingle(Node<T> *node, int dir);
	Node<T> *rotDouble(Node<T> *node, int dir);
	Node<T> *insertNode(Node<T> *node, T N);
	Node<T> *putNode(Node<T> *node, T N) override;

	Node<T> *removeNode(Node<T> *node, T N, int *done);
	Node<T> *removeBalance(Node<T> *node, int dir, int *done);
	Node<T> *deletNode(Node<T> *node, T N) override;

	void printFactorNode(Node<T> *node) override;
};

template <class T>
void RedBlackTree<T>::printFactorNode(Node<T> *node)
{
	if (node->red())
		cout << "-R";
	else
		cout << "-B";
}

template <class T>
Node<T> *RedBlackTree<T>::insertNode(Node<T> *node, T N)
{
	if (node == nullptr)
		node = new Node<T>(N, 0, nullptr, nullptr);
	else
	{
		int dir = node->getInfo() < N;

		node->ds(insertNode((*node)[dir], N), dir);

		if ((*node)[dir]->red())
		{
			if ((*node)[!dir]->red())
			{
				node->red(true);
				(*node)[0]->red(false);
				(*node)[1]->red(false);
			}
			else
			{
				if ((*(*node)[dir])[dir]->red())
					node = rotSingle(node, !dir);
				else if ((*(*node)[dir])[!dir]->red())
					node = rotDouble(node, !dir);
			}
		}
	}
	return node;
}

template <class T>
Node<T> *RedBlackTree<T>::putNode(Node<T> *node, T N)
{
	node = insertNode(node, N);
	node->red(false);
	return node;
}

template <class T>
Node<T> *RedBlackTree<T>::rotSingle(Node<T> *node, int dir)
{
	Node<T> *save = (*node)[!dir];

	node->ds((*save)[dir], !dir);
	save->ds(node, dir);
	node->red(true);
	save->red(false);

	return save;
}

template <class T>
Node<T> *RedBlackTree<T>::rotDouble(Node<T> *node, int dir)
{
	node->ds(rotSingle((*node)[!dir], !dir), !dir);
	return rotSingle(node, dir);
}

template <class T>
Node<T> *RedBlackTree<T>::removeNode(Node<T> *node, T N, int *done)
{
	if (node == nullptr)
		*done = 1;
	else
	{
		int dir;
		if (node->getInfo() == N)
		{
			if ((*node)[0] == nullptr || (*node)[1] == nullptr)
			{
				Node<T> *save = (*node)[(*node)[0] == nullptr];

				if (node->red())
					*done = 1;
				else if (save->red())
				{
					save->red(false);
					*done = 1;
				}

				node->setLeft(nullptr);
				node->setRight(nullptr);
				delete node;
				node = nullptr;

				return save;
			}
			else
			{
				Node<T> *heir = (*node)[0];

				while ((*heir)[1] != nullptr)
					heir = (*heir)[1];

				node->setInfo(heir->getInfo());
				N = heir->getInfo();
			}
		}

		dir = node->getInfo() < N;
		node->ds(removeNode((*node)[dir], N, done), dir);
		if (!*done)
			node = removeBalance(node, dir, done);
	}
	return node;
}

template <class T>
Node<T> *RedBlackTree<T>::removeBalance(Node<T> *node, int dir, int *done)
{
	Node<T> *p = node;
	Node<T> *s = (*node)[!dir];

	if (s->red())
	{
		node = rotSingle(node, dir);
		s = (*p)[!dir];
	}

	if (s != nullptr)
	{
		if (!(*s)[0]->red() && !(*s)[1]->red())
		{
			if (p->red())
				*done = 1;
			p->red(false);
			s->red(true);
		}
		else
		{
			int save = p->red();
			int new_root = (node == p);

			if ((*s)[!dir]->red())
				p = rotSingle(p, dir);
			else
				p = rotDouble(p, dir);

			p->red(save);
			(*p)[0]->red(false);
			(*p)[1]->red(false);

			if (new_root)
				node = p;
			else
				node->ds(p, dir);
			*done = 1;
		}
	}

	return node;
}

template <class T>
Node<T> *RedBlackTree<T>::deletNode(Node<T> *node, T N)
{
	int done = 0;

	node = removeNode(node, N, &done);
	if (node != nullptr)
		node->red(false);
	return node;
}