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

void BTreeNode::add_node(int val)
{
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
	else
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
}

void BTreeNode::delete_node(int val)
{
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
		balance = right->height;
		right->calcBalance();
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
		return 1;
	}
		
}

void BTreeNode::rotate()
{
	
}

BTreeNode* BTreeNode::find(int val, bool visible)
{
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

BTreeNode* BTreeNode::findImbalance(bool visible)
{
	if (visible)
		std::cout << "Looking at " << value << std::endl;
	if (balance > 1 || balance < -1)
	{
		if (visible)
			std::cout << "Found!\n";

		return this;
	}
	if (left != nullptr)
	{
		left->findImbalance();
	}
	if (right != nullptr)
	{
		right->findImbalance();
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

void AVLTree::add_val(int val)
{
	root->add_node(val);
	updateTree();
}

void AVLTree::delete_val(int val)
{
	root->delete_node(val);
	updateTree();
}

BTreeNode* AVLTree::find(int val, bool visible)
{
	return root->find(val, visible);
}

BTreeNode* AVLTree::findImbalance()
{
	root->findImbalance();
}

void AVLTree::showTree()
{
	std::cout << std::endl;
	if (root != nullptr)
	{
		root->showSubTree();
	}
}

bool AVLTree::updateTree()
{
	root->height = root->get_height();
	root->calcBalance();
	while (!findImbalance())
	{
		lastOccur->rotate();
	}
	return true;
}
