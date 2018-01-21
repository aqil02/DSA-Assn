//Team Member's names: Aqil Ahmad Subahan, Lee ZhiYong
//Team Member's IDs: S10166743C, S10173753F

#include "stdafx.h"
#include "tree.h"
#include <iostream>

using namespace std;
Tree tree; //Defines the tree
int nodecount = 0; //Global counter to check number of nodes for user validation
//Renders the menu and checks if user-input is an integer, sets it to 0 and returns a proper choice integer otherwise
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
//Switch case to refer program to the proper tree functions. Case 0 represents an invalid choice as it either means the user entered a non-integer which results in choice being 0
//Or the user entered 0 which are both invalid anyway
//Each option has user-validation to ensure a correct integer is entered for added and removing including checking if values already exists or not in the tree before running the functions
//Default case means any integer other than 1-7, resulting in an error message
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
		if (cin.fail() || value < 0)
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
		if (cin.fail() || value < 0)
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
			nodecount++;
			cout << endl;
			menu();
		}
	case 3:
		cout << "Please enter value to be removed: ";
		cin >> value;
		if (cin.fail() || value < 0)
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
			nodecount--;
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
//Intiliases the program by adding the correct numbers to the tree at the start of the program
//Uses user validation and restarts the main program if input is not an integer
//Uses a for-loop afterwards to add the numbers one-by-one and initialises the main-menu afterwards
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
		nodecount++;
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

