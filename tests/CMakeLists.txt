include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
  )

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests static_string.cpp main.cpp)
target_include_directories(tests
  PRIVATE ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(tests easyfsm gtest_main)

include(GoogleTest)
gtest_discover_tests(tests
  PROPERTIES
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
  10
  )