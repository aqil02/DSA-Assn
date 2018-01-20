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
	Tree(); 
	~Tree();
	node *insert(node *root,ItemType value); 
	void insert(int value);
	node *minvaluenode(node *node);
	node *remove(node* tempnode,ItemType value); 
	void remove(ItemType value);

	void search(ItemType value,node *targetnode);
	void search(ItemType value);

	void displayinasc();
	void displayinasc(node *tempnode); 

	void displayNthnode(int value);
	int printlevel(node *root, int level, int nth);
	void printlevelorder(node *root, int nth);

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