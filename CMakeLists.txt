cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)


set(project goblin-engineer)

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
add_subdirectory(dependency/actor-zeta)
include_directories(SYSTEM dependency/actor-zeta/libactor_zeta_core/)
include_directories(SYSTEM dependency/actor-zeta/libactor_zeta_io)
#############################################################################################

#############################################################################################
#BOOST
set(BOOST_COMPONENTS)

list(APPEND BOOST_COMPONENTS
        thread
        date_time
        system
        filesystem
        timer
        chrono
        program_options
        unit_test_framework
        locale
)


find_package (Boost 1.67 REQUIRED COMPONENTS ${BOOST_COMPONENTS})
include_directories (SYSTEM ${Boost_INCLUDE_DIR})
#############################################################################################


include_directories(header)

list(APPEND ${project}_header

        header/goblin-engineer/abstract_plugin.hpp
        header/goblin-engineer/abstract_service.hpp
        header/goblin-engineer/configuration.hpp
        header/goblin-engineer/constructors.hpp
        header/goblin-engineer/context.hpp
        header/goblin-engineer/converters.hpp
        header/goblin-engineer/dynamic.hpp
        header/goblin-engineer/dynamic_environment.hpp
        header/goblin-engineer/forward.hpp
        header/goblin-engineer/message.hpp
        header/goblin-engineer/metadata.hpp
        header/goblin-engineer/object.hpp
        header/goblin-engineer/plugin.hpp
        header/goblin-engineer/service.hpp
)

list(APPEND ${project}_source
        source/abstract_service.cpp
        source/context.cpp
        source/dynamic.cpp
        source/dynamic_environment.cpp
        source/plugin.cpp
        source/service.cpp
)

add_library(
        ${project}
        ${${project}_header}
        ${${project}_source}
)

target_link_libraries (
        ${project} PUBLIC
        ${Boost_LIBRARIES}
        actor-zeta-core
        actor-zeta-io
)

target_include_directories(
        ${project}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/header
        dependency/actor-zeta/core
        dependency/actor-zeta/io
)