#include "AVLTree.h"

BTreeNode::BTreeNode(BTreeNode* parent_, int value_)
	:parent(parent_),
	left(nullptr),
	right(nullptr),
	value(value_),
	height(1),
	balance(0)
{
	//std::cout << "Constr" << std::endl;
}

void BTreeNode::add_node(int val, bool visible)
{
	if (visible)
		std::cout << "Adding: " << val << std::endl;

	if (val < value)
	{
		if (left == nullptr)
		{
			left = new BTreeNode(this, val);
		}
		else
		{
			left->add_node(val);
		}
	}
	else if (val > value)
	{
		if (right == nullptr)
		{
			right = new BTreeNode(this, val);
		}
		else
		{
			right->add_node(val);
		}
		
	}
	else
	{
		if (visible)
			std::cout << "Value " << val << " already exists. Ignoring." << std::endl;
	}
}

void BTreeNode::delete_node(int val, bool visible)
{
	if (visible)
		std::cout << "Adding: " << val << std::endl;

	if (val == value)
	{
		if (left != nullptr) // If I have child nodes to the left,
		{	                 // try to swap value with biggest node on the left subtree.
			if (left->right == nullptr) // If my left child does not have any children, then I swap with
			{							// it. Note that now I need to cut off LEFT connection, as it would
				BTreeNode* ptr = left;  // connect to my deleted left child.
				value = ptr->value;
				left = nullptr;
				delete ptr;
			}							// Now if my left child is NOT A LEAF!
			else						// If my left child HAS right subtree, then swap with biggest
			{							// of them. Now I need to cut off IT'S PARENTS RIGHT node, since
				BTreeNode* ptr = findUpTo(value); // it is on the very right to my left subtree.
				value = ptr->value;
				ptr->parent->right = nullptr;
				delete ptr;
			}
		}
		else if (right != nullptr)		// If I don't have smaller childs, I can just swap with first bigger
		{								// node. Just swap with child on the left, then delete it. done.
			BTreeNode* ptr = right;
			value = ptr->value;
			left = ptr->left;
			right = ptr->right;
			delete ptr;
		}
	}
	else if (val < value)
	{
		left->delete_node(val);
	}
	else if (val >= value)
	{
		right->delete_node(val);
	}
}

void BTreeNode::showSubTree()
{
	std::cout << "Value: " << value << std::endl;
	std::cout << "{\n    Height: " << height << std::endl;
	if (parent != nullptr)
		std::cout << "    Parent: " << parent->value << std::endl;

	std::cout << "    Balance: " << balance << std::endl;

	if (left != nullptr)
		std::cout << "\n    Left: " << left->value << std::endl;
	if (right != nullptr)
		std::cout << "    Right: " << right->value << std::endl;
	std::cout << "}" << std::endl;

	if (left != nullptr)
		left->showSubTree();
	if (right != nullptr)
		right->showSubTree();
}

void BTreeNode::calcBalance() // CALCULATE, not rotate. CALCULATE the balance. If not in <-1; 1>, rotate();
{
	if (left != nullptr && right != nullptr)
	{
		balance = left->height - right->height;
		left->calcBalance();
		right->calcBalance();
	}
	else if (left != nullptr)
	{
		balance = left->height;
		left->calcBalance();
	}
	else if (right != nullptr)
	{
		balance = 0 - right->height; // Remember: left - right. left = 0. so "0 - right".
		right->calcBalance();
	}
	else if (left == nullptr && right == nullptr) // If leaf, balance is 0.
	{
		balance = 0;
	}
}

unsigned int BTreeNode::get_height()  // Do a recursive check of height. Add 1 to every node after a leaf
{									  // and return to your parent until you reach the root.
	if (left != nullptr && right != nullptr)
	{
		height = std::max(left->get_height(), right->get_height()) + 1; // We need HEIGHT, not amount of nodes
		return height;													// so we do max(left, right).
	}
	else if (right != nullptr) // If no left children, just check right.
	{
		height = right->get_height() + 1; 
		return height;
	}
	else if (left != nullptr) // If no right children, just check left.
	{
		height = left->get_height() + 1;
		return height;
	}
	else // If leaf, height is just 1. Remember - HEIGHT, not BALANCE. We calculate balance later.
	{
		height = 1;
		return 1;
	}
		
}

void BTreeNode::rotate(bool visible)
{
	// Keep in mind that currently, this function is called only on AVLTree::lastOccur which is a pointer
	// to lowest (height-wise) disbalanced node. Thus no arguments, no nothing.
	// if this function is called it just MEANS that balance is not in <-1, 1>.
	BTreeNode* pivot;
	BTreeNode* first;
	BTreeNode* second;
	if (balance > 1) // Left-heavy! LX-Rotation.
	{
		std::cout << "Balance: " << balance << std::endl;
		// if balance is greater than 1 it just MEANS that left child exists.
		if (left->balance > 0) // Left-of-left disbalance! LL-Rotation.
		{
			if (visible)
				std::cout << "Performing LL-Rotation on " << value << std::endl;

			rotate_LL(this);
		}
		else // Right-of-left disbalance! LR-Rotation.
		{
			if (visible)
				std::cout << "Performing LR-Rotation on " << value << std::endl;

			prerotate_LR(this);
			rotate_LL(this);
		}
	}
	else // Right-heavy! RX-Rotation.
	{
		// if balance is lower than -1 it just MEANS that right child exists.
		if (right->balance < 0) // Right-of-right disbalance! RR-Rotation.
		{
			if (visible)
				std::cout << "Performing RR-Rotation on " << value << std::endl;

			rotate_RR(this);
		}
		else // Left-of-right disbalance! RL-Rotation.
		{
			if (visible)
				std::cout << "Performing RL-Rotation on " << value << std::endl;

			prerotate_RL(this);
			rotate_RR(this);
		}

	}
}

