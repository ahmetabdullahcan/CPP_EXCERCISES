#include "PmergeMe.hpp"
#include <cstdlib>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(PmergeMe &other)
{
	this->sortedDeque = other.sortedDeque;
	this->sortedVector = other.sortedVector;
	this->originalNumbers = other.originalNumbers;
}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(PmergeMe &other)
{
	this->sortedDeque = other.sortedDeque;
	this->sortedVector = other.sortedVector;
	this->originalNumbers = other.originalNumbers;
	return *this;
}

void PmergeMe::execute(char **arguments)
{
	struct timeval startTime, endTime;

	for (int index = 1; arguments[index]; index++)
		originalNumbers.push_back(std::atoi(arguments[index]));

	if (originalNumbers.size() < 2)
		throw std::exception();

	for (unsigned long index = 0; index < originalNumbers.size(); index++)
	{
		if (originalNumbers.at(index) < 0)
			throw std::exception();
	}

	std::cout << "Before: ";
	for (unsigned long index = 0; index < originalNumbers.size(); index++)
	{
		std::cout << originalNumbers.at(index);
		if (index != originalNumbers.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;

	gettimeofday(&startTime, NULL);
	for (int index = 1; arguments[index]; index++)
		sortedDeque.push_back(std::atoi(arguments[index]));
	fordJohnsonSort(sortedDeque);
	gettimeofday(&endTime, NULL);

	std::cout << "After: ";
	for (unsigned long index = 0; index < sortedDeque.size(); index++)
	{
		std::cout << sortedDeque.at(index);
		if (index != sortedDeque.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl
			  << std::fixed << "Time to process a range of " << sortedDeque.size()
			  << " elements with std::deque : "
			  << (endTime.tv_sec - startTime.tv_sec) * 1000000 + endTime.tv_usec - startTime.tv_usec
			  << " us" << std::endl;

	gettimeofday(&startTime, NULL);
	for (int index = 1; arguments[index]; index++)
		sortedVector.push_back(std::atoi(arguments[index]));
	fordJohnsonSort(sortedVector);
	gettimeofday(&endTime, NULL);

	std::cout << std::fixed << "Time to process a range of " << sortedVector.size()
			  << " elements with std::vector : "
			  << (endTime.tv_sec - startTime.tv_sec) * 1000000 + endTime.tv_usec - startTime.tv_usec
			  << " us" << std::endl;
}
