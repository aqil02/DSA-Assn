// DSA Assn1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tree.h"
#include <iostream>

using namespace std;
Tree tree;
int rendermenu()
{
	cout << "1. Search for value" << endl
		<< "2. Add a value" << endl
		<< "3. Remove a value" << endl
		<< "4. Diplay values in ascending order" << endl
		<< "5. Display nth node" << endl
		<< "6. Display full tree" << endl
		<< "7. Exit" << endl;
	cout << "Please enter a selection: ";
	int choice;
	cin >> choice;
	return choice;
}
void menu()
{
	int choice;
	int value;
	choice = rendermenu();
	switch (choice)
	{
	case 1:
		cout << "Please enter value to be searched: ";
		cin >> value;
		tree.search(value);
		menu();
	case 2:
		cout << "Please enter value to be inserted: ";
		cin >> value;
		tree.insert(value);
		menu();
	case 3:
		cout << "Please enter value to be removed: ";
		cin >> value;
		tree.remove(value);
		menu();
	case 4:
		tree.displayinasc();
		cout << endl;
		menu();
	case 5:
		cout << "Please enter node to be displayed: ";
		cin >> value;
		tree.printlevelorder(value);
		menu();
	case 6:
		tree.fulldisplay();
		menu();
	case 7:
		exit(0);
	default :
		cout << "Invalid choice" << endl;
		menu();
	}
}
int main()
{
	int total;
	
	cout << "Please enter a number to intialise the program: ";
	cin >> total;
	int currenttotal = 0;
	for (int i = 1; i <= total; i++)
	{
		tree.insert(i);
		currenttotal += i;
		if (currenttotal > total)
		{
			break;
		}
	}
	menu();
	system("PAUSE");
    return 0;
}

