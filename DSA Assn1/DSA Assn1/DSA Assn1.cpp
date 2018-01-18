// DSA Assn1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tree.h"
#include <iostream>

using namespace std;

int main()
{
	Tree tree;
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	//tree.insert(6);
	//tree.insert(7);
	//tree.insert(8);
	//tree.insert(9);
	//tree.insert(10);
	system("PAUSE");
	tree.fulldisplay();
	//tree.traverse(7);
	//tree.traverse(5);
	//tree.remove(5);
	//tree.traverse(5);
	tree.displayNthnode();
	
	system("PAUSE");
    return 0;
}

