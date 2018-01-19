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

	node *insert(node *root,ItemType value); //Step 1: Insert (Regardless of balancing, only follow basic rules) //COMPLETE
	void insert(int value);
	node *minvaluenode(node *node);
	node *remove(node* tempnode,ItemType value); 
	void remove(ItemType value);

	int search(ItemType value,node *targetnode);
	void search(ItemType value);

	void displayinasc();
	void displayinasc(node *tempnode); //COMPLETE

	void displayNthnode();
	void displayNthnode(node *tempnode,ItemType nth,int counter);

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