#include "iter.hpp"

int sum(int &x) {
    return x + 1;
}

void sums(std::string &x) {
    x += "!";
}

int square(int &x) {
    return x * x;
}

int main(void){
    int arr[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(arr) / sizeof(arr[0]);

    iter(arr, length, [](int &x) { std::cout << x << " "; });
    std::cout << std::endl;

    iter(arr, length, [](int &x) { sum(x); });
    iter(arr, length, [](int &x) { std::cout << x << " "; });
    std::cout << std::endl;

    std::string strArr[] = {"Hello", "World", "!"};
    size_t strLength = sizeof(strArr) / sizeof(strArr[0]);
    iter(strArr, strLength, [](std::string &x) { std::cout << x << " "; });
    std::cout << std::endl;
    iter(strArr, strLength, [](std::string &x) { sums(x); });
    iter(strArr, strLength, [](std::string &x) { std::cout << x << " "; });
    std::cout << std::endl;

    return 0;
}