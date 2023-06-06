project(test_httpserver)

# set(CMAKE_CXX_STANDARD 20)
# add_compile_options(-coverage)

file(GLOB SOURCES *.cpp)

enable_testing()
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

message("sdcscdscsdcsdIB=${HTTPSERVER_INCLUDE_DIRS}")

target_link_libraries(${PROJECT_NAME}  ${HTTPSERVER_LIB} GTest::GTest gmock)
target_include_directories(${PROJECT_NAME} PUBLIC ${HTTPSERVER_INCLUDE_DIRS})

add_test(test_httpserver test_httpserver)