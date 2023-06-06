project("ClientEntitiesLib")

set(LIB_NAME libClientEntities)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g -Wall -Wextra -O2 -pedantic -Wformat=2 -Wfloat-equal -Wconversion \
-Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lboost_filesystem")

add_library(${LIB_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(libClientEntities_LIB ${LIB_NAME})
set(libClientEntities_LIB ${libClientEntities_LIB} PARENT_SCOPE)
set(libClientEntities_INCLUDE_DIRS ${LIB_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(libClientEntities_INCLUDE_DIRS ${libClientEntities_INCLUDE_DIRS} PARENT_SCOPE)