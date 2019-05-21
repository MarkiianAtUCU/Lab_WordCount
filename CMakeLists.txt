cmake_minimum_required(VERSION 3.14)
project(Lab_WordCount)

set(CMAKE_CXX_STANDARD 14)


find_package(Boost REQUIRED COMPONENTS filesystem locale system)
find_package(libarchive REQUIRED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})


add_executable(Lab_WordCount_one_thread Word_count_one_thread.cpp config_reader.h FileProcessor.cpp FileProcessor.h time_meter.h)
target_link_libraries( Lab_WordCount_one_thread ${Boost_LIBRARIES} libarchive)

add_executable(Lab_WordCount_multi_thread Word_count_multi_thread.cpp config_reader.h FileProcessor.cpp FileProcessor.h time_meter.h)
target_link_libraries( Lab_WordCount_multi_thread ${Boost_LIBRARIES} libarchive)