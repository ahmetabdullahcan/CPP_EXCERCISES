#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << std::endl;
        return 1;
    }
    try{
        PmergeMe pmerge;
        pmerge.execute(argv);
    }
    catch(std::exception &s){
        std::cerr << "Error" << std::endl;
    }
}