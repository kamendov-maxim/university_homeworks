cmake_minimum_required(VERSION 3.0.0)
project(task3 VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(task3 main.c
read/read.c
tests/test.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
