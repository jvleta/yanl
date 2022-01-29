#include <iostream>

#include "yanl.h"

int main() {
  auto x = yanl::ones<double>(3, 3);
  auto y = yanl::zeros<double>(3, 3);
  y(0, 0) = 1;
  y(1, 1) = 2;
  y(2, 2) = 3;

  auto z = x + y;

  std::cout << x << "\n";
  std::cout << y << "\n";
  std::cout << z << "\n";

  auto identity = yanl::eye<double>(5);
  // std::cout << identity << "\n";

  // std::cout << x * y << "\n";

  auto [lu, p] = yanl::lu_decompose(z);

  std::cout << lu << "\n";
  double det = yanl::det(z);
  std::cout << det << "\n";
}
