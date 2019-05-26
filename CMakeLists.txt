cmake_minimum_required(VERSION 3.14)
project(Lab_WordCount)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

find_package(Boost REQUIRED COMPONENTS filesystem locale system)
find_package(LibArchive REQUIRED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})


add_executable(Lab_WordCount_one_thread src/Word_count_one_thread.cpp dependencies/config_reader.h dependencies/FileProcessor.cpp dependencies/FileProcessor.h dependencies/time_meter.h)
target_link_libraries( Lab_WordCount_one_thread ${Boost_LIBRARIES} ${LibArchive_LIBRARIES})

add_executable(Lab_WordCount_multi_thread src/Word_count_multi_thread.cpp dependencies/config_reader.h dependencies/FileProcessor.cpp dependencies/FileProcessor.h dependencies/time_meter.h)
target_link_libraries( Lab_WordCount_multi_thread ${Boost_LIBRARIES} ${LibArchive_LIBRARIES})