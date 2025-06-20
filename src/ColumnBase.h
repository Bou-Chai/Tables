#ifndef COLUMN_BASE_H
#define COLUMN_BASE_H

#include <vector>

namespace tables {
    class ColumnBase {
    public:
        virtual ~ColumnBase() = default;
        virtual void print() = 0;
    private:
    };
}

#endif
