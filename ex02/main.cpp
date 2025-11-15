#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	PmergeMe sorter;
	
	if (!sorter.parseInput(argc, argv))
		return 1;
	
	std::cout << "Before: ";
	for (int i = 1; i < argc; i++)
	{
		if (i > 1) std::cout << " ";
		std::cout << argv[i];
	}
	std::cout << std::endl;
	
	sorter.sort();
	sorter.display();
	
	return 0;
}
