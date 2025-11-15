#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <sys/time.h>

class PmergeMe
{
private:
	std::vector<int> _vector;
	std::deque<int> _deque;
	
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& rhs);
	
	void mergeInsertVector(std::vector<int>& arr);
	void mergeInsertDeque(std::deque<int>& arr);

public:
	PmergeMe(void);
	~PmergeMe(void);
	
	bool parseInput(int argc, char** argv);
	void sort(void);
	void display(void);
};

#endif
