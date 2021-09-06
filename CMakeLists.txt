cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main2.cpp LinkedList.h library1.h BinarySearchTree.h LinkedListImp.h library1.cpp BinarySearchTreeImp.h Image.h library2.h Image.cpp ImageTagger.cpp ImageTagger.h library2.cpp)
