set(CMAKE_PREFIX_PATH build)
project(SourcedOut CXX)
find_package(Boost 1.81.0 REQUIRED)
IF (APPLE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
ELSE ()
    find_package(Threads REQUIRED)
ENDIF ()

find_library(PQXX_LIB pqxx)

find_package(GTest REQUIRED)

message(STATUS ${nlohmann_json_LIBRARIES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(pkg)
add_subdirectory(internal)
add_subdirectory(cmd)

message(STATUS ${Boost_LIBRARIES})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-lpthread -pthread")

