# MY FUNCTIONS
function(add_exe_linked_to_lib TEST_NAME TEST_FILE CLASS_SET)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PUBLIC ${CLASS_SET})
endfunction()

function(add_test_linked_to_lib TEST_NAME TEST_FILE CLASS_SET)
    add_exe_linked_to_lib(${TEST_NAME} ${TEST_FILE} ${CLASS_SET})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

#PROJECT OPTIONS
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
#add_compile_options(-D DEBUG)

#STRUCTURE
project(my_cpp_libraries)
#include_directories(my_libs)

#EXECUTABLES COMPILATION
add_executable(MAIN_TEST ../test/main.cpp)
#add_library(RANDOM_LIB STATIC ../my_libs/Random/Random.cpp)
#target_link_libraries(MAIN PUBLIC TIMER_LIB RANDOM_LIB)




