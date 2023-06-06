project("RepositoryLib")

set(LIB_NAME libRepository)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/virtual/*.hpp)


message("SOURCES = ${SOURCES}")
message("HEADERS = ${HEADERS}")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g -Wall -Wextra -O2 -pedantic -Wformat=2 -Wfloat-equal -Wconversion \
-Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -ftest-coverage")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lboost_filesystem")

add_custom_target(
        ${PROJECT_NAME}_COVERAGE
        COMMAND gcovr ${CMAKE_CURRENT_BINARY_DIR} -r ${CMAKE_CURRENT_SOURCE_DIR}
)
add_custom_target(
        ${PROJECT_NAME}_COVERAGE_FILE
        COMMAND rm -r ${CMAKE_CURRENT_BINARY_DIR}/report || echo "There are no reports"
        COMMAND mkdir ${CMAKE_CURRENT_BINARY_DIR}/report
        COMMAND gcovr ${CMAKE_CURRENT_BINARY_DIR} -r ${CMAKE_CURRENT_SOURCE_DIR} --html-details report/report.html
)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/virtual)
target_link_libraries(${LIB_NAME} ${Boost_LIBRARIES} ${PQXX_LIB} ${libEntities_LIB} ${libDbManager_LIB})

set(libRepository_LIB ${LIB_NAME})
set(libRepository_LIB ${libRepository_LIB} PARENT_SCOPE)

set(libRepository_INCLUDE_DIRS ${LIB_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/virtual)
set(libRepository_INCLUDE_DIRS ${libRepository_INCLUDE_DIRS} PARENT_SCOPE)


message(Entities_LIB = "${libEntities_LIB}")
message(dbManager = "${libDbManager_LIB}")
message("libRepository_LIB = ${libRepository_LIB}")
message("libRepository_INCLUDE_DIRS = ${libRepository_INCLUDE_DIRS}")

# enable_testing()
# add_subdirectory(tests)