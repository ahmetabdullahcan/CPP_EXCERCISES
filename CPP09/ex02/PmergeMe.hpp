#pragma once

#include <iostream>
#include <algorithm>
#include <fstream>
#include <deque>
#include <vector>
#include <sys/time.h>

template <typename Container>
void binaryInsert(Container &sorted, int value)
{
	typename Container::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), value);
	sorted.insert(pos, value);
}

template <typename Container>
void fordJohnsonSort(Container &data)
{
	if (data.size() <= 1)
		return;

	typedef typename Container::value_type T;
	std::vector<std::pair<T, T> > pairs;
	std::vector<T> mainChain;
	std::vector<T> pendingElements;

	typename Container::iterator it = data.begin();
	while (it != data.end())
	{
		T first = *it;
		++it;
		if (it != data.end())
		{
			T second = *it;
			if (first > second)
				std::swap(first, second);
			pairs.push_back(std::make_pair(first, second));
			++it;
		}
		else
		{
			pendingElements.push_back(first);
		}
	}

	for (size_t i = 0; i < pairs.size(); ++i)
		mainChain.push_back(pairs[i].second);

	fordJohnsonSort(mainChain);

	for (size_t i = 0; i < pairs.size(); ++i)
		binaryInsert(mainChain, pairs[i].first);

	for (size_t i = 0; i < pendingElements.size(); ++i)
		binaryInsert(mainChain, pendingElements[i]);

	data.assign(mainChain.begin(), mainChain.end());
}

class PmergeMe
{
	private:
		std::deque<int> sortedDeque;
		std::deque<int> originalNumbers;
		std::vector<int> sortedVector;

	public:
		PmergeMe();
		PmergeMe(PmergeMe &other);
		~PmergeMe();
		PmergeMe &operator=(PmergeMe &other);
		void execute(char **arguments);
};
