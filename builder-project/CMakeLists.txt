cmake_minimum_required(VERSION 3.18) 

project(tech LANGUAGES CXX)

file(GLOB_RECURSE HEADERS 
     ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h
)

file(GLOB_RECURSE SOURCES 
     ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp
)

add_executable(techbin ${SOURCES} ${HEADERS}) 
target_include_directories(techbin PUBLIC Include/)
