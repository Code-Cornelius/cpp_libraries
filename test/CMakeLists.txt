#set( MAIN MAIN_TEST ) #setting MAIN as being MAIN_TEST
set( LIBS RDTSCP_LIB TIMER_LIB ) #setting LIBS as all my libraries.


add_exe_linked_to_lib(MAIN main.cpp LIBS)

#target_link_libraries(MAIN_TEST PUBLIC TIMER_LIB)
#target_link_libraries(${MAIN} PRIVATE RDTSCP_LIB)
