#pragma once
#include "coptcpp.idl.h"
#include "column.h"

// This client implemented class showing how to wrapper RowArray class from copt cpp dll
class ColumnArray
{
public:
    ColumnArray() : m_cols(CreateColumnArray()) {}
    ColumnArray(Copt::IColumnArray *ptr) : m_cols(ptr) {}

    void PushBack(const Column &col)
    {
        return m_cols->PushBack(col.Get());
    }

    int Size() const { return m_cols->Size(); }

    Column GetColumn(int idx) const { return m_cols->GetColumn(idx); }
    Column operator[](int i) const { return m_cols->GetColumn(i); }

    void Reserve(int n) { m_cols->Reserve(n); }

    void Clear() { m_cols->Clear(); }

    Copt::IColumnArray *Get() const { return &(*m_cols); }

private:
    std::shared_ptr<Copt::IColumnArray> m_cols;
};
