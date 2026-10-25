#include <iostream>
#include <emscripten/bind.h>

auto dostuff() -> void {
	std::cout << "hi mom!!!\n";
}

EMSCRIPTEN_BINDINGS(yanl_bindings) {
    emscripten::function("dostuff", &dostuff);
}
