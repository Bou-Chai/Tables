#include <iostream>
#include <string>
#include "Tables/Table.h"
#include "Tables/Column.h"
#include "Tables/NumericalColumn.h"

int main() {
    tables::Table table;
    tables::Column<int> col1;
    tables::NumericalColumn<float> col2;
    tables::Column<std::string> col3;
    tables::ColumnBase* col1P;
    tables::ColumnBase* col2P;

    //col1P = (tables::ColumnBase*) &col1;

    col1.add(1);
    col1.add(2);
    col2.add(3.0);
    col2.add(4.0);
    col3.add("Tim");
    col3.add("Oborn");

    table.addColumn(&col1);
    table.addColumn(&col2);
    table.addColumn(&col3);
    table.print();

    table.col<std::string>(2).row(1) = "bo";
    table.print();
    return 0;
}