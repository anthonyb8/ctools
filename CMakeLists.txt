# General
cmake_minimum_required(VERSION 3.14)
project(ctools VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Library
add_library(ctools
  src/vec.c
  src/list.c
  src/map.c 
  src/queue.c 
  src/stack.c  
)

target_include_directories(ctools PUBLIC include/)

# Examples
add_executable(vecExample examples/vec.c)
target_link_libraries(vecExample PRIVATE ctools )

add_executable(listExample examples/list.c)
target_link_libraries(listExample PRIVATE ctools )

add_executable(mapExample examples/map.c)
target_link_libraries(mapExample PRIVATE ctools )

add_executable(queueExample examples/queue.c)
target_link_libraries(queueExample PRIVATE ctools )

add_executable(stackExample examples/stack.c)
target_link_libraries(stackExample PRIVATE ctools )

# Testing
enable_testing()
find_package(CMocka REQUIRED)

add_executable(ctoolsTests 
  test/test_main.c 
  test/test_vec.c
  test/test_map.c
  test/test_list.c
#   # test/test_queue.c
#   # test/test_stack.c
)

target_link_libraries(ctoolsTests PRIVATE cmocka::cmocka ctools)
target_include_directories(ctoolsTests PRIVATE include/ src/)

add_test(NAME ctoolsTests COMMAND ctoolsTests)

