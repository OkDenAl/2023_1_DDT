set(PROJECT_NAME "Server")

project(${PROJECT_NAME})

add_executable(Server main.cpp)
target_link_libraries(${PROJECT_NAME} ${HTTPSERVER_LIB} ${SERVICE_lib_LIBRARY} ${libRepository_LIB}
       ${METRICS_LIBRARY} ${libEntities_LIB} ${ANTLR4_LIB} ${libDbManager_LIB} ${PQXX_LIB})
message("a = ${SERVICE_lib_INCLUDE_DIRS}")
target_include_directories(Server PUBLIC ${Boost_INCLUDE_DIR} ${HTTPSERVER_INCLUDE_DIRS} ${SERVICE_lib_INCLUDE_DIRS} ${libRepository_INCLUDE_DIRS}
       ${libDbManager_INCLUDE_DIRS} ${METRICS_lib_INCLUDE_DIRS} ${libEntities_INCLUDE_DIRS} ${ANTLR4_LIB_INCLUDE_DIRS})

message("Built server")

