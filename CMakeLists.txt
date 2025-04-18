cmake_minimum_required(VERSION 3.2.4)
project(main10 VERSION 0.1.0)

add_executable(main main.cpp)

add_subdirectory(ext)
add_subdirectory(lib)

target_link_libraries(main ${CPR_LIBRARIES})
target_link_libraries(main ncurses)
include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})
