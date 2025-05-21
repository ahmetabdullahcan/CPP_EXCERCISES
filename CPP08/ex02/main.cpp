#include "MutantStack.hpp"
#include <iostream>
#include <list>

int main() {
    std::cout << "=== MutantStack test ===" << std::endl;
    MutantStack<int> mstack;
    
    mstack.push(5);
    mstack.push(17);
    
    std::cout << "Top element: " << mstack.top() << std::endl;
    
    mstack.pop();
    std::cout << "Size after pop: " << mstack.size() << std::endl;
    
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    std::cout << "Iterating through MutantStack: " << std::endl;
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    
    ++it;
    --it;
    
    while (it != ite) {
        std::cout << *it << std::endl;
        ++it;
    }
    
    std::cout << "\n=== std::list test for comparison ===" << std::endl;
    std::list<int> lst;
    
    lst.push_back(5);
    lst.push_back(17);
    
    std::cout << "Back element: " << lst.back() << std::endl;
    
    lst.pop_back();
    std::cout << "Size after pop: " << lst.size() << std::endl;
    
    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(737);
    lst.push_back(0);
    
    std::cout << "Iterating through list: " << std::endl;
    std::list<int>::iterator lst_it = lst.begin();
    std::list<int>::iterator lst_ite = lst.end();
    
    ++lst_it;
    --lst_it;
    
    while (lst_it != lst_ite) {
        std::cout << *lst_it << std::endl;
        ++lst_it;
    }
    
    std::stack<int> s(mstack);
    std::cout << "\nSize of copied stack: " << s.size() << std::endl;
    std::cout << "Top element of copied stack: " << s.top() << std::endl;
    
    return 0;
}