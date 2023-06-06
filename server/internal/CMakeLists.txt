add_subdirectory(entities)
add_subdirectory(dbManager)
add_subdirectory(repository)
add_subdirectory(metrics)
add_subdirectory(service)
add_subdirectory(httpServer)


set(libEntities_LIB ${libEntities_LIB} PARENT_SCOPE)
set(libEntities_INCLUDE_DIRS ${libEntities_INCLUDE_DIRS} PARENT_SCOPE)

set(METRICS_LIBRARY ${METRICS_LIBRARY} PARENT_SCOPE)
set(METRICS_lib_INCLUDE_DIRS ${METRICS_lib_INCLUDE_DIRS} PARENT_SCOPE)

set(libDbManager_LIB ${libDbManager_LIB} PARENT_SCOPE)
set(libDbManager_INCLUDE_DIRS ${libDbManager_INCLUDE_DIRS} PARENT_SCOPE)

set(libRepository_LIB ${libRepository_LIB} PARENT_SCOPE)
set(libRepository_INCLUDE_DIRS ${libRepository_INCLUDE_DIRS} PARENT_SCOPE)

set(SERVICE_lib_LIBRARY ${SERVICE_lib_LIBRARY} PARENT_SCOPE)
set(SERVICE_lib_INCLUDE_DIRS ${SERVICE_lib_INCLUDE_DIRS} PARENT_SCOPE)

set(HTTPSERVER_LIB ${HTTPSERVER_LIB} PARENT_SCOPE)
set(HTTPSERVER_INCLUDE_DIRS ${HTTPSERVER_INCLUDE_DIRS} PARENT_SCOPE)

set(ALL_INCLUDE_DIRS ${HTTPSERVER_INCLUDE_DIRS}; ${SERVICE_lib_INCLUDE_DIRS}; ${libRepository_INCLUDE_DIRS};
        ${libDbManager_INCLUDE_DIRS}; ${METRICS_lib_INCLUDE_DIRS}; ${libEntities_INCLUDE_DIRS} PARENT_SCOPE)

message("b = ${SERVICE_lib_INCLUDE_DIRS}")