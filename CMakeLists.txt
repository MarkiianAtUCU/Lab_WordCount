cmake_minimum_required(VERSION 3.14)
project(Lab_WordCount)

set(CMAKE_CXX_STANDARD 14)


find_package(Boost REQUIRED COMPONENTS filesystem locale system)
find_package(libarchive REQUIRED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

#add_executable(lab2 main2.c)
#target_link_libraries(lab2 libarchive)

add_executable(Lab_WordCount main.cpp libarchive_wrapper.cpp libarchive_wrapper.h config_reader.h)
target_link_libraries( Lab_WordCount ${Boost_LIBRARIES} libarchive)