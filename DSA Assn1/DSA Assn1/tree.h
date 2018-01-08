#pragma once

typedef int ItemType;

class Tree
{
private:
	struct node
	{
		ItemType value;
		node *left_node;
		node *right_node;
	};
	node *root;
public:
	Tree(); //Step 1: Core Functionality 
	~Tree();

	void insert(ItemType value); //Step 1: Insert (Regardless of balancing, only follow basic rules)
	void remove(ItemType value);
	void search(ItemType value);
	void displayinasc();
	void displayNthnode(ItemType nth);
	void fulldisplay();
};