# General
cmake_minimum_required(VERSION 3.14)
project(cvec VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Library
add_library(cvec 
  src/cvec.c
  src/iterator.c
)

target_include_directories(cvec PUBLIC include/)

# Examples 
add_executable(cvecExamples examples/demo.c)
target_link_libraries(cvecExamples PRIVATE cvec )

# Testing
enable_testing()
find_package(CMocka REQUIRED)

add_executable(cvecTests 
  test/test_lib.c 
  test/test_main.c 
)

target_link_libraries(cvecTests PRIVATE
  cmocka::cmocka
  cvec
)

target_include_directories(cvecTests PRIVATE 
  include/ 
  src/
)
add_test(NAME cvecTests COMMAND cvecTests)

# Compiled output file
set_target_properties(cvecExamples PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
