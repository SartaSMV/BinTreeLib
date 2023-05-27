cmake_minimum_required(VERSION 3.5 FATAL_ERROR)


set(TESTS_MAIN
	main.cpp
)
add_executable(Test ${TESTS_MAIN})

include_directories(../binTreeLib/binTreeLib)
target_link_libraries(Test binTreeLib)