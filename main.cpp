#include <iostream>
#include "AVLTree.h"
int main()
{
	std::cout << "Sandbox for AVL Tree!" << std::endl;
	AVLTree x(1);
	x.add_val(10, true);
	x.showTree();
	x.add_val(2, true);
	x.showTree();
	x.add_val(9, true);
	x.showTree();
	x.add_val(3, true);
	x.showTree();
	x.add_val(8, true);
	x.showTree();
	x.add_val(4, true);
	x.showTree();
	x.add_val(7, true);
	x.showTree();
	x.add_val(-1, true);
	x.showTree();
	x.add_val(-2, true);
	x.showTree();
	x.add_val(-3, true);
	x.showTree();
	x.add_val(-4, true);
	x.showTree();
	//std::cout << "\n\n\nDONE!\n\n\n";
	x.delete_val(3);
	//x.delete_val(7);
	x.showTree();
	std::cin.get();
	return 0;
}