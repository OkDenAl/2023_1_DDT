project("ServiceLib")

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/virtual)


include_directories(${INCLUDE_DIRS})
add_library(${PROJECT_NAME} ${SOURCES})

message("ANTLR4_LIB = ${ANTLR4_LIB}")
message("ANTLR4_LIB_INCLUDE_DIRS = ${ANTLR4_LIB_INCLUDE_DIRS}")

message("METRICS_lib_INCLUDE_DIRS=${METRICS_lib_INCLUDE_DIRS}")
message("METRICS_LIBRARY=${METRICS_LIBRARY}")

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS} ${libEntities_INCLUDE_DIRS} ${libRepository_INCLUDE_DIRS} ${ANTLR4_LIB_INCLUDE_DIRS} ${METRICS_lib_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${libRepository_LIB} ${libEntities_LIB} ${ANTLR4_LIB} ${METRICS_LIBRARY} ${PQXX_LIB})

set(SERVICE_lib_LIBRARY ${PROJECT_NAME})
set(SERVICE_lib_LIBRARY ${SERVICE_lib_LIBRARY} PARENT_SCOPE)

set(SERVICE_lib_INCLUDE_DIRS ${INCLUDE_DIRS})
set(SERVICE_lib_INCLUDE_DIRS ${SERVICE_lib_INCLUDE_DIRS} PARENT_SCOPE)


enable_testing()
add_subdirectory(tests)

