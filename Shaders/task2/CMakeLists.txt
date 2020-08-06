cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_NAME task2)

set(SRC_DIR src/)

set(BIN_DIR ../bin/)

project(${PROJECT_NAME})

file(GLOB SRC_FILES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.c)
#the header files are linked with the cpp files

include_directories(~/usr/local/include)

link_directories(~/usr/local/lib)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} glfw3 GL X11 pthread Xrandr Xi dl)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}")
