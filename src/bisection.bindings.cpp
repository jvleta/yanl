#include <emscripten/bind.h>

#include <iostream>

#include "yanl.h"

auto dostuff() -> void { std::cout << "hi mom!!!\n"; }

EMSCRIPTEN_BINDINGS(yanl_bisection) {
  emscripten::function("dostuff", &dostuff);

  emscripten::class_<yanl::BisectionMethodResult>("BisectionMethodResult")
      .constructor<>()
      .property("root", &yanl::BisectionMethodResult::root)
      .property("residual", &yanl::BisectionMethodResult::residual)
      .property("numIterations", &yanl::BisectionMethodResult::num_iterations)
      .property("converged", &yanl::BisectionMethodResult::converged);

  emscripten::function(
      "bisection",
      emscripten::optional_override([](emscripten::val js_func, double a,
                                       double b, emscripten::val js_xtol) {
        std::function<double(double)> cpp_function =
            [js_func](double x) -> double { return js_func(x).as<double>(); };
        return yanl::bisection(cpp_function, a, b);
      }));
};
