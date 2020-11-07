set( MAIN MAIN_TEST ) #setting MAIN as being MAIN_TEST

#EXECUTABLES COMPILATION
add_executable(MAIN_TEST main.cpp)
target_link_libraries(MAIN_TEST PUBLIC TIMER_LIB)
target_link_libraries(${MAIN} PRIVATE RDTSCP_LIB)
