#pragma once
#include "coptcpp.idl.h"
#include "constraint.h"

// This client implemented class showing how to wrapper RowArray class from copt cpp dll
class ConstrArray
{
public:
    ConstrArray() : m_rows(CreateConstrArray()) {}
    ConstrArray(Copt::IConstrArray *ptr) : m_rows(ptr) {}

    void PushBack(const Constraint &constr)
    {
        return m_rows->PushBack(constr.Get());
    }

    int Size() const { return m_rows->Size(); }

    void Reserve(int n) { m_rows->Reserve(n); }

    Constraint GetConstr(int idx) const { return m_rows->GetConstr(idx); }
    Constraint operator[](int i) const { return m_rows->GetConstr(i); }

    Copt::IConstrArray *Get() const { return &(*m_rows); }

private:
    std::shared_ptr<Copt::IConstrArray> m_rows;
};
