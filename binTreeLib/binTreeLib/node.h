#pragma once

template <class T>
class Node
{
private:
	T info;
	int factor;
	Node *left;
	Node *right;

public:
	Node()
	{
		left = nullptr;
		right = nullptr;
	}
	Node(T info, Node *left, Node *right);
	Node(T info, int factor, Node *left, Node *right);
	~Node()
	{
		delete left;
		left = nullptr;
		delete right;
		right = nullptr;
	}

	void setInfo(T info) { this->info = info; }
	void setFactor(int factor) { this->factor = factor; }
	void setLeft(Node *left) { this->left = left; }
	void setRight(Node *right) { this->right = right; }
	T getInfo() { return this->info; }
	int getFactor() { return this->factor; }
	Node *getLeft() { return this->left; }
	Node *getRight() { return this->right; }

	bool red() { return this != nullptr && factor == 0; }
	void red(bool red)
	{
		if (this == nullptr)
			return;
		factor = !red;
	}

	friend bool operator==(const Node &left, const Node &right) { return left.info == right.info; }
	friend bool operator!=(const Node &left, const Node &right) { return !(left == right); }
	friend bool operator<(const Node &left, const Node &right) { return left.info < right.info; }
	friend bool operator>(const Node &left, const Node &right) { return left.info > right.info; }
	friend bool operator<=(const Node &left, const Node &right) { return !(left > right); }
	friend bool operator>=(const Node &left, const Node &right) { return !(left < right); }
	Node *operator[](const int index)
	{
		if (this == nullptr)
			return nullptr;
		else if (index == 0)
			return left;
		else
			return right;
	}
	void ds(Node *a, int dir)
	{
		if (this == nullptr)
			return;
		else if (dir == 0)
			left = a;
		else
			right = a;
	}
};

template <class T>
Node<T>::Node(T info, Node<T> *left, Node<T> *right)
{
	this->info = info;
	factor = 0;
	this->left = left;
	this->right = right;
}

template <class T>
Node<T>::Node(T info, int factor, Node<T> *left, Node<T> *right)
{
	this->info = info;
	this->factor = factor;
	this->left = left;
	this->right = right;
}