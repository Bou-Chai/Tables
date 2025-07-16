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
    table.toDouble("bathrooms");
    table.col<double>("bathrooms").print();
    std::cout << table.sum<double>("bathrooms", 0.75) << "\n";
    table.toString<double>("bathrooms");
    table.col<std::string>("bathrooms").print();
    //std::cout << table.sum<std::string>("bathrooms") << "\n";
    return 0;
}
