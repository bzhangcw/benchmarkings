#pragma once
#include "coptcpp.idl.h"
#include "genconstr.h"

class GenConstrArray
{
public:
    GenConstrArray() : m_sp(CreateGenConstrArray()) {}
    GenConstrArray(Copt::IGenConstrArray *ptr) : m_sp(ptr) {}

    void PushBack(const GenConstr &constr)
    {
        m_sp->PushBack(constr.Get());
    }

    int Size() const { return m_sp->Size(); }

    GenConstr GetGenConstr(int idx) const { return m_sp->GetGenConstr(idx); }
    GenConstr operator[](int i) const { return m_sp->GetGenConstr(i); }

    Copt::IGenConstrArray *Get() const { return &(*m_sp); }

private:
    std::shared_ptr<Copt::IGenConstrArray> m_sp;
};
