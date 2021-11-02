#pragma once
#include "coptcpp.idl.h"
#include "conebuilder.h"

class ConeBuilderArray
{
public:
    ConeBuilderArray() : m_builders(CreateConeBuilderArray()) {}
    ConeBuilderArray(Copt::IConeBuilderArray *ptr) : m_builders(ptr) {}

    void PushBack(const ConeBuilder &builder)
    {
        return m_builders->PushBack(builder.Get());
    }

    int Size() const { return m_builders->Size(); }
    ConeBuilder GetBuilder(int idx) const { return m_builders->GetBuilder(idx); }
    ConeBuilder operator[](int i) const { return m_builders->GetBuilder(i); }

    Copt::IConeBuilderArray *Get() const { return &(*m_builders); }

private:
    std::shared_ptr<Copt::IConeBuilderArray> m_builders;
};
