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

        // Return a new column with column elements from index start to n - 1
        Column<T>& getRange(int start, int n) {
            checkRange(start, n, "getRange");

            Column<T>* newCol = new Column<T>();
            for (int i = start; i < n; i++) {
                newCol->add(this->columnVector.at(i));
            }   
            return *newCol;
        }

        void add(T data) {
            columnVector.push_back(data);
        }

        void remove(int row) {
            columnVector.erase(columnVector.begin() + row);
        }

        void swap(int index1, int index2) {
            T temp;
            temp = columnVector.at(index1);
            columnVector.at(index1) = columnVector.at(index2);
            columnVector.at(index2) = temp;
        }

        ColumnBase* bpCopy(int start, int n) {
            checkRange(start, n, "bpCopy");
            return &(getRange(start, n));
        }

        int size() const {
            return columnVector.size();
        }

        bool empty() const {
            return columnVector.empty();
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
            for (int i = 0; i < columnVector.size(); i++) {
                columnVector[i] = (columnVector[i] - min) / (max - min);
            }
        }

        void print() const override {
            int i;
            for (i = 0; i < columnVector.size() - 1; i++) {
                std::cout << columnVector[i] << ", ";
            }
            std::cout << columnVector[i];
            std::cout << "\n";
        }

        T findMajority() {
            T majorityElement = columnVector[0];
            int count = 0;

            for (T element : columnVector) {
                if (count == 0) {
                    majorityElement = element;
                    count++;
                } else if (element == majorityElement) {
                    count++;
                } else {
                    count--;
                }
            }
            return majorityElement;
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

        T getMin(int start, int n) {
            checkRange(start, n, "getMin");

            T min;
            min = columnVector[start];
            for (int i = start; i < n; i++) {
                min = std::min(min, columnVector[i]);
            }
            return min;
        }

        T getMax(int start, int n) {
            checkRange(start, n, "getMax");

            T max;
            max = columnVector[start];
            for (int i = start; i < n; i++) {
                max = std::max(max, columnVector[i]);
            }
            return max;
        }

        T getMean(int start, int n) {
            checkRange(start, n, "getMean");

            T sum;
            sum = 0;
            for (int i = start; i < n; i++) {
                sum += columnVector[i];
            }
            return sum / (n - start);
        }

    protected:
        std::vector<T> columnVector;
        T min;
        T max;
        T mean;
        bool fieldsSet;

    private:
        void setFields() {
            if (columnVector.empty()) {
                throw std::logic_error("Cannot calculate field for empty column");
            }
            
            mean = 0;
            min = columnVector[0];
            max = columnVector[0];
            if (!fieldsSet) {
                for (T data : columnVector) {
                    min = std::min(min, data);
                    max = std::max(max, data);
                    mean += data;
                }
                mean /= columnVector.size();
                fieldsSet = true;
            }
        }

        void checkRange(int start, int n, std::string funcName) {
            if (!(start >= 0 && n <= this->columnVector.size() && start < n)) {
                std::string errMsg = "Column::" + funcName + ": Invalid range";
                throw std::range_error(errMsg);
            }
        }
    };
}

#endif
