#include <iostream>
#include <string>
#include "Tables/Table.h"
#include "Tables/Column.h"
#include "Tables/NumericalColumn.h"

int main() {

    tables::Column<int> col1;
    tables::Column<std::string> col3;
    tables::Column<float> col2;
    tables::ColumnBase* col1P;
    tables::ColumnBase* col2P;
    tables::Table table;
    
    table.loadCSV("../../../../Linear-Regression/data/house-price.csv");
    table.toInt("bathrooms");
    std::cout << table.sum<int>("bathrooms");
    //table.print();
    return 0;
}
