cmake_minimum_required(VERSION 3.18) 

project(calculator LANGUAGES CXX)

file(GLOB_RECURSE HEADERS 
     ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

file(GLOB_RECURSE SOURCES 
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(calculator ${SOURCES} ${HEADERS}) 
target_include_directories(calculator PUBLIC Include/)
