#include <iostream>
#include "DataTables/DataTable.h"

double DataTable::sumCol(int col) {
    if (table.empty()) {
        std::cout << "Table is empty" << "\n";
        std::exit(1);
    }

    double sum = 0;
    for (int i = 0; i < table.size(); i++) {
        if (!table[i].empty()) {
            sum += table[i][col];
        }
    }
    return sum;
}

double& DataTable::at(int row, int col) {
    return table[row][col];
}

std::vector<double>& DataTable::at(int row) {
    return table[row];
}

void DataTable::setTableMatrix(std::vector<std::vector<double>> &table) {
    this->table = table;
}

int DataTable::getHeight() {
    return table.size();
}
