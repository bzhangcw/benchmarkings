#pragma once
#include "coptcpp.idl.h"
#include "exception.h"

class Expr;
class ConstrBuilder;

// This client implemented class showing how to wrapper variable class from copt cpp dll
class Var
{
public:
    Var(Copt::IVar *var) : m_var(var) {}

    int GetIdx() const { return m_var->GetIdx(); }
    const char *GetName() const { return m_var->GetName(); }
    void SetName(const char *szName)
    {
        m_var->SetName(szName);
        CHECKERROR(m_var);
    }
    char GetType() const { return m_var->GetType(); }
    void SetType(char type)
    {
        m_var->SetType(type);
        CHECKERROR(m_var);
    }
    int GetBasis() const
    {
        int status = m_var->GetBasis();
        CHECKERROR(m_var);
        return status;
    }

    double Get(const char *szAttr)
    {
        double val = m_var->Get(szAttr);
        CHECKERROR(m_var);
        return val;
    }
    void Set(const char *szAttr, double value)
    {
        m_var->Set(szAttr, value);
        CHECKERROR(m_var);
    }

    void Remove() { m_var->Remove(); }

    Copt::IVar *Get() const { return &(*m_var); }

    // Declare operator overloadings here and refer to utils.h for actual definitions,
    // because they depend on each other.
    friend Expr operator+(const Var &var, double a);
    friend Expr operator+(double a, const Var &var);
    friend Expr operator+(const Var &left, const Var &right);
    friend Expr operator-(const Var &var, double a);
    friend Expr operator-(double a, const Var &var);
    friend Expr operator-(const Var &var);
    friend Expr operator-(const Var &left, const Var &right);
    friend Expr operator*(const Var &var, double a);
    friend Expr operator*(double a, const Var &var);

    friend ConstrBuilder operator==(const Var &left, double a);
    friend ConstrBuilder operator==(double a, const Var &left);
    friend ConstrBuilder operator==(const Var &left, const Var &right);
    friend ConstrBuilder operator>=(const Var &left, double a);
    friend ConstrBuilder operator>=(double a, const Var &left);
    friend ConstrBuilder operator>=(const Var &left, const Var &right);
    friend ConstrBuilder operator<=(const Var &left, double a);
    friend ConstrBuilder operator<=(double a, const Var &left);
    friend ConstrBuilder operator<=(const Var &left, const Var &right);

private:
    std::shared_ptr<Copt::IVar> m_var;
};
