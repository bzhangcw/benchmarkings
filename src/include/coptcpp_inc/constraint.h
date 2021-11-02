#pragma once
#include "coptcpp.idl.h"
#include "exception.h"

// This client implemented class showing how to wrapper constraint class from copt cpp dll
class Constraint
{
public:
    Constraint(Copt::IConstraint *constr) : m_constr(constr) {}

    int GetIdx() const { return m_constr->GetIdx(); }
    const char *GetName() const { return m_constr->GetName(); }

    void SetName(const char *szName)
    {
        m_constr->SetName(szName);
        CHECKERROR(m_constr);
    }

    int GetBasis() const
    {
        int status = m_constr->GetBasis();
        CHECKERROR(m_constr);
        return status;
    }

    double Get(const char *szAttr)
    {
        double val = m_constr->Get(szAttr);
        CHECKERROR(m_constr);
        return val;
    }

    void Set(const char *szAttr, double value)
    {
        m_constr->Set(szAttr, value);
        CHECKERROR(m_constr);
    }

    void Remove() { m_constr->Remove(); }

    Copt::IConstraint *Get() const { return &(*m_constr); }

private:
    std::shared_ptr<Copt::IConstraint> m_constr;
};
