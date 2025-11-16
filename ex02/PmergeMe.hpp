#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <utility>

class PmergeMe
{
private:
	std::vector<int> _vector;
	std::deque<int> _deque;
	
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& rhs);
	
	void fordJohnsonVector(std::vector<int>& arr);
	void fordJohnsonDeque(std::deque<int>& arr);
	
	// Helper for generating Jacobsthal numbers
	int jacobsthal(int n);
	
public:
	PmergeMe(void);
	~PmergeMe(void);
	
	bool parseInput(int argc, char** argv);
	void sort(void);
};

#endif
