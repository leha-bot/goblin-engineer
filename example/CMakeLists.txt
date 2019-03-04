cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)

set(project goblin-engineer-example-dll)

set (CMAKE_PROJECT_VERSION_MAJOR 1)
set (CMAKE_PROJECT_VERSION_MINOR 0)
set (CMAKE_PROJECT_VERSION_PATCH 0)
set (CMAKE_PROJECT_VERSION "${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}.${CMAKE_PROJECT_VERSION_PATCH}")

if (CMAKE_VERSION VERSION_LESS 3.0)
    PROJECT(${project} CXX)
else()
    cmake_policy(SET CMP0048 NEW)
    PROJECT(${project} VERSION "${CMAKE_PROJECT_VERSION}" LANGUAGES CXX)
endif()


#############################################################################################
#ACTOR-ZETA

#include_directories(SYSTEM ${path_actor_zeta}/core)
#include_directories(SYSTEM ${path_actor_zeta}/io)

#ACTOR-ZETA
#############################################################################################


set(${PROJECT_NAME}_header

)

set(${PROJECT_NAME}_source
        main.cpp
)

add_executable(
        ${PROJECT_NAME}
        ${${PROJECT_NAME}_header}
        ${${PROJECT_NAME}_source}
)

add_library(
        ProgPlugin SHARED
        test_plugin.cpp
        test_plugin.hpp
)

target_link_libraries (
        ${PROJECT_NAME}
)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/header
        ${path_actor_zeta}/core
        ${path_actor_zeta}/io
)