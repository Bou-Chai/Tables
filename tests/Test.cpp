#include <iostream>
#include <string>
#include "Tables/Table.h"
#include "Tables/Column.h"

int main() {

    tables::Column<int> col1;
    tables::Column<std::string> col3;
    tables::Column<float> col2;
    tables::ColumnBase* col1P;
    tables::ColumnBase* col2P;
    tables::Table table;
    
    table.loadCSV("../../tests/data/winequality-red.csv", ';');
    std::vector<std::string> row = table.getRow<std::string>(0, 0, 11);
    for (std::string element : row) {
        std::cout << element << "\n";
    }
    /*
    int trainSize = (int) (0.6 * table.height());
    tables::Table table2 = table.copy(0, 3, 0, trainSize);
    tables::Table table3 = table.copy(0, 3, trainSize, table.height());
    table2.print();
    table3.print();
    */
    
    return 0;
}
