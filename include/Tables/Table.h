#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include "ColumnBase.h"
#include "Tables/Column.h"

namespace tables {
    class Table {
    public:
        /*
            ColumnBase& col(int col);
            void removeRow(int row);
            void removeCol(int col);
            //void setTableMatrix(std::vector<std::vector<double>> &table);
            int getHeight();
            void toInt(int col);
            void toLong(int col);
            void toFloat(int col);
            void toDouble(int col);
            void toStr(int col);
            double sumCol(int col);
            */

        template <typename T>
        Column<T>& col(int col) {
            Column<T>* columnPtr = dynamic_cast<Column<T>*>(table.at(col));
            if (columnPtr == nullptr) {
                throw std::invalid_argument("Table::col: Invalid template type used to retrieve column");
            }
            return *columnPtr;
        }   

        template <typename T>
        void removeRow(int row) {
            for (Column<T>* columnP : table) {
                columnP->remove(row);
            }
        }
        
        void addColumn(ColumnBase* column) {
            table.push_back(column);
        }

        void removeCol(int col) {
            // TODO: make sure object is deleted
            table.erase(table.begin() + col);
        }

        int getHeight() {
            return table.size();
        }

        void toInt(int col) {

        }

        void toLong(int col) {

        }

        void toFloat(int col) {

        }

        void toDouble(int col) {

        }

        void toStr(int col) {

        }

        double sumCol(int col) {

        }

        void print() {
            for (ColumnBase* column : table) {
                column->print();
            }
        }

    private:
        std::vector<ColumnBase*> table;
        std::vector<bool> numerical;
        std::unordered_map<std::string, int> columnNames;
    };
}

#endif
