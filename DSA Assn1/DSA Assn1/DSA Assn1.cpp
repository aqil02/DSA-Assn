// DSA Assn1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tree.h"
#include <iostream>

using namespace std;
Tree tree;
int nodecount;
int rendermenu()
{
		cout << endl
		<< "1. Search for value" << endl
		<< "2. Add a value" << endl
		<< "3. Remove a value" << endl
		<< "4. Diplay values in ascending order" << endl
		<< "5. Display nth node" << endl
		<< "6. Display full tree" << endl
		<< "7. Exit" << endl;
	cout << "Please enter a selection: ";
	int choice;
	cin >> choice;
	if (cin.fail())
	{
		choice = 0;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return choice;
}
void menu()
{
	int choice;
	int value;
	choice = rendermenu();
	switch (choice)
	{
	case 0:
		cout << "Invalid choice" << endl;
		menu();
	case 1:
		cout << "Please enter value to be searched: ";
		cin >> value;
		if (cin.fail())
		{
			cout << "Invalid choice" << endl;
			choice = 0;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			menu();
		}
		else {
			tree.search(value);
			menu();
		}
	case 2:
		cout << "Please enter value to be inserted: ";
		cin >> value;
		if (cin.fail())
		{
			cout << "Invalid choice" << endl;
			choice = 0;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			menu();
		}
		else 
		{
			tree.insert(value);
			cout << endl;
			menu();
		}
	case 3:
		cout << "Please enter value to be removed: ";
		cin >> value;
		if (cin.fail())
		{
			cout << "Invalid choice" << endl;
			choice = 0;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			menu();
		}
		else
		{
			tree.remove(value);
			cout << endl;
			menu();
		}
	case 4:
		tree.displayinasc();
		cout << endl;
		menu();
	case 5:
		cout << "Please enter node to be displayed: ";
		cin >> value;
		if (cin.fail())
		{
			cout << "Invalid choice" << endl;
			choice = 0;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			menu();
		}
		else
		{
			if (value > nodecount)
			{
				cout << "WARNING:Value entered more than total nodes, exiting..." << endl;
				menu();
			}
			tree.displayNthnode(value);
			menu();
		}
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
	if (cin.fail())
	{
		cout << "Invalid choice" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		main();
	}
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

