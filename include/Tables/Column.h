#ifndef COLUMN_H
#define COLUMN_H

#include <vector>
#include <iostream>
#include "ColumnBase.h"

namespace tables {
    template <typename T>
    class Column : public ColumnBase {
    public:
        virtual ~Column() {
            std::cout << "Column destructor called" << "\n";
        }
        
        std::vector<T>& getVector() {
            return columnVector;
        }

        T& row(int row) {
            return columnVector.at(row);
        }

        void add(T data) {
            columnVector.push_back(data);
        }

        void remove(int row) {
            columnVector.erase(columnVector.begin() + row);
        }

        int size() {
            return columnVector.size();
        }

        virtual T sum() {
            if (this->columnVector.empty()) {
                std::cout << "Table is empty" << "\n";
                std::exit(1);
            }

            T sum = 0;
            for (int i = 0; i < this->columnVector.size(); i++) {
                sum += this->columnVector.at(i);
            }
            return sum;
        }

        void print() override {
            int i;
            for (i = 0; i < columnVector.size() - 1; i++) {
                std::cout << columnVector[i] << ", ";
            }
            std::cout << columnVector[i];
            std::cout << "\n";
        }

        int length() {
            return columnVector.size();
        }

    protected:
        std::vector<T> columnVector;
    };
}

#endif
