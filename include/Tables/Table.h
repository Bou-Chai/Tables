#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <fstream>
#include <random>
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

        // Function to add new data to column specified by index
        template <typename T>
        void add(int col, T data) {
            this->col<T>(col).add(data);
        }

        // Function to add new data to column specified by title
        template <typename T>
        void add(std::string title, T data) {
            this->col<T>(title).add(data);
        }
/*
        // Function to access table column using square brackets
        template <typename T>
        Column<T>& operator[](int col) {
            return this->col<T>(col);
        }
*/      
        // Function to access column using index
        template <typename T>
        Column<T>& col(int col) {
            try {
                Column<T>* columnPtr = dynamic_cast<Column<T>*>(table.at(col));
                if (columnPtr == nullptr) {
                    throw std::invalid_argument("Table::col: Invalid template type used to retrieve column");
                }
                return *columnPtr;
            } catch (std::out_of_range) {
                throw std::out_of_range("Table::col: Column index " + std::to_string(col) + " is out of range");
            }
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

        // Function to get a row of the table as a vector
        template <typename T>
        std::vector<T> getRow(int rowIndex) {
            std::vector<T> row;
            for(int i = 0; i < width(); i++) {
                row.push_back(at<double>(i, rowIndex));
            }
            return row;
        }

        void removeRow(int row) {
            for(int i = 0; i < table.size(); i++) {
                table[i]->remove(row);
            }
        }

        // Function to copy the table starting at columnStart copying n columns and copying n rows from row start
        Table& copy(int columnStart, int columnN, int rowStart, int rowN) {
            Table* newTable = new Table();
            std::unordered_map<std::string, ColumnBase*>::iterator it;

            for (int i = columnStart; i < columnN; i++) {
                ColumnBase* newColumn = table[i]->bpCopy(rowStart, rowN);
                // Copy over the column vector
                newTable->table.push_back(newColumn);
                // Copy over the column map
                for (it = columnMap.begin(); it != columnMap.end(); ++it) {
                    if (it->second == table[i]) {
                        newTable->columnMap[it->first] = newColumn;
                        break;
                    }
                }
            }
            return * newTable;
        }

        // Function to reshuffle table using Fisher-Yates algorithm
        void reshuffle() {
            std::random_device rd;
            std::mt19937 gen(rd());
            for (int i = 0; i < height(); i++) {
                std::uniform_int_distribution<> dist(i, height() - 1);
                int randomIndex = dist(gen);
                for (ColumnBase* column : table) {
                    column->swap(i, randomIndex);
                }
            }
        }

        // Funciton to return sum of portion of column using index
        template <typename T>
        T sum(int col, float portion) {
            return this->col<T>(col).sum(portion);
        }

        // Function to return sum of portion of column using title
        template <typename T>
        T sum(std::string title, float portion) {
            return this->col<T>(title).sum(portion);
        }

        int height() {
            return table[0]->size();;
        }

        int width() {
            return table.size();
        }

        void toInt(std::vector<int> indexList) {
            for (int col : indexList) {
                Column<int>* newColumn = new Column<int>;
                // Populate new column with integer values of the strings of the old column
                std::vector<std::string> oldColumnV = this->col<std::string>(col).getVector();
                for (std::string s : oldColumnV) {
                    newColumn->add(std::stoi(s));
                }
                // Replace old column with new column
                this->replaceCol<int>(col, newColumn);
            }
        }

        void toInt(std::vector<std::string> titleList) {
            for (std::string title : titleList) {
                Column<int>* newColumn = new Column<int>;

                // Populate new column with integer values of the strings of the old column
                std::vector<std::string> oldColumnV = this->col<std::string>(title).getVector();
                for (std::string s : oldColumnV) {
                    newColumn->add(std::stoi(s));
                }
                // Replace old column with new column
                this->replaceCol<int>(title, newColumn);
            }
        }

        void toLong(std::vector<int> indexList) {
            for (int col : indexList) {
                Column<long>* newColumn = new Column<long>;
                // Populate new column with long values of the strings of the old column
                std::vector<std::string> oldColumnV = this->col<std::string>(col).getVector();
                for (std::string s : oldColumnV) {
                    newColumn->add(std::stol(s));
                }
                // Replace old column with new column
                this->replaceCol<long>(col, newColumn);
            }
        }

        void toLong(std::vector<std::string> titleList) {
            for (std::string title : titleList) {
                Column<long>* newColumn = new Column<long>;

                // Populate new column with long values of the strings of the old column
                std::vector<std::string> oldColumnV = this->col<std::string>(title).getVector();
                for (std::string s : oldColumnV) {
                    newColumn->add(std::stol(s));
                }
                // Replace old column with new column
                this->replaceCol<long>(title, newColumn);
            }
        }

        void toFloat(std::vector<int> indexList) {
            for (int col : indexList) {
                Column<float>* newColumn = new Column<float>;
                // Populate new column with float values of the strings of the old column
                std::vector<std::string> oldColumnV = this->col<std::string>(col).getVector();
                for (std::string s : oldColumnV) {
                    newColumn->add(std::stof(s));
                }
                // Replace old column with new column
                this->replaceCol<float>(col, newColumn);
            }
        }

        void toFloat(std::vector<std::string> titleList) {
            for (std::string title : titleList) {
                Column<float>* newColumn = new Column<float>;

                // Populate new column with float values of the strings of the old column
                std::vector<std::string> oldColumnV = this->col<std::string>(title).getVector();
                for (std::string s : oldColumnV) {
                    newColumn->add(std::stof(s));
                }
                // Replace old column with new column
                this->replaceCol<float>(title, newColumn);
            }
        }

        void toDouble(std::vector<int> indexList) {
            for (int col : indexList) {
                Column<double>* newColumn = new Column<double>;
                // Populate new column with double values of the strings of the old column
                std::vector<std::string> oldColumnV = this->col<std::string>(col).getVector();
                for (std::string s : oldColumnV) {
                    newColumn->add(std::stod(s));
                }
                // Replace old column with new column
                this->replaceCol<double>(col, newColumn);
            }
        }

        void toDouble(std::vector<std::string> titleList) {
            for (std::string title : titleList) {
                Column<double>* newColumn = new Column<double>;

                // Populate new column with double values of the strings of the old column
                std::vector<std::string> oldColumnV = this->col<std::string>(title).getVector();
                for (std::string s : oldColumnV) {
                    newColumn->add(std::stod(s));
                }
                // Replace old column with new column
                this->replaceCol<double>(title, newColumn);
            }
        }

        template <typename T>
        void toString(std::vector<int> indexList) {
            for (int col : indexList) {
                Column<std::string>* newColumn = new Column<std::string>;
                // Populate new column with double values of the strings of the old column
                std::vector<T> oldColumnV = this->col<T>(col).getVector();
                for (T s : oldColumnV) {
                    newColumn->add(std::to_string(s));
                }
                // Replace old column with new column
                this->replaceCol<std::string>(col, newColumn);
            }
        }

        template <typename T>
        void toString(std::vector<std::string> titleList) {
            for (std::string title : titleList) {
                Column<std::string>* newColumn = new Column<std::string>;

                // Populate new column with double values of the strings of the old column
                std::vector<T> oldColumnV = this->col<T>(title).getVector();
                for (T s : oldColumnV) {
                    newColumn->add(std::to_string(s));
                }
                // Replace old column with new column
                this->replaceCol<std::string>(title, newColumn);
            }
        }

        void loadCSV(std::string fileName, char delimiter) {
            std::ifstream file(fileName);
            std::string line;

            if (!file.is_open()) {
                throw std::runtime_error("loadCSV: unable to open file " + fileName);
            }

            getline(file, line);
            std::string title = "";
            for (char c : line) {
                if (c == delimiter) {
                    this->addColumn<std::string>(title, Column<std::string>());
                    title = "";
                } else {
                    title += c;
                }
            }
            this->addColumn<std::string>(title, Column<std::string>());

            while (getline(file, line)) {
                int columnIndex = 0;
                std::string data = "";
                for (char c : line) {
                    if (c == delimiter) {
                        this->add<std::string>(columnIndex, data);
                        data = "";
                        columnIndex++;
                    } else {
                        data += c;
                    }
                }
                this->add<std::string>(columnIndex, data);
            }
            file.close();
        }

        void print() {
            for (int i = 0; i  < table.size(); i++) {
                std::unordered_map<std::string, ColumnBase*>::iterator it;
                for (it = columnMap.begin(); it != columnMap.end(); ++it) {
                    if (it->second == table[i]) {
                        std::cout << it->first << ": ";
                        break;
                    }
                }

                if (it == columnMap.end()) {
                    std::cout << i << ": ";
                }
                table[i]->print();
            }
        }

    private:
        std::vector<ColumnBase*> table;
        std::unordered_map<std::string, ColumnBase*> columnMap;

        // Function to replace column using index
        template <typename T>
        void replaceCol(int col, Column<T>* newColumn) {
            // Replace old column with new column in columnMap
            std::unordered_map<std::string, ColumnBase*>::iterator it;
            for (it = columnMap.begin(); it != columnMap.end(); ++it) {
                if (it->second == table[col]) {
                    it->second = newColumn;
                    break;
                }
            }

            // Delete the old column and assign new comlumn in column vector
            delete table[col];
            table[col] = newColumn;            
        }

        template <typename T>
        // Function to replace column using title
        void replaceCol(std::string title, Column<T>* newColumn) {
            // Replace old column with new column in column vector
            std::vector<ColumnBase*>::iterator it;
            for (it = table.begin(); it != table.end(); ++it) {
                if (*it == columnMap.at(title)) {
                    *it = newColumn;
                }
            }

            // Delete the old column and assign new comlumn in columnMap
            delete columnMap.at(title);
            columnMap.at(title) = newColumn;
        }
    };
}

#endif
