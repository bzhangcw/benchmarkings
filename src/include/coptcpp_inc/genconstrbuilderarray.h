#pragma once
#include "coptcpp.idl.h"
#include "genconstrbuilder.h"

class GenConstrBuilderArray
{
public:
    GenConstrBuilderArray() : m_builders(CreateGenConstrBuilderArray()) {}
    GenConstrBuilderArray(Copt::IGenConstrBuilderArray *ptr) : m_builders(ptr) {}

    void PushBack(const GenConstrBuilder &builder)
    {
        return m_builders->PushBack(builder.Get());
    }

    int Size() const { return m_builders->Size(); }
    GenConstrBuilder GetBuilder(int idx) const { return m_builders->GetBuilder(idx); }
    GenConstrBuilder operator[](int i) const { return m_builders->GetBuilder(i); }

    Copt::IGenConstrBuilderArray *Get() const { return &(*m_builders); }

private:
    std::shared_ptr<Copt::IGenConstrBuilderArray> m_builders;
};
