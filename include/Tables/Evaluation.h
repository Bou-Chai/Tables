#include <cmath>
#include "Tables/Column.h"

namespace tables {
    namespace eval {
        template <typename T>
        double mae(Column<T> yActual, Column<T> yPredicted) {
            if (yActual.empty() || yPredicted.empty()) {
                throw std::logic_error("eval::mae: input columns must not be empty");
            }
            if (yActual.size() != yPredicted.size()) {
                throw std::logic_error("eval::mae: input column sizes must be the same");
            }

            T errorSum = 0;
            for (int i = 0; i < yActual.size(); i++) {
                errorSum += std::abs(yActual.row(i) - yPredicted.row(i));
            }
            return errorSum / yActual.size();
        }

        template <typename T>
        double rmse(Column<T> yActual, Column<T> yPredicted) {
            if (yActual.empty() || yPredicted.empty()) {
                throw std::logic_error("eval::rmse: input columns must not be empty");
            }
            if (yActual.size() != yPredicted.size()) {
                throw std::logic_error("eval::rmse: input column sizes must be the same");
            }

            T errorSum = 0;
            for (int i = 0; i < yActual.size(); i++) {
                errorSum += std::pow(yActual.row(i) - yPredicted.row(i), 2);
            }
            return std::sqrt(errorSum / yActual.size());
        }
    }
}