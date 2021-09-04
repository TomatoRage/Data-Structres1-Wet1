cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled library1.h Part1_List.cpp Part1_SearchTree.cpp main2.cpp ImageTagger.cpp library2.h)
