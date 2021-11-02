#pragma once
#include "coptcpp.idl.h"
#include "constrbuilder.h"

class ConstrBuilderArray
{
public:
    ConstrBuilderArray() : m_builders(CreateConstrBuilderArray()) {}
    ConstrBuilderArray(Copt::IConstrBuilderArray *ptr) : m_builders(ptr) {}

    void PushBack(const ConstrBuilder &builder)
    {
        return m_builders->PushBack(builder.Get());
    }

    int Size() const { return m_builders->Size(); }
    
    void Reserve(int n) { m_builders->Reserve(n); }

    ConstrBuilder GetBuilder(int idx) const { return m_builders->GetBuilder(idx); }
    ConstrBuilder operator[](int i) const { return m_builders->GetBuilder(i); }

    Copt::IConstrBuilderArray *Get() const { return &(*m_builders); }

private:
    std::shared_ptr<Copt::IConstrBuilderArray> m_builders;
};