void BTreeNode::rotate_LL(BTreeNode* pivot)
{
	BTreeNode* first = pivot->left;
	BTreeNode* second = pivot->left->left;

	first->parent = pivot->parent; // LL-Rotation.
	if (pivot->parent != nullptr)  // In case we rotate root (which does not have parents).
	{
	if (pivot->parent->left != nullptr)
		if (pivot->parent->left == pivot)
			pivot->parent->left = first;
	if (pivot->parent->right != nullptr)
		if (pivot->parent->right == pivot)
			pivot->parent->right = first;
	}
	pivot->left = first->right;
	if (pivot->left != nullptr)
		pivot->left->parent = pivot;

	pivot->parent = first;
	first->right = pivot;
}

void BTreeNode::rotate_RR(BTreeNode* pivot)
{
	BTreeNode* first = pivot->right;
	BTreeNode* second = pivot->right->right;

	first->parent = pivot->parent; // RR-Rotation.
	if (pivot->parent != nullptr)  // In case we rotate root (which does not have parents).
	{
		if (pivot->parent->left != nullptr)
			if (pivot->parent->left == pivot)
				pivot->parent->left = first;
		if (pivot->parent->right != nullptr)
			if (pivot->parent->right == pivot)
				pivot->parent->right = first;
	}
	pivot->right = first->left;
	if (pivot->right != nullptr)
		pivot->right->parent = pivot;

	pivot->parent = first;
	first->left = pivot;
}

void BTreeNode::prerotate_RL(BTreeNode* pivot)
{
	BTreeNode* first = pivot->right;
	BTreeNode* second = pivot->right->left;

	second->parent = pivot;
	pivot->right = second;

	first->left = second->right;
	if (second->right != nullptr)
		second->right->parent = first; // "Second" node may not have any children.

	second->right = first;
	first->parent = second;
}

void BTreeNode::prerotate_LR(BTreeNode* pivot)
{
	BTreeNode* first = pivot->left;
	BTreeNode* second = pivot->left->right;

	second->parent = pivot;
	pivot->left = second;

	first->right = second->left;
	if (second->left != nullptr)
		second->left->parent = first; // "Second" node may not have any children.

	second->left = first;
	first->parent = second;
}

BTreeNode* BTreeNode::find(int val, bool visible) // Just simply go through the tree like in normal BST
{											      // to find your desired number.
	if (visible)
		std::cout << "Looking at " << value << std::endl;
	if (value == val)
	{
		if (visible)
			std::cout << "Found!\n";

		return this;
	}
	else if (val < value)
	{
		if (visible)
			std::cout << "Searching left...\n";
		if (left != nullptr)
			left->find(val, visible);
		else
			return nullptr;
	}
	else
	{
		if (visible)
			std::cout << "Searching right...\n";
		if (right != nullptr)
			right->find(val, visible);
		else
			return nullptr;
	}
}

void BTreeNode::findImbalance(BTreeNode** ptr, bool visible) // Now we go down the tree to find the LOWEST
{															 // (height-wise) imbalance to rotate it first.
	if (visible)	// Pointer-to-pointer is needed since we need possibility to MODIFY the AVLTree::lastOccur
		std::cout << "Looking at disbalance of " << value << std::endl; // So we cannot just create variable
	if (balance > 1 || balance < -1)									// in the tree, as it'd be a copy.
	{
		if (visible)
			std::cout << "Found disbalance on " << value << "!" << std::endl;

		*ptr = this;
	}
	if (left != nullptr)
	{
		left->findImbalance(ptr, visible);
	}
	if (right != nullptr)
	{
		right->findImbalance(ptr, visible);
	}
}

BTreeNode* BTreeNode::findUpTo(int val)
{
	if (right != nullptr)
		right->findUpTo(val);
	else
		return this;

}

AVLTree::AVLTree(int root_value)
{
	root = new BTreeNode(nullptr, root_value);
}

void AVLTree::add_val(int val, bool visible)
{
	root->add_node(val, visible);
	updateTree(visible);
}

void AVLTree::delete_val(int val, bool visible)
{
	root->delete_node(val, visible);
	updateTree(visible);
}

BTreeNode* AVLTree::find(int val, bool visible)
{
	return root->find(val, visible);
}

void AVLTree::showTree()
{
	std::cout << std::endl;
	if (root != nullptr)
	{
		root->showSubTree();
	}
	std::cout << "=======" << std::endl;
}

bool AVLTree::updateTree(bool visible)
{
	root->height = root->get_height();		  // Calculate heights of every node, then perform calculations
	root->calcBalance();					  // of balances for each node. Then try to find LOWEST (height-wise)
	root->findImbalance(&lastOccur, visible); // occurance of imbalance.
	while (lastOccur != nullptr)			  // lastOccur is nullptr if no imbalance is found.
	{
		lastOccur->rotate(visible);			  // If imbalance is detected, recalculate tree and check for more
		lastOccur = nullptr;			      // imbalances until nothing found (pointer to occurances is null.
		root = getNewRoot(root);			  // If we rotate around root, then something else becomes new root.
		root->height = root->get_height();
		root->calcBalance();
		root->findImbalance(&lastOccur, visible);
		showTree();
	} 
	return true;
}

BTreeNode* AVLTree::getNewRoot(BTreeNode* current_root) // If something has a parent, then go to it.
{
	while (current_root->parent != nullptr)
		current_root = current_root->parent;
	return current_root;
}
