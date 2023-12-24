cmake_minimum_required(VERSION 3.8.0)
project(parseTree VERSION 0.1.0 LANGUAGES C)

add_executable(parseTree main.c
parseTree/parseTree.c
String/String.c
tests/test.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
