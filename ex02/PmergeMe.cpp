#include "PmergeMe.hpp"
#include <sys/time.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

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

int PmergeMe::jacobsthal(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

void PmergeMe::fordJohnsonVector(std::vector<int>& arr)
{
	if (arr.size() <= 1)
		return;
	std::vector<std::pair<int, int> > pairs;
	int unpaired = -1;
	
	for (size_t i = 0; i + 1 < arr.size(); i += 2)
	{
		if (arr[i] > arr[i + 1])
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
		else
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
	}
	
	if (arr.size() % 2 == 1)
		unpaired = arr[arr.size() - 1];
	std::vector<int> smaller;
	for (size_t i = 0; i < pairs.size(); i++)
		smaller.push_back(pairs[i].first);
	
	fordJohnsonVector(smaller);
	
	std::vector<int> result;
	for (size_t i = 0; i < smaller.size(); i++)
		result.push_back(smaller[i]);
	std::vector<int> largerElements;
	for (size_t i = 0; i < pairs.size(); i++)
		largerElements.push_back(pairs[i].second);
	
	for (size_t i = 0; i < largerElements.size(); i++)
	{
		std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), largerElements[i]);
		result.insert(pos, largerElements[i]);
	}
	
	if (unpaired != -1)
	{
		std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), unpaired);
		result.insert(pos, unpaired);
	}
	
	arr = result;
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& arr)
{
	if (arr.size() <= 1)
		return;
	
	std::deque<std::pair<int, int> > pairs;
	int unpaired = -1;
	
	for (size_t i = 0; i + 1 < arr.size(); i += 2)
	{
		if (arr[i] > arr[i + 1])
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
		else
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
	}
	
	if (arr.size() % 2 == 1)
		unpaired = arr[arr.size() - 1];
	
	std::deque<int> smaller;
	for (size_t i = 0; i < pairs.size(); i++)
		smaller.push_back(pairs[i].first);
	
	fordJohnsonDeque(smaller);
	
	std::deque<int> result;
	for (size_t i = 0; i < smaller.size(); i++)
		result.push_back(smaller[i]);
	
	std::deque<int> largerElements;
	for (size_t i = 0; i < pairs.size(); i++)
		largerElements.push_back(pairs[i].second);
	
	for (size_t i = 0; i < largerElements.size(); i++)
	{
		std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), largerElements[i]);
		result.insert(pos, largerElements[i]);
	}
	
	if (unpaired != -1)
	{
		std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), unpaired);
		result.insert(pos, unpaired);
	}
	
	arr = result;
}

void PmergeMe::sort(void)
{
    std::cout << "Before: ";
    for (size_t i = 0; i < _vector.size(); ++i)
    {
        if (i > 0) std::cout << " ";
        std::cout << _vector[i];
    }
    std::cout << std::endl;
    timeval start, end;
    gettimeofday(&start, NULL);
    fordJohnsonVector(_vector);
    gettimeofday(&end, NULL);
    double timeVector = (end.tv_sec - start.tv_sec)*1000000.0 + (end.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    fordJohnsonDeque(_deque);
    gettimeofday(&end, NULL);
    double timeDeque = (end.tv_sec - start.tv_sec)*1000000.0 + (end.tv_usec - start.tv_usec);

    std::cout << "After: ";
    for (size_t i = 0; i < _vector.size(); ++i)
    {
        if (i > 0) std::cout << " ";
        std::cout << _vector[i];
    }
    std::cout << std::endl;


    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Time to process a range of " << _vector.size()
              << " elements with std::vector: " << timeVector << " us" << std::endl;
    std::cout << "Time to process a range of " << _deque.size()
              << " elements with std::deque: " << timeDeque << " us" << std::endl;
}


