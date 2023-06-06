project("GuiLib")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

set(CMAKE_PREFIX_PATH "~/Qt/6.5.0/macos/lib/cmake")
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

include_directories(${INCLUDE_DIRS} ${libClientEntities_INCLUDE_DIRS} ${CORE_lib_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${SOURCES} ${INCLUDES})
target_link_libraries(${PROJECT_NAME} ${libClientEntities_LIB} ${CORE_lib_LIB} Qt6::Widgets Qt6::Core Qt6::Gui)

set(GUI_lib_LIB ${PROJECT_NAME})
set(GUI_lib_LIB ${GUI_lib_LIB} PARENT_SCOPE)

set(GUI_lib_INCLUDE_DIRS ${INCLUDE_DIRS})
set(GUI_lib_INCLUDE_DIRS ${GUI_lib_INCLUDE_DIRS} PARENT_SCOPE)

add_executable(gui_run main.cpp)
target_link_libraries(gui_run ${GUI_lib_LIB})

enable_testing()
add_subdirectory(tests)