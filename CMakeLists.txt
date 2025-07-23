cmake_minimum_required(VERSION 3.28)
project(Tables)


add_library(libTables ./include/Tables/Table.h ./src/ColumnBase.h ./include/Tables/Column.h)
target_include_directories(libTables PUBLIC ./include ./src)
set_target_properties(libTables PROPERTIES LINKER_LANGUAGE CXX)

add_executable(tablesTest ./tests/Test.cpp)
add_executable(normalizationTest ./tests/NormalizationTest.cpp)
target_link_libraries(tablesTest libTables)
target_link_libraries(normalizationTest libTables)
