cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)


set(project goblin-engineer)

project(${project} CXX)

#############################################################################################
#YAML
set(yaml_path dependency/yaml-cpp)
add_subdirectory(${yaml_path})
set_property(TARGET yaml-cpp PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${YAML_INCLUDE_DIR} )
find_package(${YAML_INCLUDE_DIR} REQUIRED PATHS ${yaml_path} )
include_directories(SYSTEM dependency/yaml-cpp/include)
#############################################################################################

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
        header/goblin-engineer/abstract_service.hpp
        header/goblin-engineer/dynamic_environment.hpp
        header/goblin-engineer/context.hpp
        header/goblin-engineer/forward.hpp
        header/goblin-engineer/metadata.hpp
        header/goblin-engineer/service.hpp
        header/goblin-engineer/configuration.hpp
        header/goblin-engineer/plugin.hpp
        header/goblin-engineer/service.hpp
)

list(APPEND ${project}_source
        source/abstract_service.cpp
        source/context.cpp
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
        yaml-cpp
        actor-zeta-core
        actor-zeta-io
)

target_include_directories(
        ${project}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/header
        dependency/yaml-cpp/include
        dependency/actor-zeta/core
        dependency/actor-zeta/io
)