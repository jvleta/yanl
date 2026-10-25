add_library(yanl optimization.cpp)

if(EMSCRIPTEN)
  add_executable(yanl_wasm bindings.cpp)
	target_link_libraries(yanl_wasm PRIVATE yanl)
	target_link_options(yanl_wasm PRIVATE
	  "-lembind"
    "-sMODULARIZE=1"
    "-sEXPORT_ES6=1"     
  )
  set_target_properties(yanl_wasm PROPERTIES SUFFIX ".js")
endif()
