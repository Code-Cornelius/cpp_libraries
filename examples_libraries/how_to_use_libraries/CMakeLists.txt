#### multiple ways to import classical libraries.

#https://cmake.org/cmake/help/latest/module/FindOpenMP.html
#https://cmake.org/cmake/help/latest/module/FindLAPACK.html
#https://cmake.org/cmake/help/latest/module/FindBLAS.html


#### way 1:
#### set global, so ANY program can have OpenMP by including the file.
#FIND_PACKAGE(OpenMP REQUIRED)
#message("OPEN MP FOUND!")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")


#### way 2:
#### link one target with the library:
#FIND_PACKAGE(OpenMP REQUIRED)
#target_compile_options(test PUBLIC ${OpenMP_CXX_FLAGS})
#target_include_directories(test PUBLIC ${OpenMP_CXX_INCLUDE_DIR})
#target_link_libraries(test PUBLIC ${OpenMP_CXX_LIBRARIES})

#### way 3:
#### same as previous but more concise:
#find_package(OpenMP REQUIRED)
#target_link_libraries(test OpenMP::OpenMP_CXX)

#find_package(LAPACK REQUIRED)
#target_link_libraries(test PUBLIC ${LAPACK_LIBRARIES})
#target_link_libraries(test PUBLIC LAPACK::LAPACK)



#I also have that for private libraries ???
#add_library(foo IMPORTED)
#target_compile_options(foo INTERFACE ${OpenMP_CXX_FLAGS})
#target_include_directories(foo INTERFACE ${OpenMP_CXX_INCLUDE_DIR})
#target_link_libraries(foo INTERFACE ${OpenMP_CXX_LIBRARIES})
#target_link_libraries(main foo)



# needs BLAS!
find_package(BLAS REQUIRED)
    add_executable(blas_usage blas_usage.cpp)
    target_link_libraries(blas_usage PUBLIC ${BLAS_LIBRARIES})
if (NOT BLAS_FOUND)
    message("BLAS not found")
endif ()

# needs LAPACK!
find_package(LAPACK REQUIRED)
    add_executable(lapack_usage lapack_usage.cpp)
    target_link_libraries(lapack_usage PUBLIC ${LAPACK_LIBRARIES})
if (NOT LAPACK_FOUND)
    message("LAPACK not found")
endif ()


# needs eigen
include_directories(INCLUDE)
include_directories(${EIGEN3_INCLUDE_DIR})
add_executable(eigen_usage eigen_usage.cpp)


# needs OPENMP
FIND_PACKAGE(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    add_executable(openMP_usage openMP_usage.cpp)
    add_executable(main main.cpp)
endif ()
