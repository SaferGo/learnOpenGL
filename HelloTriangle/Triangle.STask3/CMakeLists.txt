cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_NAME Triangle)

set(SRC_DIRECTORY src/)

set(OUTPUT_DIRECTORY ../)

project(${PROJECT_NAME})

include_directories(~/usr/local/include)

link_directories(~/usr/local/lib)

add_executable(${PROJECT_NAME} ${SRC_DIRECTORY}/main.cpp ${SRC_DIRECTORY}/glad.c)

target_link_libraries(${PROJECT_NAME} glfw3 GL X11 pthread Xrandr Xi dl)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")
