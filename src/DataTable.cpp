#include <iostream>
#include "DataTables/DataTable.h"

float DataTable::sumCol(int col) {
    if (table.empty()) {
        std::cout << "Table is empty" << "\n";
        std::exit(1);
    }

    float sum = 0;
    for (int i = 0; i < table.size(); i++) {
        if (!table[i].empty()) {
            sum += table[i][col];
        }
    }
    return sum;
}

float& DataTable::at(int row, int col) {
    return table[row][col];
}

std::vector<float>& DataTable::at(int row) {
    return table[row];
}

void DataTable::setTableMatrix(std::vector<std::vector<float>> &table) {
    this->table = table;
}

int DataTable::getHeight() {
    return table.size();
}
