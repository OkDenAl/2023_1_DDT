set(CMAKE_PREFIX_PATH build)
project(SourcedOut_client CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.8.1 REQUIRED)
find_package(GTest REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(internal)
add_subdirectory(cmd)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-lpthread -pthread")