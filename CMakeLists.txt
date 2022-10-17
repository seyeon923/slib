cmake_minimum_required(VERSION 3.22)

project(slib VERSION 0.1)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

include_directories(${CMAKE_SOURCE_DIR})

add_library(${CMAKE_PROJECT_NAME} src/list.c)
target_include_directories(${CMAKE_PROJECT_NAME} INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>")

install(TARGETS ${CMAKE_PROJECT_NAME}
    RUNTIME DESTINATION bin COMPONENT Runtime
    LIBRARY DESTINATION lib COMPONENT Runtime
    ARCHIVE DESTINATION "lib/${CMAKE_PROJECT_NAME}" COMPONENT Development)

install(DIRECTORY include/ DESTINATION include/)

add_executable(simple_test tests/simple_test.c)
target_link_libraries(simple_test PRIVATE ${CMAKE_PROJECT_NAME})

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
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

add_subdirectory(tests)