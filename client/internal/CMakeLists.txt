add_subdirectory(entities)
add_subdirectory(httpClient)
add_subdirectory(core)
add_subdirectory(gui)

set(libClientEntities_LIB ${libClientEntities_LIB} PARENT_SCOPE)
set(libClientEntities_INCLUDE_DIRS ${libClientEntities_INCLUDE_DIRS} PARENT_SCOPE)

set(HTTPCLIENT_lib_LIB ${HTTPCLIENT_lib_LIB} PARENT_SCOPE)
set(HTTPCLIENT_lib_INCLUDE_DIRS ${HTTPCLIENT_lib_INCLUDE_DIRS} PARENT_SCOPE)

set(CORE_lib_LIB ${CORE_lib_LIB} PARENT_SCOPE)
set(CORE_lib_INCLUDE_DIRS ${CORE_lib_INCLUDE_DIRS} PARENT_SCOPE)

set(GUI_lib_LIB ${GUI_lib_LIB} PARENT_SCOPE)
set(GUI_lib_INCLUDE_DIRS ${GUI_lib_INCLUDE_DIRS} PARENT_SCOPE)