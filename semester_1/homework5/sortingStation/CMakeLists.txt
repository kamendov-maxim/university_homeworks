cmake_minimum_required(VERSION 3.8.0)
project(sortingStation VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(sortingStation main.c
sortingStation/sortingStation.c
Stack/Stack.c
getString/getString.c
tests/test.c
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
