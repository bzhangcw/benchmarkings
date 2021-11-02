#pragma once
#include <cmath>
#include "coptcpp.idl.h"

class SosBuilder
{
public:
    SosBuilder() : m_builder(CreateSosBuilder()) {}
    SosBuilder(Copt::ISosBuilder *pcb) : m_builder(pcb) {}

    int GetType() const { return m_builder->GetType(); }
    int GetSize() const { return m_builder->GetSize(); }
    Var GetVar(int idx) const { return m_builder->GetVar(idx); }
    double GetWeight(int idx) const { return m_builder->GetWeight(idx); }

    void Set(const VarArray &vars, double *pWeights, int type)
    {
        m_builder->Set(vars.Get(), pWeights, type);
    }

    Copt::ISosBuilder *Get() const { return &(*m_builder); }

    friend std::ostream &operator<<(std::ostream &out, const SosBuilder &builder)
    {
        bool beg = true;
        for (int i = 0; i < builder.GetSize(); i++)
        {
            if (builder.GetVar(i).GetIdx() < 0 || builder.GetWeight(i) == 0.0)
            {
                continue;
            }

            if (builder.GetWeight(i) < 0.0)
            {
                out << " - ";
            }
            else if (!beg)
            {
                out << " + ";
            }

            beg = false;
            if (fabs(builder.GetWeight(i)) != 1.0)
            {
                out << fabs(builder.GetWeight(i)) << " * ";
            }
            out << builder.GetVar(i).GetName();
        }
        out << "   <SOS Type " << builder.GetType() << ">";
        return out;
    }

private:
    std::shared_ptr<Copt::ISosBuilder> m_builder;
};
