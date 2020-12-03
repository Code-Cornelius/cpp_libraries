# needs BLAS!
find_package(BLAS)
    add_executable(blas_usage blas_usage.cpp)
    target_link_libraries(blas_usage PUBLIC ${BLAS_LIBRARIES})
if (BLAS_FOUND)
    message("BLAS not found")
endif ()

# needs LAPACK!
find_package(LAPACK)
    add_executable(lapack_usage lapack_usage.cpp)
    target_link_libraries(lapack_usage PUBLIC ${LAPACK_LIBRARIES})
if (LAPACK_FOUND)

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
