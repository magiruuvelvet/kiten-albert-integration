cmake_minimum_required(VERSION 3.14)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

project(kiten-albert CXX)
include(ProjectSetup)

add_subdirectory(libkitenpy)
