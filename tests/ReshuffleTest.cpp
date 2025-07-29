#include <iostream>
#include <string>
#include "Tables/Table.h"
#include "Tables/Column.h"

int main() {
    tables::Table table;
    tables::Table table2;

    table.loadCSV("../../tests/data/winequality-red.csv", ';');
    table2.loadCSV("../../tests/data/winequality-red.csv", ';');

    table.reshuffle(2);
    table2.reshuffle(2);
    table.reshuffle(7);
    table2.reshuffle(7);
    
    table.print();
    table2.print();

    return 0;
}