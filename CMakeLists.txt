cmake_minimum_required(VERSION 3.28)
project(Tables)


add_library(libTables ./include/Tables/Table.h ./src/ColumnBase.h ./include/Tables/Column.h)
target_include_directories(libTables PUBLIC ./include ./src)
set_target_properties(libTables PROPERTIES LINKER_LANGUAGE CXX)

add_executable(tablesTest ./tests/Test.cpp)
add_executable(normalizationTest ./tests/NormalizationTest.cpp)
add_executable(reshuffleTest ./tests/ReshuffleTest.cpp)
add_executable(FindMajorityTest ./tests/FindMajorityTest.cpp)
target_link_libraries(tablesTest libTables)
target_link_libraries(normalizationTest libTables)
target_link_libraries(reshuffleTest libTables)
target_link_libraries(FindMajorityTest libTables)
