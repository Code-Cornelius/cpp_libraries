#EXECUTABLES COMPILATION
add_library(RDTSCP_LIB STATIC tacc_rdtscp.cpp)
target_include_directories(RDTSCP_LIB PUBLIC ./)
