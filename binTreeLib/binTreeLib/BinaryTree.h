#pragma once

#include "node.h"
#include <iostream>

using std::cout;
using std::endl;

template <class T>
class BinarySearchTree
{
private:
	virtual Node<T> *deletNode(Node<T> *root, T N);
	virtual Node<T> *putNode(Node<T> *node, T N);
	virtual void printFactorNode(Node<T> *node) { return; };

protected:
	Node<T> *root;

	Node<T> *getMin(Node<T> *node)
	{
		if (node->getLeft() == nullptr)
			return node;
		return getMin(node->getLeft());
	}
	Node<T> *getMax(Node<T> *node)
	{
		if (node->getRight() == nullptr)
			return node;
		return getMax(node->getRight());
	}
	void printTree(Node<T> *node, int put);

public:
	BinarySearchTree() { this->root = nullptr; }
	~BinarySearchTree()
	{
		delete root;
		root = nullptr;
	}

	bool searchNode(T N);
	void addNode(T N);
	bool delNode(T N);
	void printTree() { this->printTree(this->root, 0); }
};

template <class T>
void BinarySearchTree<T>::printTree(Node<T> *node, int put)
{
	if (node == nullptr)
		return;

	printTree(node->getRight(), put + 1);

	cout.width(2 * put);
	cout << "";
	cout << node->getInfo();
	printFactorNode(node);
	cout << endl;

	printTree(node->getLeft(), put + 1);
	return;
}

template <class T>
Node<T> *BinarySearchTree<T>::deletNode(Node<T> *root, T N)
{
	if (root == nullptr)
	{
		return root;
	}
	if (N < root->getInfo())
	{
		root->setLeft(deletNode(root->getLeft(), N));
	}
	else if (N > root->getInfo())
	{
		root->setRight(deletNode(root->getRight(), N));
	}
	else if (root->getLeft() != nullptr && root->getRight() != nullptr)
	{
		if (root->getRight()->getLeft() == nullptr)
		{
			root->setInfo(root->getRight()->getInfo());
		}
		else
		{
			root->setInfo(root->getRight()->getLeft()->getInfo());
		}
		root->setRight(deletNode(root->getRight(), root->getInfo()));
	}
	else
	{
		Node<T> *swapNode;
		if (root->getLeft() != nullptr)
		{
			swapNode = root->getLeft();
			root->setInfo(root->getLeft()->getInfo());
			root->setRight(root->getLeft()->getRight());
			root->setLeft(root->getLeft()->getLeft());
			swapNode->setLeft(nullptr);
			swapNode->setRight(nullptr);
			delete swapNode;
			swapNode = nullptr;
		}
		else if (root->getRight() != nullptr)
		{
			swapNode = root->getRight();
			root->setInfo(root->getRight()->getInfo());
			root->setLeft(root->getRight()->getLeft());
			root->setRight(root->getRight()->getRight());
			swapNode->setLeft(nullptr);
			swapNode->setRight(nullptr);
			delete swapNode;
			swapNode = nullptr;
		}
		else
		{
			delete root;
			root = nullptr;
		}
	}

	return root;
}

template <class T>
Node<T> *BinarySearchTree<T>::putNode(Node<T> *node, T N)
{
	Node<T> *newNode = new Node<T>(N, nullptr, nullptr);

	if (node == nullptr)
	{
		node = newNode;
		return node;
	}

	Node<T> *moveNode = node;
	Node<T> *parentNode = node;

	while (moveNode != nullptr)
	{
		parentNode = moveNode;
		if (*newNode <= *parentNode)
		{
			moveNode = moveNode->getLeft();
		}
		else
		{
			moveNode = moveNode->getRight();
		}
	}

	if (*newNode <= *parentNode)
	{
		parentNode->setLeft(newNode);
	}
	else
	{
		parentNode->setRight(newNode);
	}

	return node;
}

template <class T>
void BinarySearchTree<T>::addNode(T N)
{
	this->root = putNode(this->root, N);
}

template <class T>
bool BinarySearchTree<T>::searchNode(T N)
{
	Node<T> *moveNode = this->root;
	Node<T> *parentNode = this->root;

	while (moveNode != nullptr)
	{
		if (N == moveNode->getInfo())
		{
			return true;
		}
		else if (N <= moveNode->getInfo())
		{
			parentNode = moveNode;
			moveNode = moveNode->getLeft();
		}
		else
		{
			parentNode = moveNode;
			moveNode = moveNode->getRight();
		}
	}

	return false;
}

template <class T>
bool BinarySearchTree<T>::delNode(T N)
{
	if (searchNode(N))
	{
		this->root = deletNode(this->root, N);
		return true;
	}
	else
	{
		return false;
	}
}