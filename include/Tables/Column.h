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

        virtual T sum(float portion) {
            if (this->columnVector.empty()) {
                throw std::logic_error("Column::sum: Cannot sum empty table");
            }

            T sum = 0;
            for (int i = 0; i < (int)(this->columnVector.size() * portion); i++) {
                sum += this->columnVector.at(i);
            }
            return sum;
        }

        // Function to normalize column data to a range between 0 and 1
        void normalize() {
            setFields();
            for (T data : columnVector) {
                data = (data - min) / (max - min);
            }
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

        T getMin() {
            return min;
        }

        T getMax() {
            return max;
        }

        T getMean() {
            return mean;
        }

    protected:
        std::vector<T> columnVector;
        T min;
        T max;
        T mean = 0;
        bool fieldsSet;

    private:
        void setFields() {
            if (columnVector.empty()) {
                throw std::logic_error("Cannot calculate field for empty column");
            }
            
            min = columnVector[0];
            max = columnVector[0];
            if (!fieldsSet) {
                for (T data : columnVector) {
                    min = min(min, data);
                    max = max(max, data);
                    mean += data;
                }
                mean /= columnVector.size();
                fieldsSet = true;
            }
        }
    };
}

#endif
