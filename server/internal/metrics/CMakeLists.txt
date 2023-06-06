project("MetricsLib")

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)


include_directories(${INCLUDE_DIRS})
add_library(${PROJECT_NAME} ${SOURCES})

message("ANTLR4_LIB = ${ANTLR4_LIB}")
message("ANTLR4_LIB_INCLUDE_DIRS = ${ANTLR4_LIB_INCLUDE_DIRS}")

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


set(METRICS_LIBRARY ${PROJECT_NAME})
set(METRICS_LIBRARY ${METRICS_LIBRARY} PARENT_SCOPE)


set(METRICS_lib_INCLUDE_DIRS ${INCLUDE_DIRS})
set(METRICS_lib_INCLUDE_DIRS ${METRICS_lib_INCLUDE_DIRS} PARENT_SCOPE)


enable_testing()
#if(BUILD_TESTS)
add_subdirectory(tests)
#endif()