cmake_minimum_required(VERSION 3.8.0)
project(AVLTree VERSION 1.0)

add_executable(${PROJECT_NAME}
main.c
AVLTree/AVLTree.c
String/String.c
tests/test.c
)
