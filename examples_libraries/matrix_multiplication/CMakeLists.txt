# needs OPENMP
FIND_PACKAGE(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


add_executable (compar_mm_comput main.cpp
        mmNULL.cpp mm0.cpp mm1.cpp mm2.cpp
        mm3.cpp mm4.cpp mm5.cpp mm6.cpp
        mm7.cpp)
target_link_libraries (compar_mm_comput OpenMP::OpenMP_CXX)
