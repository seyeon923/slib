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