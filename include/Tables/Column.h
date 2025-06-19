#ifndef COLUMN_H
#define COLUMN_H

#include <vector>
#include <iostream>
#include "ColumnBase.h"

namespace tables {
    template <typename T>
    class Column : public ColumnBase {
    public:
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
            columnVector.erase(row);
        }

        int size() {
            return columnVector.size();
        }

        virtual T sum() {

        }

        void print() override {
            for (T data : columnVector) {
                std::cout << data << " ";
            }
            std::cout << "\n";
        } 

    protected:
        std::vector<T> columnVector;
    };
}

#endif
