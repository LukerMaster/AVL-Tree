#include <iostream>
#include "AVLTree.h"
int main()
{
	std::cout << "Sandbox for AVL Tree!" << std::endl;
	AVLTree x(4);
	x.add_val(2);
	x.add_val(6);
	x.add_val(1);
	x.add_val(3);
	x.add_val(5);
	x.add_val(7);
	x.add_val(8);
	x.add_val(9);
	//std::cout << "\n\n\nDONE!\n\n\n";
	x.delete_val(6);
	//x.delete_val(4);
	x.showTree();
	std::cin.get();
}