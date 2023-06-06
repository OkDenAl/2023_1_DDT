cmake_minimum_required(VERSION 3.7)
project(cpp_antlr_lib)

file(GLOB SOURCES ./src/*.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/../virtual)


antlr_target(CPP14GrammarLexer CPP14Lexer.g4 LEXER
             PACKAGE antlrcpptest)
antlr_target(CPP14GrammarParser CPP14Parser.g4 PARSER
             PACKAGE antlrcpptest
             DEPENDS_ANTLR CPP14GrammarLexer
             COMPILE_FLAGS -lib ${ANTLR_CPP14GrammarLexer_OUTPUT_DIR})

include_directories(${ANTLR_CPP14GrammarLexer_OUTPUT_DIR})
include_directories(${ANTLR_CPP14GrammarParser_OUTPUT_DIR})


message("ANTLR_CPP14GrammarParser_OUTPUT_DIR=${ANTLR_CPP14GrammarParser_OUTPUT_DIR}")

include_directories(${INCLUDE_DIRS})
add_library(${PROJECT_NAME} ${SOURCES} ${ANTLR_CPP14GrammarLexer_CXX_OUTPUTS} ${ANTLR_CPP14GrammarParser_CXX_OUTPUTS})


target_link_libraries(${PROJECT_NAME} antlr4_static Threads::Threads)

set(CPP_ANTLR_LIBRARY ${PROJECT_NAME})
set(CPP_ANTLR_LIBRARY ${CPP_ANTLR_LIBRARY} PARENT_SCOPE)

set(CPP_ANTLR_INCLUDE_DIRS ${INCLUDE_DIRS} ${ANTLR_CPP14GrammarLexer_OUTPUT_DIR} ${ANTLR_CPP14GrammarParser_OUTPUT_DIR})
set(CPP_ANTLR_INCLUDE_DIRS ${CPP_ANTLR_INCLUDE_DIRS} PARENT_SCOPE)

message("CPP_ANTLR = ${CPP_ANTLR_INCLUDE_DIRS} ")