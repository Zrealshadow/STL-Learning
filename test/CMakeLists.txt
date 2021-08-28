cmake_minimum_required(VERSION 3.0.0)
include_directories(../src/include)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# message(${CommonSourceCode})
enable_testing()

add_executable(
  hello_test
  hello_test.cc
)

add_executable(
    world_test
    world_test.cc
)

add_executable(
  heap_test
  heap_test.cc
)

add_executable(
  avltree_test
  avltree_test.cc
)

add_executable(
    all_test
    avltree_test.cc
    world_test.cc
    hello_test.cc
    heap_test.cc
)


target_link_libraries(
  hello_test
  gtest_main
)

target_link_libraries(
    world_test
    gtest_main
)

target_link_libraries(
  heap_test
  gtest_main
)
target_link_libraries(
    all_test
    gtest_main
)

target_link_libraries(
  avltree_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(
    hello_test
    world_test
    heap_test
    avltree_test
    all_test
)