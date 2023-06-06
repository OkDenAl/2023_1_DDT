cmake_minimum_required(VERSION 3.19)

project("RepositoryTests")

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES *.cpp)

if(BUILD_TYPE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0 -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif(BUILD_TYPE)


file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
message("${TEST_SOURCES}")
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${libpqxx_LIBRARIES} ${libEntities_LIB} ${libDbManager_LIB} ${GTest_LIBRARIES} ${libRepository_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC ${libRepository_INCLUDE_DIRS})

target_compile_options(${PROJECT_NAME} PUBLIC --coverage)
target_link_options(${PROJECT_NAME} PUBLIC --coverage)

gtest_discover_tests(${PROJECT_NAME})

add_custom_target(
        ${PROJECT_NAME}_TEST
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
)


add_custom_target(
        ${PROJECT_NAME}_VALGRIND
        COMMAND valgrind -s --leak-check=full --show-leak-kinds=all ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
)



