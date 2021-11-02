#pragma once
#include "coptcpp.idl.h"

class GenConstr
{
public:
    GenConstr(Copt::IGenConstr *ptr) : m_sp(ptr) {}

    int GetIdx() const { return m_sp->GetIdx(); }

    void Remove();

    Copt::IGenConstr *Get() const { return &(*m_sp); }

private:
    std::shared_ptr<Copt::IGenConstr> m_sp;
};
