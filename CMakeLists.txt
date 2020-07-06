cmake_minimum_required(VERSION 3.13)

project(head-clicker C)

subdirs(raylib)

include_directories(raylib/src raygui/src)

add_executable(head-clicker main.c drw.h drw.c)
target_link_libraries(head-clicker raylib)
