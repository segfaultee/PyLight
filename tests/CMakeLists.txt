cmake_minimum_required(VERSION 3.10.0)

project(PyLightTests LANGUAGES CXX)

add_executable(
    ${PROJECT_NAME}
    test_objects.cc
)

target_link_libraries(${PROJECT_NAME} PyLight)