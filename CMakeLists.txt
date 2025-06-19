cmake_minimum_required(VERSION 3.28)
project(Tables)

include_directories(./include ./src)
add_library(libTables ./include/Tables/Table.h ./src/ColumnBase.h ./include/Tables/Column.h ./include/Tables/NumericalColumn.h)
set_target_properties(libTables PROPERTIES LINKER_LANGUAGE CXX)
add_executable(test ./tests/Test.cpp)
target_link_libraries(test libTables)
