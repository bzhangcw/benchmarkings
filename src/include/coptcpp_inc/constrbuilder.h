#pragma once
#include "coptcpp.idl.h"
#include "expr.h"
#include "genconstrbuilder.h"

class ConstrBuilder
{
public:
    ConstrBuilder() : m_builder(CreateConstrBuilder()) {}
    ConstrBuilder(Copt::IConstrBuilder *pcb) : m_builder(pcb) {}

    Expr GetExpr() const { return m_builder->GetExpr(); }
    char GetSense() const { return m_builder->GetSense(); }
    double GetRange() const { return m_builder->GetRange(); }

    void Set(const Expr &expr, char sense, double rhs) { m_builder->Set(expr.Get(), sense, rhs); }
    void SetRange(const Expr &expr, double range) { m_builder->SetRange(expr.Get(), range); }

    friend GenConstrBuilder operator>>(const ConstrBuilder &left, const ConstrBuilder &right)
    {
        GenConstrBuilder builder;
        builder.Set(left.GetExpr().GetVar(0), 0 - (int)left.GetExpr().GetConstant(), right.GetExpr(), right.GetSense());

        return builder;
    }

    friend std::ostream &operator<<(std::ostream &out, const ConstrBuilder &builder)
    {
        char sense = builder.GetSense();

        if (sense == COPT_RANGE)
        {
            out << -builder.GetRange() << " <= ";
            out << builder.GetExpr() << " <= 0.0";
            return out;
        }

        switch (sense)
        {
        case COPT_LESS_EQUAL:
            out << builder.GetExpr() << " <= 0.0";
            break;
        case COPT_GREATER_EQUAL:
            out << builder.GetExpr() << " >= 0.0";
            break;
        case COPT_EQUAL:
            out << builder.GetExpr() << " == 0.0";
            break;
        case COPT_FREE:
            out << builder.GetExpr() << " FREE";
            break;
        default:
            out << " UNKNOWN";
            break;
        }
        return out;
    }

    Copt::IConstrBuilder *Get() const { return &(*m_builder); }

private:
    std::shared_ptr<Copt::IConstrBuilder> m_builder;
};
