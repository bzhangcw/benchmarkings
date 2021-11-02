#pragma once
#include <cmath>
#include "coptcpp.idl.h"
#include "constraint.h"
#include "constrarray.h"

// This client implemented class showing how to wrapper expr class from copt cpp dll
class Column
{
public:
    Column() : m_col(CreateColumn()) {}
    Column(Copt::IColumn *col) : m_col(col) {}

    size_t Size() const
    {
        return m_col->Size();
    }
    Constraint GetConstr(int i) const
    {
        return m_col->GetConstr(i);
    }
    double GetCoeff(int i) const
    {
        return m_col->GetCoeff(i);
    }

    void AddTerm(const Constraint &constr, double coeff = 1.0) { m_col->AddTerm(constr.Get(), coeff); }
    int AddTerms(const ConstrArray &constrs, double *pCoeff, int len) { return m_col->AddTerms(constrs.Get(), pCoeff, len); }
    void AddColumn(const Column &col, double mult) { m_col->AddColumn(col.Get(), mult); }

    void Remove(int idx) { m_col->Remove(idx); }

    void Remove(const Constraint &constr) { m_col->Remove(constr.Get()); }

    void Reserve(int n) { m_col->Reserve(n); }

    void Clear() { m_col->Clear(); }

    Column Clone() const { return m_col->Clone(); }

    friend std::ostream &operator<<(std::ostream &out, const Column &col)
    {
        bool beg = true;
        for (int i = 0; i < col.Size(); i++)
        {
            if (col.GetConstr(i).GetIdx() < 0 || col.GetCoeff(i) == 0.0)
            {
                continue;
            }

            if (col.GetCoeff(i) < 0.0)
            {
                out << " - ";
            }
            else if (!beg)
            {
                out << " + ";
            }

            beg = false;
            if (fabs(col.GetCoeff(i)) != 1.0)
            {
                out << fabs(col.GetCoeff(i)) << " * ";
            }
            out << col.GetConstr(i).GetName();
        }
        return out;
    }

    const Copt::IColumn *Get() const { return &(*m_col); }

private:
    std::shared_ptr<Copt::IColumn> m_col;
};
