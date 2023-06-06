project(test_httpclient)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-coverage)

file(GLOB SOURCES *.cpp)

enable_testing()
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${HTTPCLIENT_lib_LIB} GTest::GTest GTest::gmock)
target_include_directories(${PROJECT_NAME} PUBLIC ${HTTPCLIENT_lib_INCLUDE_DIRS})

add_test(test_httpclient test_httpclient)