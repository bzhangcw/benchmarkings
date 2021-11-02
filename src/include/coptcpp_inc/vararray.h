#pragma once
#include "coptcpp.idl.h"
#include "var.h"

// This client implemented class showing how to wrapper ColArray class from copt cpp dll
class VarArray
{
public:
    VarArray() : m_cols(CreateVarArray()) {}
    VarArray(Copt::IVarArray *ptr) : m_cols(ptr) {}

    void PushBack(const Var &var)
    {
        return m_cols->PushBack(var.Get());
    }

    int Size() const { return m_cols->Size(); }

    void Reserve(int n) { m_cols->Reserve(n); }

    Var GetVar(int idx) const { return m_cols->GetVar(idx); }
    Var operator[](int i) const { return m_cols->GetVar(i); }

    Copt::IVarArray *Get() const { return &(*m_cols); }

private:
    std::shared_ptr<Copt::IVarArray> m_cols;
};
