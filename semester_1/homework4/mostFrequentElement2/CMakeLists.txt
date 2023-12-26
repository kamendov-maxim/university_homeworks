cmake_minimum_required(VERSION 3.8.0)
project(mostFrequentElement VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(mostFrequentElement main.c
mostFrequentElement/mostFrequentElement.c
smartQuickSort/smartQuickSort.c
mostFrequentElement/tests/test.c
smartQuickSort/tests/test.c
readFile/readFile.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
