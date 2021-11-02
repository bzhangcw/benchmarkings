#pragma once
#include <cmath>
#include "coptcpp.idl.h"

class ConeBuilder
{
public:
    ConeBuilder() : m_builder(CreateConeBuilder()) {}
    ConeBuilder(Copt::IConeBuilder *pcb) : m_builder(pcb) {}

    int GetType() const { return m_builder->GetType(); }
    int GetSize() const { return m_builder->GetSize(); }
    Var GetVar(int idx) const { return m_builder->GetVar(idx); }

    void Set(const VarArray &vars, int type)
    {
        m_builder->Set(vars.Get(), type);
    }

    Copt::IConeBuilder *Get() const { return &(*m_builder); }

    friend std::ostream &operator<<(std::ostream &out, const ConeBuilder &builder)
    {
        bool beg = true;
        for (int i = 0; i < builder.GetSize(); i++)
        {
            if (builder.GetVar(i).GetIdx() < 0)
            {
                continue;
            }

            if (!beg)
            {
                out << " + ";
            }

            beg = false;
            out << builder.GetVar(i).GetName();
        }
        out << "   <SOS Type " << builder.GetType() << ">";
        return out;
    }

private:
    std::shared_ptr<Copt::IConeBuilder> m_builder;
};
