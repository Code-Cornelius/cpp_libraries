# MY FUNCTIONS


# Function that add an executable to the proejct and links the libraries.
function(add_exe_linked_to_lib EXE_NAME EXE_FILE CLASS_SET)
    # add executable to the project using the specified source files
    add_executable(${EXE_NAME} ${EXE_FILE})
    # specify that we need the  library
    #we iterate over the set
    foreach (A_LIB IN LISTS ${CLASS_SET})
        target_link_libraries(${EXE_NAME} PUBLIC ${A_LIB})
    endforeach ()
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

add_subdirectory(src) # libraries files
add_subdirectory(test) # testing the correctness of the libraries
add_subdirectory(examples_libraries) # some example of code



