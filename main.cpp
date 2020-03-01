#include <iostream>
#include "AVLTree.h"

int main()
{
	{
		std::cout << "Sandbox for AVL Tree!" << std::endl;
		AVLTree x(1);
		x.delete_val(1);
		x.add_val(20);
		x.delete_val(20);
		x.delete_val(-2);
		x.add_val(5);
		BTreeNode* s = x.find(5);
		x.showTree();
		std::cin.get();
	}
	std::cout << "Tree destroyed!" << std::endl;
	std::cin.get();
	return 0;
}