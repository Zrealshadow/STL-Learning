cmake_minimum_required(VERSION 3.0.0)
project(STLTest VERSION 0.1.0)

# include(CTest)
# enable_testing()

add_compile_options(-std=c++11)
#GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)
# add_executable(STLTest main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(src)
add_subdirectory(test)
