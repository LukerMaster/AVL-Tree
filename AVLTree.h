#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <algorithm>

enum class eRotation
{
	RR,
	LL,
	RL,
	LR
};

struct BTreeNode
{
	BTreeNode() = delete;
	BTreeNode(BTreeNode* parent_, int value_);
	BTreeNode* left;
	BTreeNode* right;
	BTreeNode* parent;
	int value;
	unsigned int height;
	short balance;
	void add_node(int val);
	void delete_node(int val);
	void showSubTree();
	void calcBalance();
	unsigned int get_height();

	void update();
	void rotate();
	BTreeNode* find(int val, bool visible = false);
	BTreeNode* findImbalance(bool visible = false);
	BTreeNode* findUpTo(int val);
};

class AVLTree
{
public:
	AVLTree() = delete;
	AVLTree(int root_value);

	void add_val(int val);
	void delete_val(int val);
	BTreeNode* find(int val, bool visible = false);
	BTreeNode* findImbalance();
	void showTree();
	bool updateTree(); // Returns true if balanced, repeats itself if false.
private:
	BTreeNode* root;
	BTreeNode* lastOccur; // Last occurance of disbalance in the tree. Is nullptr if tree is balanced.
};

