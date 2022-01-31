#include <iostream>

#include "yanl.h"

int main() {
  // auto x = yanl::ones<double>(3, 3);
  // auto y = yanl::zeros<double>(3, 3);
  // y(0, 0) = 1;
  // y(1, 1) = 2;
  // y(2, 2) = 3;

  // auto z = x + y;

  // std::cout << x << "\n";
  // std::cout << y << "\n";
  // std::cout << z << "\n";

  // auto identity = yanl::eye<double>(5);
  // // std::cout << identity << "\n";

  // // std::cout << x * y << "\n";

  // auto [lu, p] = yanl::linear_algebra::lu_decompose(z);

  // std::cout << lu << "\n";
  // double det = yanl::linear_algebra::det(z);
  // std::cout << det << "\n";

  auto A = yanl::rand<double>(3, 3);
  std::cout << "A =\n" << A << "\n";

  auto b = yanl::ones<double>(3, 1);
  std::cout << "b =\n" << b << "\n";

  auto x = yanl::linear_algebra::solve(A, b);
  std::cout << "x =\n" << x << "\n";
  
  auto prod = A * x;
  std::cout << "A * x =\n" << prod << "\n";
  
  auto norm_of_b = yanl::linear_algebra::norm(b); 
  std::cout << norm_of_b << "\n";

}
