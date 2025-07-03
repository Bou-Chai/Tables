#ifndef COLUMN_BASE_H
#define COLUMN_BASE_H

#include <vector>

namespace tables {
    class ColumnBase {
    public:
        virtual ~ColumnBase() = default;
        virtual void remove(int row) = 0; 
        virtual void print() = 0;
        virtual int length() = 0;
    };
}

#endif
