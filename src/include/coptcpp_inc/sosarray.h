#pragma once
#include "coptcpp.idl.h"
#include "sos.h"

// This client implemented class showing how to wrapper SosArray class from copt cpp dll
class SosArray
{
public:
    SosArray() : m_sosArray(CreateSosArray()) {}
    SosArray(Copt::ISosArray *ptr) : m_sosArray(ptr) {}

    void PushBack(const Sos &sos)
    {
        return m_sosArray->PushBack(sos.Get());
    }

    int Size() const { return m_sosArray->Size(); }

    Sos GetSos(int idx) const { return m_sosArray->GetSos(idx); }
    Sos operator[](int i) const { return m_sosArray->GetSos(i); }

    Copt::ISosArray *Get() const { return &(*m_sosArray); }

private:
    std::shared_ptr<Copt::ISosArray> m_sosArray;
};
