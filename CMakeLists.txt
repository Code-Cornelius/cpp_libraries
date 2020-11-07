# MY FUNCTIONS


# Function that add an executable to the proejct and links the libraries.
function(add_exe_linked_to_lib TEST_NAME TEST_FILE CLASS_SET)
    # add executable to the project using the specified source files
    add_executable(${TEST_NAME} ${TEST_FILE})
    # specify that we need the  library
    target_link_libraries(${TEST_NAME} PUBLIC ${CLASS_SET})
endfunction()

# Function that creates a tests as an executable and adds it to the project.
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

add_subdirectory(src)
#add_subdirectory(test)
add_exe_linked_to_lib(MAIN test/main.cpp TIMER_LIB)

