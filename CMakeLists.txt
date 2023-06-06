set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.16)


set(PROJECT_NAME "SourcedOut")

project(${PROJECT_NAME})


set(BUILD_DEV TRUE CACHE BOOL "build dev version")
set(SANITIZE_BUILD TRUE CACHE BOOL "build with sanitizers")

if(BUILD_DEV)
    enable_testing()
    message("Building dev version")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  --coverage -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g -Wall -Wextra -pedantic -Wformat=2 -Wfloat-equal -Wconversion \
        -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -lpq -lpqxx")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

    if(SANITIZE_BUILD)
        message("Sanitizers ON")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
    endif(SANITIZE_BUILD)
endif(BUILD_DEV)

set(BUILD_SERVER "BUILD_SERVER")
set(BUILD_CLIENT "BUILD_CLIENT")
set(BUILD_ALL "BUILD_ALL")


message("${BUILD_DEV} ${SANITIZE_BUILD} ${CMAKE_EXE_LINKER_FLAGS}")
set(BUILD_MODE ${BUILD_SERVER})

if((BUILD_MODE STREQUAL ${BUILD_CLIENT}) OR (BUILD_MODE STREQUAL ${BUILD_ALL}))
    add_subdirectory(client)
endif()

if((BUILD_MODE STREQUAL ${BUILD_SERVER}) OR (BUILD_MODE STREQUAL ${BUILD_ALL}))
    add_subdirectory(server)
endif()