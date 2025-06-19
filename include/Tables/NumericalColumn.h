#ifndef NUMERICAL_COLUMN_H
#define NUMERICAL_COLUMN_H

#include "Tables/Column.h"

namespace tables {
    template <typename T>
    class NumericalColumn : public Column<T> {
    public:
        T sum() override {
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
    };
}

#endif
