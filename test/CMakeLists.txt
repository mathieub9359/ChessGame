set(CMAKE_AUTOMOC ON)

find_package(GTest REQUIRED)
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../googletest/include)

add_executable(TestChess ${CMAKE_CURRENT_SOURCE_DIR}/TestChess.cpp)

target_link_libraries(TestChess gtest_main GTest::GTest GTest::Main Qt6::Core Qt6::Widgets ChessGame_lib)
target_include_directories(TestChess PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_test(NAME TestChess COMMAND TestChess)
