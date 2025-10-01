cmake_minimum_required(VERSION 3.30)

project(state_machine)

set(CMAKE_CXX_STANDARD 20)

add_library(fsm INTERFACE)
target_include_directories(fsm INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MASTER_PROJECT TRUE)

    # We're in the root, define additional targets for developers.
    option(BUILD_FSM_TESTS "Build fsm tests" ON)
    option(BUILD_FSM_EXAMPLES "Build fsm examples" ON)

    if(BUILD_FSM_EXAMPLES)
        add_subdirectory(examples)
    endif()

    if(BUILD_TESTS)
        enable_testing()
        add_subdirectory(tests)
    endif()
endif()
