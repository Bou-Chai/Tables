cmake_minimum_required(VERSION 3.28)
project(Tables)


add_library(libTables ./include/Tables/Table.h ./src/ColumnBase.h ./include/Tables/Column.h ./include/Tables/NumericalColumn.h)
target_include_directories(libTables PUBLIC ./include ./src)
set_target_properties(libTables PROPERTIES LINKER_LANGUAGE CXX)

add_executable(tablesTest ./tests/Test.cpp)
target_link_libraries(tablesTest libTables)
