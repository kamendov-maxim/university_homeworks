cmake_minimum_required(VERSION 3.8.0)
project(task2 VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(task2 main.c
queue/queue.c
tests/test.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
