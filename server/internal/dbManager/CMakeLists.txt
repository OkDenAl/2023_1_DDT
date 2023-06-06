project("DbManagerLib")

set(LIB_NAME libDbManager)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

message("SOURCES = ${SOURCES}")
message("HEADERS = ${HEADERS}")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g -Wall -Wextra -O2 -pedantic -Wformat=2 -Wfloat-equal -Wconversion \
-Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lboost_filesystem")


add_library(${LIB_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${LIB_NAME} ${Boost_LIBRARIES} ${PQXX_LIB})

set(libDbManager_LIB ${LIB_NAME})
set(libDbManager_LIB ${libDbManager_LIB} PARENT_SCOPE)

set(libDbManager_INCLUDE_DIRS ${LIB_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(libDbManager_INCLUDE_DIRS ${libDbManager_INCLUDE_DIRS} PARENT_SCOPE)

message("libDbManager_LIB = ${libDbManager_LIB}")
message("libDbManager_INCLUDE_DIRS = ${libDbManager_INCLUDE_DIRS}")

