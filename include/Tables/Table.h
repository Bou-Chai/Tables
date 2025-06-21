#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <fstream>
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
            std::cout << "Table dtor:" << "\n";
            for (ColumnBase* columnP : table) {
                delete columnP;
            }
            std::cout << "End Table dtor:" << "\n";
        }

        // Function to access table element
        template <typename T>
        T& at(int col, int row) {
            return this->col<T>(col).row(row);
        }

        // Function to access table element using title
        template <typename T>
        T& at(std::string title, int row) {
            return this->col<T>(title).row(row);
        }
/*
        // Function to access table column using square brackets
        template <typename T>
        Column<T>& operator[](int col) {
            return this->col<T>(col);
        }
*/      
        // Function to access column
        template <typename T>
        Column<T>& col(int col) {
            Column<T>* columnPtr = dynamic_cast<Column<T>*>(table.at(col));
            if (columnPtr == nullptr) {
                throw std::invalid_argument("Table::col: Invalid template type used to retrieve column");
            }
            return *columnPtr;
        }

        // Function to access column using title
        template <typename T>
        Column<T>& col(std::string title) {
            try {
                Column<T>* columnPtr = dynamic_cast<Column<T>*>(columnMap.at(title));
                if (columnPtr == nullptr) {
                    throw std::invalid_argument("Table::col: Invalid template type used to retrieve column");
                }
                return *columnPtr;
            } catch (std::out_of_range) {
                throw std::out_of_range("Table::col: No column with title " + title);
            }
        }
        
        // Function to add column
        template <typename T>
        void addColumn(Column<T> column) {
            table.push_back(new Column(column));
        }

        // Function to add column with title
        template <typename T>
        void addColumn(std::string title, Column<T> column) {
            Column<T>* newColumn = new Column(column);
            table.push_back(newColumn);
            columnMap[title] = newColumn;
        }

        // Function to remove column using index
        void removeCol(int col) {
            std::unordered_map<std::string, ColumnBase*>::iterator it;
            for (it = columnMap.begin(); it != columnMap.end(); ++it) {
                if (it->second == table[col]) {
                    columnMap.erase(it);
                    break;
                }
            }
            delete table[col];
            table.erase(table.begin() + col);
        }

        // Function to remove column using title
        void removeCol(std::string title) {
            std::vector<ColumnBase*>::iterator it;
            for (it = table.begin(); it != table.end(); ++it) {
                try {
                    if (*it == columnMap.at(title)) {
                        table.erase(it);
                        break;
                    }
                } catch (std::out_of_range) {
                    throw std::out_of_range("Table::removeCol: No column with title " + title);
                }
            }
            delete columnMap.at(title);
            columnMap.erase(title);
        }

        // Funciton to return sum of column using index
        template <typename T>
        T sum(int col) {
            return this->col<T>(col).sum();
        }

        // Function to return sum of column using title
        template <typename T>
        T sum(std::string title) {
            return this->col<T>(title).sum();
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

        void loadCSV(std::string fileName) {
            /*
            std::vector<std::vector<double>>* table = new std::vector<std::vector<double>>;
            std::ifstream file(fileName);
            std::string line;



            if (file.is_open()) {
                for (int i = 0; getline(file, line); i++) {
                    table->push_back({});
                    std::string element = "";
                    for (int j = 0; j < line.size(); j++) {
                        if (std::isdigit(line[j]) || line[j] == '.') {
                            element += line[j];
                        } else if (line[j] == ',') {
                            std::cout << element << "\n";
                            table->at(i).push_back(std::stof(element));
                            element = "";
                        } else {
                            break;
                        }
                    }
                    if (element != "") {
                        table->at(i).push_back(std::stof(element));
                    }
                }
                file.close();
            } else {
                std::cout << "Failed to open file" << "\n";
            }
                */
        }

        void print() {
            for (ColumnBase* column : table) {
                column->print();
            }
        }

    private:
        std::vector<ColumnBase*> table;
        std::unordered_map<std::string, ColumnBase*> columnMap;
    };
}

#endif
