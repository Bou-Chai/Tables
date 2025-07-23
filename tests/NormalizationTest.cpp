#include <iostream>
#include <string>
#include "Tables/Table.h"
#include "Tables/Column.h"

int main() {
    tables::Table table;
    table.loadCSV("../../tests/data/winequality-red.csv", ';');
    
    std::vector<std::string> titles = {"sulphates", "quality"};
    table.toDouble(titles);
    table.normalize<double>(titles);
    table.print();

    return 0;
}