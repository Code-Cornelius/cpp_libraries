# MY FUNCTIONS

# Function that add an executable to the project and links the libraries.
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

#GENERAL CHECKS:
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed.
    Please make a new directory (called a build directory) and run CMake from there.
    You may need to remove CMakeCache.txt.")
endif ()

message(STATUS ${CMAKE_BUILD_TYPE})
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif ()


if (CMAKE_BUILD_TYPE MATCHES DEBUG)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -O0")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg -00")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg -O0")
endif ()

if (CMAKE_BUILD_TYPE MATCHES RELEASE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O3 -march=native")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -O3 -march=native")
endif ()

#PROJECT OPTIONS
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

# MAKING SURE CPP FAILS QUICK AND HARD IF SOME REQUIREMENT ARE NOT SATISFIED
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

#STRUCTURE
project(my_cpp_libraries)

add_subdirectory(src) # libraries files
add_subdirectory(test) # testing the correctness of the libraries
add_subdirectory(examples_libraries) # some example of code


MESSAGE("INFORMATION")
MESSAGE(STATUS "Build type: " ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "Library Type: " ${LIB_TYPE})
MESSAGE(STATUS "Compiler flags:" ${CMAKE_CXX_COMPILE_FLAGS})
MESSAGE(STATUS "Compiler cxx flags:" ${CMAKE_CXX_FLAGS})
MESSAGE(STATUS "Compiler cxx debug flags:" ${CMAKE_CXX_FLAGS_DEBUG})
MESSAGE(STATUS "Compiler cxx release flags:" ${CMAKE_CXX_FLAGS_RELEASE})
MESSAGE(STATUS "Compiler cxx real size flags:" ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
MESSAGE(STATUS "Compiler cxx min size flags:" ${CMAKE_CXX_FLAGS_MINSIZEREL})

