cmake_minimum_required(VERSION 3.22)

project(slib VERSION 0.1)

set(CMAKE_DEBUG_POSTFIX d)

option(CMAKE_VERBOSE_MAKEFILE "" TRUE)
option(SLIB_INCLUDE_TEST "Include unit test for slib" TRUE)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

if (MSVC)
    add_compile_options(/permissive- /utf-8 /W4)
else()
    add_compile_options(-Wall -Wextra -Wshadow -Wformat=2 -Wunused)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} src/list.c)
target_include_directories(${PROJECT_NAME} INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>")

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin COMPONENT Runtime
    LIBRARY DESTINATION lib COMPONENT Runtime
    ARCHIVE DESTINATION "lib/${PROJECT_NAME}" COMPONENT Development)

install(DIRECTORY include/ DESTINATION include/)

if (${SLIB_INCLUDE_TEST})
    # GoogleTest requires at least C++14
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

    include(FetchContent)
    FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG a9b2f0495cabb1ff01b51bcd0625cb1fd82da4ce # main on 2022.10.17
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

  enable_testing()
  add_subdirectory(tests)
endif()