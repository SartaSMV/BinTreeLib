#include <iostream>
#include <cmath>
#include <chrono>

#include "BinaryTree.h"
#include "redBlackTree.h"
#include "avlTree.h"

using namespace std;

void fun(BinarySearchTree<double> *tree)
{
	int N = 10, A = 15;
	double pw = 1, X;

	for (int i = 1; i <= N; i++)
	{
		tree->addNode(i);
		pw *= i;
	}
	X = pow(pw, 1.0 / N);

	for (int i = 1; i <= A; i++)
	{
		tree->addNode((i + 1.0) * X / A);
	}
}

void Time()
{
	BinarySearchTree<double> *tree = new BinarySearchTree<double>;
	auto start = chrono::steady_clock::now();
	fun(tree);
	auto finish = chrono::steady_clock::now();
	chrono::duration<int64_t, nano> elapsed = finish - start;
	delete tree;
	tree = nullptr;
	cout << "The time binary search tree: " << elapsed.count() << " ns\n\n";

	tree = new AVLtree<double>;
	auto start_2 = chrono::steady_clock::now();
	fun(tree);
	auto finish_2 = chrono::steady_clock::now();
	chrono::duration<int64_t, nano> elapsed_2 = finish_2 - start_2;
	delete tree;
	tree = nullptr;
	cout << "The time AVL tree: " << elapsed_2.count() << " ns\n\n";

	tree = new RedBlackTree<double>;
	auto start_3 = chrono::steady_clock::now();
	fun(tree);
	tree->printTree();
	auto finish_3 = chrono::steady_clock::now();
	chrono::duration<int64_t, nano> elapsed_3 = finish_3 - start_3;
	delete tree;
	tree = nullptr;
	cout << "The time Red Black Tree: " << elapsed_3.count() << " ns\n\n";
}

int main()
{
	Time();
	return 0;
}
