#EXECUTABLES COMPILATION
add_library(TIMER_LIB STATIC timer.cpp)
target_include_directories(TIMER_LIB PUBLIC ./)
#${MAIN}