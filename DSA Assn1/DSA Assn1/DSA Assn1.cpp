// DSA Assn1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tree.h"
#include <iostream>

using namespace std;

int main()
{
	int choice;
	int number;
	Tree tree;
	choice = 5;
	number = 35;
	if (choice == 5)
	{
		int total = 0;
		for (int i = 1; i <= number; i++)
		{
			tree.insert(i);
			total += i;
			if (total > number)
			{
				break;
			}
		}
	}
	cout <<
	system("PAUSE");
    return 0;
}

