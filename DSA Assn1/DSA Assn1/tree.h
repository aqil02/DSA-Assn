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
		node() :value(NULL),left_node(NULL), right_node(NULL) {}
	};
	node *root;
public:
	Tree(); //Step 1: Core Functionality 
	~Tree();

	void insert(ItemType value); //Step 1: Insert (Regardless of balancing, only follow basic rules) //COMPLETE
	void remove(ItemType value); 
	int search(ItemType value,node *targetnode);
	void traverse(ItemType value);
	void displayinasc();
	void displayinasc(node *tempnode); //COMPLETE
	//void displayNthnode(ItemType nth);
	void fulldisplay(node *tempnode, int level);
	void fulldisplay();//Overloaded
	//Rebalancing algorithm
	node *rebalance(node *temp); 
	int height(node *temp);
	int diff(node *temp);
	node *leftrotate(node *nodeN);
	node *rightrotate(node *nodeN);
	node *leftrightrotate(node *nodeN);
	node *rightleftrotate(node *nodeN);
	
};