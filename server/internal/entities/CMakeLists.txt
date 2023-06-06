project("EntitiesLib")

set(LIB_NAME libEntities)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

message("SOURCES = ${SOURCES}")
message("HEADERS = ${HEADERS}")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g -Wall -Wextra -O2 -pedantic -Wformat=2 -Wfloat-equal -Wconversion \
-Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lboost_filesystem")


add_library(${LIB_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_link_libraries(${LIB_NAME} ${Boost_LIBRARIES} nlohmann_json::nlohmann_json)

set(libEntities_LIB ${LIB_NAME})
set(libEntities_LIB ${libEntities_LIB} PARENT_SCOPE)
set(libEntities_INCLUDE_DIRS ${LIB_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(libEntities_INCLUDE_DIRS ${libEntities_INCLUDE_DIRS} PARENT_SCOPE)

message("libEntities_LIB = ${libEntities_LIB}")
message("libEntities_INCLUDE_DIRS = ${libEntities_INCLUDE_DIRS}")

enable_testing()
add_subdirectory(tests)