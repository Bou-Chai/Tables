#include <iostream>
#include <string>
#include "Tables/Table.h"
#include "Tables/Column.h"

int main() {
    tables::Table table;
    tables::Column<int> col;
    col.add(1);
    col.add(0);
    col.add(0);

    table.addColumn<int>(col);
    int majorityElement = table.col<int>(0).findMajority();

    std::cout << majorityElement << "\n";

    return 0;
}