#ifndef DATATABLE_H
#define DATATABLE_H

#include <vector>
#include <string>

class DataTable {
public:
    double sumCol(int col);
    double& at(int row, int col);
    std::vector<double>& at(int row);
    void setTableMatrix(std::vector<std::vector<double>> &table);
    int getHeight();

private:
    std::vector<std::vector<double>> table;
};

#endif
