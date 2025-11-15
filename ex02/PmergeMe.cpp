#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>

PmergeMe::PmergeMe(void) {}

PmergeMe::~PmergeMe(void) {}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs)
{
	if (this != &rhs)
	{
		_vector = rhs._vector;
		_deque = rhs._deque;
	}
	return *this;
}

bool PmergeMe::parseInput(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		char* endptr;
		long value = std::strtol(argv[i], &endptr, 10);
		
		if (*endptr != '\0' || value <= 0)
		{
			std::cerr << "Error" << std::endl;
			return false;
		}
		
		_vector.push_back(static_cast<int>(value));
		_deque.push_back(static_cast<int>(value));
	}
	return true;
}

void PmergeMe::mergeInsertVector(std::vector<int>& arr)
{
	if (arr.size() <= 1)
		return;
	
	std::vector<std::pair<int, int> > pairs;
	
	for (size_t i = 0; i + 1 < arr.size(); i += 2)
	{
		if (arr[i] > arr[i + 1])
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
		else
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
	}
	
	int unpaired = (arr.size() % 2 == 1) ? arr[arr.size() - 1] : -1;
	
	std::vector<int> smaller;
	for (size_t i = 0; i < pairs.size(); i++)
		smaller.push_back(pairs[i].first);
	
	mergeInsertVector(smaller);
	
	std::vector<int> sorted;
	for (size_t i = 0; i < smaller.size(); i++)
		sorted.push_back(smaller[i]);
	
	for (size_t i = 0; i < pairs.size(); i++)
	{
		int larger = pairs[i].second;
		std::vector<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), larger);
		sorted.insert(pos, larger);
	}
	
	if (unpaired != -1)
	{
		std::vector<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), unpaired);
		sorted.insert(pos, unpaired);
	}
	
	arr = sorted;
}

void PmergeMe::mergeInsertDeque(std::deque<int>& arr)
{
	if (arr.size() <= 1)
		return;
	
	std::deque<std::pair<int, int> > pairs;
	
	for (size_t i = 0; i + 1 < arr.size(); i += 2)
	{
		if (arr[i] > arr[i + 1])
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
		else
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
	}
	
	int unpaired = (arr.size() % 2 == 1) ? arr[arr.size() - 1] : -1;
	
	std::deque<int> smaller;
	for (size_t i = 0; i < pairs.size(); i++)
		smaller.push_back(pairs[i].first);
	
	mergeInsertDeque(smaller);
	
	std::deque<int> sorted;
	for (size_t i = 0; i < smaller.size(); i++)
		sorted.push_back(smaller[i]);
	
	for (size_t i = 0; i < pairs.size(); i++)
	{
		int larger = pairs[i].second;
		std::deque<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), larger);
		sorted.insert(pos, larger);
	}
	
	if (unpaired != -1)
	{
		std::deque<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), unpaired);
		sorted.insert(pos, unpaired);
	}
	
	arr = sorted;
}

void PmergeMe::sort(void)
{
	timeval start, end;
	
	gettimeofday(&start, NULL);
	mergeInsertVector(_vector);
	gettimeofday(&end, NULL);
	
	double timeVector = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
	
	gettimeofday(&start, NULL);
	mergeInsertDeque(_deque);
	gettimeofday(&end, NULL);
	
	double timeDeque = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
	
	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : " << timeVector << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque : " << timeDeque << " us" << std::endl;
}

void PmergeMe::display(void)
{
	std::cout << "Before: ";
	for (size_t i = 0; i < _vector.size(); i++)
	{
		if (i > 0) std::cout << " ";
		std::cout << _vector[i];
	}
	std::cout << std::endl;
	
	std::cout << "After: ";
	for (size_t i = 0; i < _vector.size(); i++)
	{
		if (i > 0) std::cout << " ";
		std::cout << _vector[i];
	}
	std::cout << std::endl;
}
