cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(BINTREELIB_SOURCE	
	binTreeLib/node.h
	binTreeLib/AVLtree.h
	binTreeLib/BinaryTree.h
	binTreeLib/RedBlackTree.h

	binTreeLib/node.cpp
)

add_library(binTreeLib STATIC ${BINTREELIB_SOURCE})