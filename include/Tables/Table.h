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

        // Destructor
        ~Table() {
            for (ColumnBase* columnP : table) {
                delete columnP;
            }
        }

        // Function to access table element
        template <typename T>
        T& at(int col, int row) {
            return this->col<T>(col).row(row);
        }
/*
        // Function to access table column using square brackets
        template <typename T>
        Column<T>& operator[](int col) {
            return this->col<T>(col);
        }
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
        void addColumn(Column<T> column) {
            table.push_back(new Column(column));
        }

        void removeCol(int col) {
            // TODO: make sure object is deleted
            delete table[col];
            table.erase(table.begin() + col);
        }

        template <typename T>
        T sum(int col) {
            return this->col<T>(col).sum();
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
