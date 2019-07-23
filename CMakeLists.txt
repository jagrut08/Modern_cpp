cmake_minimum_required(VERSION 3.13)
project(Modern_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/common)
include_directories(/Users/jdave12/boost_1_68_0/)

add_executable(Modern_cpp
        src/common/bt.h
        src/common/misc.h
        src/common/node.h
        src/common/print.h
        src/cpp/BaseDerived.cpp
        src/cpp/DeleteFromMap.cpp
        src/cpp/RVO.cpp
        src/LC/10.1.cpp
        src/LC/10.2.cpp
        src/LC/11.1.cpp
        src/LC/11.2.cpp
        src/LC/5.4.1.cpp
        src/LC/5.4.2.cpp
        src/LC/5.4.3.cpp
        src/LC/5.4.4.cpp
        src/LC/5.4.5.cpp
        src/LC/5.4.7.cpp
        src/LC/8.4.cpp
        src/LC/8.5.1.cpp
        src/LC/8.6.1.cpp
        src/LC/9.1.cpp
        src/LC/9.2.cpp
        src/LC/9.3.cpp
        src/LC/12.1.cpp
        src/LC/12.2.cpp
        src/LC/12.3.cpp src/LC/10.7.cpp)
