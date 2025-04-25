#include "easyfind.hpp"
#include <iostream>
#include <vector>

int main(void)
{
    std::vector<int> vec;

    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    try {
        std::cout << "Found in vector: " << *easyfind(vec, 5) << std::endl;
        std::cout << "Found in vector: " << *easyfind(vec, 15) << std::endl; 
    } catch (const NotFoundException& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}