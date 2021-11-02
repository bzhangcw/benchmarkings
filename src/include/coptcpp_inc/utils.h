#pragma once
#include "constrbuilder.h"
#include "expr.h"
#include "var.h"

class Utils
{
public:
    // Define operator overloadings, which depend on each other.
    friend Expr operator+(const Var &var, double a)
    {
        Expr tmp(var, 1.0);
        tmp.SetConstant(a);
        return tmp;
    }

    friend Expr operator+(double a, const Var &var)
    {
        Expr tmp(var, 1.0);
        tmp.SetConstant(a);
        return tmp;
    }

    friend Expr operator+(const Var &left, const Var &right)
    {
        Expr tmp(left, 1.0);
        tmp.AddTerm(right, 1.0);
        return tmp;
    }

    friend Expr operator-(const Var &var, double a)
    {
        Expr tmp(var, 1.0);
        tmp.SetConstant(-a);
        return tmp;
    }

    friend Expr operator-(double a, const Var &var)
    {
        Expr tmp(var, -1.0);
        tmp.SetConstant(a);
        return tmp;
    }

    friend Expr operator-(const Var &var)
    {
        return 0.0 - var;
    }

    friend Expr operator-(const Var &left, const Var &right)
    {
        Expr tmp(left, 1.0);
        tmp.AddTerm(right, -1.0);
        return tmp;
    }

    friend Expr operator*(double a, const Var &var)
    {
        return Expr(var, a);
    }

    friend Expr operator*(const Var &var, double a)
    {
        return Expr(var, a);
    }

    friend ConstrBuilder operator==(double a, const Var &right)
    {
        ConstrBuilder builder;
        builder.Set(right, COPT_EQUAL, a);
        return builder;
    }

    friend ConstrBuilder operator==(const Var &left, double a)
    {
        ConstrBuilder builder;
        builder.Set(left, COPT_EQUAL, a);
        return builder;
    }

    friend ConstrBuilder operator==(const Var &left, const Var &right)
    {
        ConstrBuilder builder;
        builder.Set(left - right, COPT_EQUAL, 0.0);
        return builder;
    }

    friend ConstrBuilder operator>=(double a, const Var &right)
    {
        ConstrBuilder builder;
        builder.Set(right, COPT_LESS_EQUAL, a);
        return builder;
    }

    friend ConstrBuilder operator>=(const Var &left, double a)
    {
        ConstrBuilder builder;
        builder.Set(left, COPT_GREATER_EQUAL, a);
        return builder;
    }

    friend ConstrBuilder operator>=(const Var &left, const Var &right)
    {
        ConstrBuilder builder;
        builder.Set(left - right, COPT_GREATER_EQUAL, 0.0);
        return builder;
    }

    friend ConstrBuilder operator<=(double a, const Var &right)
    {
        ConstrBuilder builder;
        builder.Set(right, COPT_GREATER_EQUAL, a);
        return builder;
    }

    friend ConstrBuilder operator<=(const Var &left, double a)
    {
        ConstrBuilder builder;
        builder.Set(left, COPT_LESS_EQUAL, a);
        return builder;
    }

    friend ConstrBuilder operator<=(const Var &left, const Var &right)
    {
        ConstrBuilder builder;
        builder.Set(left - right, COPT_LESS_EQUAL, 0.0);
        return builder;
    }

    friend ConstrBuilder operator>=(const Expr &left, double a)
    {
        ConstrBuilder builder;
        builder.Set(left, COPT_GREATER_EQUAL, a);
        return builder;
    }

    friend ConstrBuilder operator>=(double a, const Expr &right)
    {
        ConstrBuilder builder;
        builder.Set(right, COPT_LESS_EQUAL, a);
        return builder;
    }

    friend ConstrBuilder operator>=(const Expr &left, const Var &var)
    {
        ConstrBuilder builder;
        builder.Set(left - var, COPT_GREATER_EQUAL, 0.0);
        return builder;
    }

    friend ConstrBuilder operator>=(const Var &var, const Expr &right)
    {
        ConstrBuilder builder;
        builder.Set(right - var, COPT_LESS_EQUAL, 0.0);
        return builder;
    }

    friend ConstrBuilder operator>=(const Expr &left, const Expr &right)
    {
        ConstrBuilder builder;
        builder.Set(left - right, COPT_GREATER_EQUAL, 0.0);
        return builder;
    }

    friend ConstrBuilder operator<=(const Expr &left, double a)
    {
        ConstrBuilder builder;
        builder.Set(left, COPT_LESS_EQUAL, a);
        return builder;
    }

    friend ConstrBuilder operator<=(double a, const Expr &right)
    {
        ConstrBuilder builder;
        builder.Set(right, COPT_GREATER_EQUAL, a);
        return builder;
    }

    friend ConstrBuilder operator<=(const Expr &left, const Var &var)
    {
        ConstrBuilder builder;
        builder.Set(left - var, COPT_LESS_EQUAL, 0.0);
        return builder;
    }

    friend ConstrBuilder operator<=(const Var &var, const Expr &right)
    {
        ConstrBuilder builder;
        builder.Set(right - var, COPT_GREATER_EQUAL, 0.0);
        return builder;
    }

    friend ConstrBuilder operator<=(const Expr &left, const Expr &right)
    {
        ConstrBuilder builder;
        builder.Set(left - right, COPT_LESS_EQUAL, 0.0);
        return builder;
    }

    friend ConstrBuilder operator==(const Expr &left, double a)
    {
        ConstrBuilder builder;
        builder.Set(left, COPT_EQUAL, a);
        return builder;
    }

    friend ConstrBuilder operator==(double a, const Expr &right)
    {
        ConstrBuilder builder;
        builder.Set(right, COPT_EQUAL, a);
        return builder;
    }

    friend ConstrBuilder operator==(const Expr &left, const Var &var)
    {
        ConstrBuilder builder;
        builder.Set(left - var, COPT_EQUAL, 0.0);
        return builder;
    }

    friend ConstrBuilder operator==(const Var &var, const Expr &right)
    {
        ConstrBuilder builder;
        builder.Set(right - var, COPT_EQUAL, 0.0);
        return builder;
    }

    friend ConstrBuilder operator==(const Expr &left, const Expr &right)
    {
        ConstrBuilder builder;
        builder.Set(left - right, COPT_EQUAL, 0.0);
        return builder;
    }
};
