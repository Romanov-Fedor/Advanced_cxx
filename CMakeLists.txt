cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)
project(cxx_hw)

file(GLOB TASKS LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/task_*")

message(${TASKS})

foreach(TASK ${TASKS})
    get_filename_component(TASK_NAME ${TASK} NAME)

    file(GLOB_RECURSE TASK_SOURCES
        ${TASK}/*.hpp
        ${TASK}/*.cpp
    )

    add_executable(${TASK_NAME} ${TASK_SOURCES})
endforeach()