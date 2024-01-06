cmake_minimum_required(VERSION 3.10)
set(CMAKE_AUTOMOC ON)

project(ChessGame CXX)
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

file(GLOB APP_SOURCES
    src/*.cpp
)
list(REMOVE_ITEM APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_library(ChessGame_lib ${APP_SOURCES})
target_link_libraries(ChessGame_lib Qt6::Core Qt6::Widgets)

qt_add_resources(resources_RCC resources.qrc)

add_executable(${PROJECT_NAME} src/main.cpp ${resources_RCC})
target_link_libraries(${PROJECT_NAME} ChessGame_lib)

enable_testing()
add_subdirectory(test)
