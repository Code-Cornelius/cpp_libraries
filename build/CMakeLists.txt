# MY FUNCTIONS
function(add_exe_linked_to_lib TEST_NAME TEST_FILE CLASS_SET)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PUBLIC ${CLASS_SET})
endfunction()

function(add_test_linked_to_lib TEST_NAME TEST_FILE CLASS_SET)
    add_exe_linked_to_lib(${TEST_NAME} ${TEST_FILE} ${CLASS_SET})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()


cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

project(my_cpp_libraries)

add_executable(MAIN_TEST ../test/main.cpp)
