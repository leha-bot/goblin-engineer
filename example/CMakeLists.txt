cmake_minimum_required(VERSION 2.8)

set(project example)

project(${project})

#############################################################################################
#YAML
set(yaml_path ../dependency/yaml-cpp)
set_property(TARGET yaml-cpp PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${YAML_INCLUDE_DIR} )
find_package(${YAML_INCLUDE_DIR} REQUIRED PATHS ${yaml_path} )
include_directories(../dependency/yaml-cpp/include)

#############################################################################################

list(APPEND ${project}_header
        plugins/database/block.hpp
        plugins/database/database.hpp
        plugins/database/database_wrapper.hpp
        plugins/database_api/database_api.hpp
        plugins/database/handler.hpp

)

list(APPEND ${project}_source
        plugins/database/database.cpp
        plugins/database/database_wrapper.cpp
        plugins/database_api/database_api.cpp
        main.cpp

)

include_directories (
        SYSTEM
        ../goblin-engineer
)

add_executable(
        ${project}
        ${${project}_header}
        ${${project}_source}
)

target_link_libraries (
        ${project}
        yaml-cpp
        goblin-engineer
)

target_include_directories(
        ${project}
        PUBLIC
        ${YAML_INCLUDE_DIR}
)