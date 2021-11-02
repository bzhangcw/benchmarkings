#pragma once
#include "coptcpp.idl.h"

// This client implemented class showing how to wrapper Sos class from copt cpp dll
class Sos
{
public:
    Sos(Copt::ISos *sos) : m_sos(sos) {}

    int GetIdx() const { return m_sos->GetIdx(); }

    void Remove() { m_sos->Remove(); }

    Copt::ISos *Get() const { return &(*m_sos); }

private:
    std::shared_ptr<Copt::ISos> m_sos;
};
