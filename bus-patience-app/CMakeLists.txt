cmake_minimum_required(VERSION 3.18) 

project(bus-patience-app LANGUAGES CXX)

file(GLOB_RECURSE HEADERS 
     ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

file(GLOB_RECURSE SOURCES 
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(bus-patience-app ${SOURCES} ${HEADERS}) 
target_include_directories(bus-patience-app PUBLIC Include/)
