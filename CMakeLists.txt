cmake_minimum_required(VERSION 2.8.2)

set(CMAKE_BUILD_TYPE Debug)

if(${CMAKE_VERSION} VERSION_LESS 2.8.2)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(atsp_taxi
        DESCRIPTION "Asymmetric Travelling Salesman Problem"
        LANGUAGES CXX)     

set(HEADERS
    ${CMAKE_SOURCE_DIR}/include/file_handler.hpp
    ${CMAKE_SOURCE_DIR}/include/held_karp.hpp
    ${CMAKE_SOURCE_DIR}/include/timer.hpp
    ${CMAKE_SOURCE_DIR}/include/adjacency_matrix.hpp
    "${CMAKE_SOURCE_DIR}/include/path.hpp"
    ${CMAKE_SOURCE_DIR}/include/city.hpp
    ${CMAKE_SOURCE_DIR}/include/reduction_matrix.hpp
    ${CMAKE_SOURCE_DIR}/include/brute_force.hpp
    ${CMAKE_SOURCE_DIR}/include/branch_n_bound.hpp)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/held_karp.cpp
    ${CMAKE_SOURCE_DIR}/src/file_handler.cpp
    ${CMAKE_SOURCE_DIR}/src/adjacency_matrix.cpp
    "${CMAKE_SOURCE_DIR}/src/path.cpp"
    ${CMAKE_SOURCE_DIR}/src/city.cpp
    ${CMAKE_SOURCE_DIR}/src/reduction_matrix.cpp
    ${CMAKE_SOURCE_DIR}/src/brute_force.cpp
    ${CMAKE_SOURCE_DIR}/src/branch_n_bound.cpp)

if (NOT WIN32)
    find_package(CURL REQUIRED) 
    include_directories(${CURL_INCLUDE_DIR})
endif()


add_executable(atsp_taxi ${SOURCES} ${HEADERS})

if (NOT WIN32)
    target_link_libraries(atsp_taxi ${CURL_LIBRARY})
endif()

set_target_properties(atsp_taxi PROPERTIES
        CXX_STANDARD 17)