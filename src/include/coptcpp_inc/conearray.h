#pragma once
#include "coptcpp.idl.h"
#include "cone.h"

// This client implemented class showing how to wrapper ConeArray class from copt cpp dll
class ConeArray
{
public:
    ConeArray() : m_coneArray(CreateConeArray()) {}
    ConeArray(Copt::IConeArray *ptr) : m_coneArray(ptr) {}

    void PushBack(const Cone &cone)
    {
        return m_coneArray->PushBack(cone.Get());
    }

    int Size() const { return m_coneArray->Size(); }

    Cone GetCone(int idx) const { return m_coneArray->GetCone(idx); }
    Cone operator[](int i) const { return m_coneArray->GetCone(i); }

    Copt::IConeArray *Get() const { return &(*m_coneArray); }

private:
    std::shared_ptr<Copt::IConeArray> m_coneArray;
};
