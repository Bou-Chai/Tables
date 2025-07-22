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
            //std::cout << "Column destructor called" << "\n";
        }
        
        std::vector<T>& getVector() {
            return columnVector;
        }

        T& row(int row) {
            return columnVector.at(row);
        }

        // Return a new column with column elements from index start to end - 1
        Column<T>& getRange(int start, int end) {
            checkRange(start, end, "getRange");

            Column<T>* newCol = new Column<T>();
            for (int i = start; i < end; i++) {
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

        ColumnBase* bpCopy() {
            return new Column<T>(*this);
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
            for (T data : columnVector) {
                data = (data - min) / (max - min);
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

        T getMin() {
            return min;
        }

        T getMax() {
            return max;
        }

        T getMean() {
            return mean;
        }

        T getMin(int start, int end) {
            checkRange(start, end, "getMin");

            T min;
            min = columnVector[start];
            for (int i = start; i < end; i++) {
                min = std::min(min, columnVector[i]);
            }
            return min;
        }

        T getMax(int start, int end) {
            checkRange(start, end, "getMax");

            T max;
            max = columnVector[start];
            for (int i = start; i < end; i++) {
                max = std::max(max, columnVector[i]);
            }
            return max;
        }

        T getMean(int start, int end) {
            checkRange(start, end, "getMean");

            T sum;
            sum = 0;
            for (int i = start; i < end; i++) {
                sum += columnVector[i];
            }
            return sum / (end - start);
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
                    min = min(min, data);
                    max = max(max, data);
                    mean += data;
                }
                mean /= columnVector.size();
                fieldsSet = true;
            }
        }

        void checkRange(int start, int end, std::string funcName) {
            if (!(start >= 0 && end <= this->columnVector.size() && start < end)) {
                std::string errMsg = "Column::" + funcName + ": Invalid range";
                throw std::range_error(errMsg);
            }
        }
    };
}

#endif
