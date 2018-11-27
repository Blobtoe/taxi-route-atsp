cmake_minimum_required(VERSION 2.8.2)

if(${CMAKE_VERSION} VERSION_LESS 2.8.2)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(tsp
        DESCRIPTION "Asymmetric Travelling Salesman Problem"
        LANGUAGES CXX)    

include(GNUInstallDirs)

set(HEADERS
    ${CMAKE_SOURCE_DIR}/include/file_handler.hpp
    ${CMAKE_SOURCE_DIR}/include/held_karp.hpp
    ${CMAKE_SOURCE_DIR}/include/timer.hpp
    ${CMAKE_SOURCE_DIR}/include/adjacency_matrix.hpp
    "${CMAKE_SOURCE_DIR}/include/path.hpp"
    ${CMAKE_SOURCE_DIR}/include/city.hpp
    ${CMAKE_SOURCE_DIR}/include/reduction_matrix.hpp
    ${CMAKE_SOURCE_DIR}/include/brute_force.hpp
    ${CMAKE_SOURCE_DIR}/include/branch_n_bound.hpp
    ${CMAKE_SOURCE_DIR}/include/atsp.hpp)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/held_karp.cpp
    ${CMAKE_SOURCE_DIR}/src/file_handler.cpp
    ${CMAKE_SOURCE_DIR}/src/adjacency_matrix.cpp
    "${CMAKE_SOURCE_DIR}/src/path.cpp"
    ${CMAKE_SOURCE_DIR}/src/city.cpp
    ${CMAKE_SOURCE_DIR}/src/reduction_matrix.cpp
    ${CMAKE_SOURCE_DIR}/src/brute_force.cpp
    ${CMAKE_SOURCE_DIR}/src/branch_n_bound.cpp
    ${CMAKE_SOURCE_DIR}/src/atsp.cpp)

add_library(tsp SHARED ${SOURCES} ${HEADERS})

set_target_properties(tsp PROPERTIES
        CXX_STANDARD 17
        PUBLIC_HEADER include/atsp.hpp)  


if(WIN32)
    install(TARGETS tsp
        RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/build/lib/
        PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/build/lib/header/)
else()
    install(TARGETS tsp
        LIBRARY DESTINATION lib/
        PUBLIC_HEADER DESTINATION lib/header/)
endif()

target_include_directories(tsp PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(tsp PRIVATE ${CMAKE_SOURCE_DIR}/src)