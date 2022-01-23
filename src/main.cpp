#include <iostream>

#include "yanl.h"

int main(){
    auto x = yanl::Vector<double>::zeros(3);
    std::cout << x;
}