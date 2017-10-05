cmake_minimum_required(VERSION 2.8)

set(project example)

project(${project})

include_directories(../application/header/)

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

set(BOOST_COMPONENTS)

list(APPEND BOOST_COMPONENTS thread
        date_time
        system
        filesystem
        chrono
        program_options
        unit_test_framework
        locale)


find_package (Boost 1.60 REQUIRED COMPONENTS ${BOOST_COMPONENTS})
include_directories (SYSTEM ${Boost_INCLUDE_DIR} ../application)

add_executable(${project} ${${project}_header} ${${project}_source})
target_link_libraries (${project} ${Boost_LIBRARIES} application)