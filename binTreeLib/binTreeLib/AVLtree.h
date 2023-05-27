#pragma once

#include "BinaryTree.h"

template <class T>
class AVLtree : public BinarySearchTree<T>
{
private:
	void correctHeight(Node<T> *node);
	int bfactor(Node<T> *node) { return getSize(node->getRight()) - getSize(node->getLeft()); }
	int getSize(Node<T> *node);

	Node<T> *rotateLeft(Node<T> *node);
	Node<T> *rotateRight(Node<T> *node);
	Node<T> *balance(Node<T> *node);
	Node<T> *putNode(Node<T> *node, T N) override;
	Node<T> *deletNode(Node<T> *node, T N) override;
	void printFactorNode(Node<T> *node) override;
	Node<T> *deleteMin(Node<T> *node);
};

template <class T>
void AVLtree<T>::printFactorNode(Node<T> *node)
{
	cout << "-" << node->getFactor();
}

template <class T>
void AVLtree<T>::correctHeight(Node<T> *node)
{
	int heightLeft = getSize(node->getLeft());
	int heightRight = getSize(node->getRight());

	node->setFactor(((heightLeft > heightRight) ? heightLeft : heightRight) + 1);
}

template <class T>
int AVLtree<T>::getSize(Node<T> *node)
{
	if (node == nullptr)
		return 0;
	return node->getFactor();
}

template <class T>
Node<T> *AVLtree<T>::rotateLeft(Node<T> *node)
{
	Node<T> *tempNode = node->getRight();
	node->setRight(tempNode->getLeft());
	tempNode->setLeft(node);

	correctHeight(node);
	correctHeight(tempNode);

	return tempNode;
}

template <class T>
Node<T> *AVLtree<T>::rotateRight(Node<T> *node)
{
	Node<T> *tempNode = node->getLeft();
	node->setLeft(tempNode->getRight());
	tempNode->setRight(node);

	correctHeight(node);
	correctHeight(tempNode);

	return tempNode;
}

template <class T>
Node<T> *AVLtree<T>::balance(Node<T> *node)
{
	correctHeight(node);

	if (bfactor(node) == 2)
	{

		if (bfactor(node->getRight()) < 0)
		{
			node->setRight(rotateRight(node->getRight()));
		}

		return rotateLeft(node);
	}

	if (bfactor(node) == -2)
	{

		if (bfactor(node->getLeft()) > 0)
		{
			node->setLeft(rotateLeft(node->getLeft()));
		}

		return rotateRight(node);
	}

	return node;
}

template <class T>
Node<T> *AVLtree<T>::putNode(Node<T> *node, T N)
{
	if (node == nullptr)
		return new Node<T>(N, 1, nullptr, nullptr);

	if (N <= node->getInfo())
	{
		node->setLeft(putNode(node->getLeft(), N));
	}
	else
	{
		node->setRight(putNode(node->getRight(), N));
	}

	node->setFactor(1 + getSize(node->getLeft()) + getSize(node->getRight()));

	return balance(node);
}

template <class T>
Node<T> *AVLtree<T>::deletNode(Node<T> *node, T N)
{
	if (node == nullptr)
		return nullptr;
	if (N < node->getInfo())
	{
		node->setLeft(deletNode(node->getLeft(), N));
	}
	else if (N > node->getInfo())
	{
		node->setRight(deletNode(node->getRight(), N));
	}
	else
	{
		if (node->getRight() == nullptr)
		{
			Node<T> *swapNode = node->getLeft();

			node->setLeft(nullptr);
			delete node;
			node = nullptr;

			return swapNode;
		}
		if (node->getLeft() == nullptr)
		{
			Node<T> *swapNode = node->getRight();
			node->setRight(nullptr);
			delete node;
			node = nullptr;

			return swapNode;
		}

		Node<T> *t = node;
		node->setInfo(this->BinarySearchTree<T>::getMin(t->getRight())->getInfo());
		node->setRight(deleteMin(t->getRight()));
		node->setLeft(t->getLeft());
	}

	return balance(node);
}

template <class T>
Node<T> *AVLtree<T>::deleteMin(Node<T> *node)
{
	if (node->getLeft() == nullptr)
	{
		Node<T> *swapNode = node->getRight();
		node->setRight(nullptr);
		delete node;
		node = nullptr;

		return swapNode;
	}

	node->setLeft(deleteMin(node->getLeft()));
	node->setFactor(1 + getSize(node->getRight()) + getSize(node->getLeft()));

	return node;
}
