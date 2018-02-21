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
#BOOST
set(BOOST_COMPONENTS)

list(APPEND BOOST_COMPONENTS
        thread
        date_time
        system
        filesystem
        chrono
        program_options
        unit_test_framework
        locale
)


find_package (Boost 1.60 REQUIRED COMPONENTS ${BOOST_COMPONENTS})
include_directories (SYSTEM ${Boost_INCLUDE_DIR})
#############################################################################################

include_directories(header)

list(APPEND ${project}_header
        header/goblin-engineer/abstract_plugin.hpp
        header/goblin-engineer/application.hpp
        header/goblin-engineer/context.hpp
        header/goblin-engineer/forward.hpp
        header/goblin-engineer/metadata.hpp
        header/goblin-engineer/plugin.hpp
        header/goblin-engineer/configuration.hp
)

list(APPEND ${project}_source
        source/application.cpp
        source/plugin.cpp
        source/context.cpp
)

add_library(
        ${project}
        ${${project}_header}
        ${${project}_source}
)

target_link_libraries (
        ${project}
        ${Boost_LIBRARIES}
        yaml-cpp
)

target_include_directories(
        ${project}
        PUBLIC
        ${YAML_INCLUDE_DIR}
)



add_subdirectory(example)