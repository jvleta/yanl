#pragma once

#include <concepts>
#include <utility>

namespace yanl::differentiation {

template <typename F>
concept DifferentiationCallable =
    std::invocable<F, double> && requires(F&& func, double x) {
      { std::forward<F>(func)(x) } -> std::convertible_to<double>;
    };

auto fp_fd(std::function<double(double)> func, double x_value, double h_value)
    -> double {
  return (func(x_value + h_value) - func(x_value)) / h_value;
}

auto fp_cd(std::function<double(double)> func, double x_value, double h_value)
    -> double {
  return (func(x_value + h_value) - func(x_value - h_value)) / (kTwo * h_value);
}

auto fp_bd(std::function<double(double)> func, double x_value, double h_value)
    -> double {
  return (func(x_value) - func(x_value - h_value)) / h_value;
}

auto fpp_121(std::function<double(double)> func, double x_value, double h_value)
    -> double {
  return (func(x_value + h_value) - (kTwo * func(x_value)) +
          func(x_value - h_value)) /
         std::pow(h_value, kTwo);
}

}  // namespace yanl::differentiation
