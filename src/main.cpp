#include <iostream>

#include "yanl.h"

int main(){
    auto x = yanl::zeros<double>(3, 3);
    std::cout << x;
}