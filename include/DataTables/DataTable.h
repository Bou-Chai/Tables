#ifndef DATATABLE_H
#define DATATABLE_H

#include <vector>
#include <string>

class DataTable {
public:
    float sumCol(int col);
    float& at(int row, int col);
    std::vector<float>& at(int row);
    void setTableMatrix(std::vector<std::vector<float>> &table);
    int getHeight();

private:
    std::vector<std::vector<float>> table;
};

#endif
