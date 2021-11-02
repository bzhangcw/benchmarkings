#pragma once
#include "coptcpp.idl.h"
#include "sosbuilder.h"

class SosBuilderArray
{
public:
    SosBuilderArray() : m_builders(CreateSosBuilderArray()) {}
    SosBuilderArray(Copt::ISosBuilderArray *ptr) : m_builders(ptr) {}

    void PushBack(const SosBuilder &builder)
    {
        return m_builders->PushBack(builder.Get());
    }

    int Size() const { return m_builders->Size(); }
    SosBuilder GetBuilder(int idx) const { return m_builders->GetBuilder(idx); }
    SosBuilder operator[](int i) const { return m_builders->GetBuilder(i); }

    Copt::ISosBuilderArray *Get() const { return &(*m_builders); }

private:
    std::shared_ptr<Copt::ISosBuilderArray> m_builders;
};
