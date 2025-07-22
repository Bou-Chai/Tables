#ifndef COLUMN_BASE_H
#define COLUMN_BASE_H

#include <vector>

namespace tables {
    class ColumnBase {
    public:
        virtual ~ColumnBase() = default;
        virtual void remove(int row) = 0;
        virtual void swap(int index1, int index2) = 0;
        virtual ColumnBase* bpCopy(int start, int n) = 0;
        virtual void print() const = 0;
        virtual int size() const = 0;
        virtual bool empty() const = 0;
    };
}

#endif
