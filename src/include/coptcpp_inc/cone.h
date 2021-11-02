#pragma once
#include "coptcpp.idl.h"

// This client implemented class showing how to wrapper Cone class from copt cpp dll
class Cone
{
public:
    Cone(Copt::ICone *cone) : m_cone(cone) {}

    int GetIdx() const { return m_cone->GetIdx(); }

    void Remove() { m_cone->Remove(); }

    Copt::ICone *Get() const { return &(*m_cone); }

private:
    std::shared_ptr<Copt::ICone> m_cone;
};
