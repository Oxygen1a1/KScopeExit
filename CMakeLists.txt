cmake_minimum_required(VERSION 3.10)

project(ScopeExit LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(WDK REQUIRED)

set(SOURCES main.cpp)
wdk_add_driver(ScopeExit ${SOURCES})
