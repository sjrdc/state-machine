cmake_minimum_required(VERSION 3.30)

project(state_machine)

set(CMAKE_CXX_STANDARD 20)

add_library(easyfsm INTERFACE)
target_include_directories(easyfsm INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MASTER_PROJECT TRUE)

    # We're in the root, define additional targets for developers.
    option(BUILD_TESTS "Build easyfsm tests" ON)
    option(BUILD_EXAMPLES "Build easyfsm examples" ON)

    if(BUILD_EXAMPLES)
        add_subdirectory(examples)
    endif()

    if(BUILD_TESTS)
        enable_testing()
        add_subdirectory(tests)
    endif()
endif()
