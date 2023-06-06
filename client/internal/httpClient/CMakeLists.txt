project("HttpClientLib")

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/virtual)
file(GLOB INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/virtual/*.h)

include_directories(${INCLUDE_DIRS} ${Boost_INCLUDE_DIR} ${libClientEntities_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${SOURCES} ${INCLUDES})
target_link_libraries(${PROJECT_NAME} ${libClientEntities_LIB} ${Boost_LIBRARIES})

set(HTTPCLIENT_lib_LIB ${PROJECT_NAME})
set(HTTPCLIENT_lib_LIB ${HTTPCLIENT_lib_LIB} PARENT_SCOPE)

set(HTTPCLIENT_lib_INCLUDE_DIRS ${INCLUDE_DIRS})
set(HTTPCLIENT_lib_INCLUDE_DIRS ${HTTPCLIENT_lib_INCLUDE_DIRS} PARENT_SCOPE)

enable_testing()
add_subdirectory(tests)