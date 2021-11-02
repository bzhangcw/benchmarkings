#pragma once
#include "coptcpp.idl.h"

class GenConstrBuilder
{
public:
    GenConstrBuilder() : m_builder(CreateGenConstrBuilder()) {}
    GenConstrBuilder(Copt::IGenConstrBuilder *pcb) : m_builder(pcb) {}

    Var GetBinVar() const { return m_builder->GetBinVar(); }
    int GetBinVal() const { return m_builder->GetBinVal(); }

    Expr GetExpr() const { return m_builder->GetExpr(); }
    char GetSense() const { return m_builder->GetSense(); }

    void Set(const Var &var, int val, const Expr &expr, char sense)
    {
        m_builder->Set(var.Get(), val, expr.Get(), sense);
    }

    friend std::ostream &operator<<(std::ostream &out, const GenConstrBuilder &builder)
    {
        out << "(" << builder.GetBinVar().GetName();
        out << " == " << builder.GetBinVal() << ") >> ";

        char sense = builder.GetSense();
        switch (sense)
        {
            case COPT_LESS_EQUAL:
                out << "(" << builder.GetExpr() << " <= 0.0)";
                break;
            case COPT_GREATER_EQUAL:
                out << "(" << builder.GetExpr() << " >= 0.0)";
                break;
            case COPT_EQUAL:
                out << "(" << builder.GetExpr() << " == 0.0)";
                break;
            default:
                out << " UNKNOWN";
                break;
        }
        return out;
    }

    Copt::IGenConstrBuilder *Get() const { return &(*m_builder); }

private:
    std::shared_ptr<Copt::IGenConstrBuilder> m_builder;
};
