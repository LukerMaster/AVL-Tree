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
	void add_node(int val, bool visible = false);
	void delete_node(int val, bool visible = false);
	void showSubTree();
	void calcBalance();
	unsigned int get_height();

	void update();
	void rotate(bool visible = false);

	void rotate_LL(BTreeNode* pivot);
	void rotate_RR(BTreeNode* pivot);
	void prerotate_RL(BTreeNode* pivot);
	void prerotate_LR(BTreeNode* pivot);

	BTreeNode* find(int val, bool visible = false);
	void findImbalance(BTreeNode** ptr, bool visible = false);
	BTreeNode* findUpTo(int val);
};

class AVLTree
{
public:
	AVLTree() = delete;
	AVLTree(int root_value);

	void add_val(int val, bool visible = false);
	void delete_val(int val, bool visible = false);
	BTreeNode* find(int val, bool visible = false);
	void showTree();
	bool updateTree(bool visible); // Returns true if balanced, repeats itself if false.
	BTreeNode* getNewRoot(BTreeNode* current_root);
private:
	BTreeNode* root;
	BTreeNode* lastOccur; // Last occurance of disbalance in the tree. Is nullptr if tree is balanced.
};

