cmake_minimum_required(VERSION 3.10.0)

project(PyLight LANGUAGES CXX)

option(EXPOSE_PYTHON "Make Python a public dependency of this project" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(Python3 COMPONENTS Interpreter Development.Module REQUIRED)

add_library(
    ${PROJECT_NAME}

    ${SRC_DIR}/module/module.cc
    
    ${SRC_DIR}/wrapped_types/py_dict.cc
    ${SRC_DIR}/wrapped_types/py_list.cc

    ${SRC_DIR}/python.cc
)

target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})

if(EXPOSE_PYTHON)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${Python3_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PUBLIC ${Python3_INCLUDE_DIRS})
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${Python3_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${Python3_INCLUDE_DIRS})
endif()