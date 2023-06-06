file(GLOB SOURCES src/*.cpp)

add_executable(metrics_test ${SOURCES})

target_link_libraries(metrics_test MetricsLib  GTest::gtest_main GTest::gmock)

add_test(metrics_test metrics_test)