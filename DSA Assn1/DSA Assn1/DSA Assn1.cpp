// DSA Assn1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tree.h"
#include <iostream>

using namespace std;

int main()
{
	Tree tree;
	tree.insert(2);
	tree.insert(3);
	tree.insert(1);
	tree.insert(4);
	tree.insert(5);
	cout << "Success" << endl;
	system("PAUSE");
	tree.traverse(1);
	system("PAUSE");
    return 0;
}

