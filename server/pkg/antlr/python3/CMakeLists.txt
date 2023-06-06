cmake_minimum_required(VERSION 3.7)
project(python_antlr_lib)

file(GLOB SOURCES ./src/*.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/../virtual)


antlr_target(Python3Grammar Python3.g4
             PACKAGE antlrcpptest)

include_directories(${ANTLR_Python3Grammar_OUTPUT_DIR})


message("ANTLR_Python3Grammar_OUTPUT_DIR=${ANTLR_Python3Grammar_OUTPUT_DIR}")

include_directories(${INCLUDE_DIRS})
add_library(${PROJECT_NAME} ${SOURCES} ${ANTLR_Python3Grammar_CXX_OUTPUTS})


target_link_libraries(${PROJECT_NAME} antlr4_static Threads::Threads)

set(PYTHON3_ANTLR_LIBRARY ${PROJECT_NAME})
set(PYTHON3_ANTLR_LIBRARY ${PYTHON3_ANTLR_LIBRARY} PARENT_SCOPE)

set(PYTHON3_ANTLR_INCLUDE_DIRS ${INCLUDE_DIRS} ${ANTLR_Python3Grammar_OUTPUT_DIR})
set(PYTHON3_ANTLR_INCLUDE_DIRS ${PYTHON3_ANTLR_INCLUDE_DIRS} PARENT_SCOPE)

message("PYTHON3_ANTLR = ${PYTHON3_ANTLR_INCLUDE_DIRS} ")