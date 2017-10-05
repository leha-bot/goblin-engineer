cmake_minimum_required(VERSION 2.8)

set(project application)

project(${project})

include_directories(header)

list(APPEND ${project}_header
        header/application/abstract_plugin.hpp
        header/application/application.hpp
        header/application/context.hpp
        header/application/forward.hpp
        header/application/pimpl.hpp
        header/application/plugin.hpp
        header/application/rpc.hpp
)

list(APPEND ${project}_source
        source/abstract_plugin.cpp
        source/application.cpp
        source/plugin.cpp
        source/rpc.cpp
)

set(BOOST_COMPONENTS)

list(APPEND BOOST_COMPONENTS thread
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

add_library(${project} ${${project}_header} ${${project}_source})
target_link_libraries (${project} ${Boost_LIBRARIES})