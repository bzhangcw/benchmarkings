#pragma once
#include "coptcpp.idl.h"
#include "var.h"
#include "column.h"
#include "columnarray.h"
#include "expr.h"
#include "exception.h"
#include "constraint.h"
#include "vararray.h"
#include "constrarray.h"
#include "constrbuilderarray.h"
#include "probbuffer.h"
#include "sosarray.h"
#include "sosbuilderarray.h"
#include "genconstrarray.h"
#include "genconstrbuilderarray.h"
#include "conearray.h"
#include "conebuilderarray.h"

// This client implemented class showing how to wrapper model class from copt cpp dll
class Model
{
public:
    Model(Copt::IEnvr *env, const char *szName)
        : m_model(CreateModel(env, szName))
    {
        CHECKERROR(m_model);
    }
    Model(Copt::IModel *model) : m_model(model) {}

    void Read(const char *szFileName)
    {
        m_model->Read(szFileName);
        CHECKERROR(m_model);
    }

    void ReadMps(const char *szFileName)
    {
        m_model->ReadMps(szFileName);
        CHECKERROR(m_model);
    }

    void ReadLp(const char *szFileName)
    {
        m_model->ReadLp(szFileName);
        CHECKERROR(m_model);
    }

    void ReadBin(const char *szFileName)
    {
        m_model->ReadBin(szFileName);
        CHECKERROR(m_model);
    }

    void ReadSol(const char *szFileName)
    {
        m_model->ReadSol(szFileName);
        CHECKERROR(m_model);
    }

    void ReadBasis(const char *szFileName)
    {
        m_model->ReadBasis(szFileName);
        CHECKERROR(m_model);
    }

    void ReadMst(const char *szFileName)
    {
        m_model->ReadMst(szFileName);
        CHECKERROR(m_model);
    }

    void ReadParam(const char *szFileName)
    {
        m_model->ReadParam(szFileName);
        CHECKERROR(m_model);
    }

    void GetParamInfo(const char *szParam, int *pnCur, int *pnDef, int *pnMin, int *pnMax)
    {
        m_model->GetParamInfo(szParam, pnCur, pnDef, pnMin, pnMax);
        CHECKERROR(m_model);
    }

    void GetParamInfo(const char *szParam, double *pdCur, double *pdDef, double *pdMin, double *pdMax)
    {
        m_model->GetParamInfo(szParam, pdCur, pdDef, pdMin, pdMax);
        CHECKERROR(m_model);
    }

    int GetIntParam(const char *szParam)
    {
        int val = m_model->GetIntParam(szParam);
        CHECKERROR(m_model);
        return val;
    }

    double GetDblParam(const char *szParam)
    {
        double val = m_model->GetDblParam(szParam);
        CHECKERROR(m_model);
        return val;
    }

    void SetIntParam(const char *szParam, int nVal)
    {
        m_model->SetIntParam(szParam, nVal);
        CHECKERROR(m_model);
    }

    void SetDblParam(const char *szParam, double dVal)
    {
        m_model->SetDblParam(szParam, dVal);
        CHECKERROR(m_model);
    }

    void Write(const char *szFileName)
    {
        m_model->Write(szFileName);
        CHECKERROR(m_model);
    }

    void WriteMps(const char *szFileName)
    {
        m_model->WriteMps(szFileName);
        CHECKERROR(m_model);
    }

    ProbBuffer WriteMpsStr()
    {
        ProbBuffer buffer = m_model->WriteMpsStr();
        CHECKERROR(m_model);
        return buffer;
    }

    void WriteLp(const char *szFileName)
    {
        m_model->WriteLp(szFileName);
        CHECKERROR(m_model);
    }

    void WriteBin(const char *szFileName)
    {
        m_model->WriteBin(szFileName);
        CHECKERROR(m_model);
    }

    void WriteSol(const char *szFileName)
    {
        m_model->WriteSol(szFileName);
        CHECKERROR(m_model);
    }

    void WriteBasis(const char *szFileName)
    {
        m_model->WriteBasis(szFileName);
        CHECKERROR(m_model);
    }

    void WriteMst(const char *szFileName)
    {
        m_model->WriteMst(szFileName);
        CHECKERROR(m_model);
    }

    void WriteParam(const char *szFileName)
    {
        m_model->WriteParam(szFileName);
        CHECKERROR(m_model);
    }

    int GetIntAttr(const char *szAttr)
    {
        int val = m_model->GetIntAttr(szAttr);
        CHECKERROR(m_model);
        return val;
    }

    double GetDblAttr(const char *szAttr)
    {
        double val = m_model->GetDblAttr(szAttr);
        CHECKERROR(m_model);
        return val;
    }

    Var AddVar(double lb, double ub, double obj, char vtype, const char *szName = nullptr)
    {
        Var var = m_model->AddVar(lb, ub, obj, vtype, szName);
        CHECKERROR(m_model);
        return var;
    }

    Var AddVar(double lb, double ub, double obj, char vtype, const Column &col, const char *szName = nullptr)
    {
        Var var = m_model->AddVar(lb, ub, obj, vtype, col.Get(), szName);
        CHECKERROR(m_model);
        return var;
    }

    VarArray AddVars(int count, char type, const char *szPrefix = "C")
    {
        VarArray vars = m_model->AddVars(count, type, szPrefix);
        CHECKERROR(m_model);
        return vars;
    }

    VarArray AddVars(int count, double lb, double ub, double obj, char vtype, const char *szPrefix = "C")
    {
        VarArray vars = m_model->AddVars(count, lb, ub, obj, vtype, szPrefix);
        CHECKERROR(m_model);
        return vars;
    }

    VarArray AddVars(int count, double *plb, double *pub, double *pobj, char *pvtype, const char *szPrefix = "C")
    {
        VarArray vars = m_model->AddVars(count, plb, pub, pobj, pvtype, szPrefix);
        CHECKERROR(m_model);
        return vars;
    }

    VarArray AddVars(int count, double *plb, double *pub, double *pobj, char *pvtype,
                     const ColumnArray &cols, const char *szPrefix = "C")
    {
        VarArray vars = m_model->AddVars(count, plb, pub, pobj, pvtype, cols.Get(), szPrefix);
        CHECKERROR(m_model);
        return vars;
    }

    Constraint AddConstr(const Expr &expr, char sense, double rhs, const char *szName = nullptr)
    {
        Constraint constr = m_model->AddConstr(expr.Get(), sense, rhs, szName);
        CHECKERROR(m_model);
        return constr;
    }

    Constraint AddConstr(const Expr &lhs, char sense, const Expr &rhs, const char *szName = nullptr)
    {
        Constraint constr = m_model->AddConstr(lhs.Get(), sense, rhs.Get(), szName);
        CHECKERROR(m_model);
        return constr;
    }

    Constraint AddConstr(const Expr &expr, double lb, double ub, const char *szName = nullptr)
    {
        Constraint constr = m_model->AddConstr(expr.Get(), lb, ub, szName);
        CHECKERROR(m_model);
        return constr;
    }

    Constraint AddConstr(const ConstrBuilder &builder, const char *szName = nullptr)
    {
        Constraint constr = m_model->AddConstr(builder.Get(), szName);
        CHECKERROR(m_model);
        return constr;
    }

    ConstrArray AddConstrs(int count, char *pSense, double *pRhs, const char *szPrefix = "R")
    {
        ConstrArray constrs = m_model->AddConstrs(count, pSense, pRhs, szPrefix);
        CHECKERROR(m_model);
        return constrs;
    }

    ConstrArray AddConstrs(int count, double *pLower, double *pUpper, const char *szPrefix = "R")
    {
        ConstrArray constrs = m_model->AddConstrs(count, pLower, pUpper, szPrefix);
        CHECKERROR(m_model);
        return constrs;
    }

    ConstrArray AddConstrs(const ConstrBuilderArray &builders, const char *szPrefix = "R")
    {
        ConstrArray constrs = m_model->AddConstrs(builders.Get(), szPrefix);
        CHECKERROR(m_model);
        return constrs;
    }

    Sos AddSos(const SosBuilder &builder)
    {
        Sos sos = m_model->AddSos(builder.Get());
        CHECKERROR(m_model);
        return sos;
    }

    Sos AddSos(const VarArray &vars, const double *pWeights, int type)
    {
        Sos sos = m_model->AddSos(vars.Get(), pWeights, type);
        CHECKERROR(m_model);
        return sos;
    }

    GenConstr AddGenConstrIndicator(const GenConstrBuilder &builder)
    {
        GenConstr indicator = m_model->AddGenConstrIndicator(builder.Get());
        CHECKERROR(m_model);
        return indicator;
    }

    GenConstr AddGenConstrIndicator(const Var &binVar, int binVal, const ConstrBuilder &constr)
    {
        GenConstr indicator = m_model->AddGenConstrIndicator(binVar.Get(), binVal, constr.Get());
        CHECKERROR(m_model);
        return indicator;
    }

    GenConstr AddGenConstrIndicator(const Var &binVar, int binVal, const Expr &expr, char sense, double rhs)
    {
        GenConstr indicator = m_model->AddGenConstrIndicator(binVar.Get(), binVal, expr.Get(), sense, rhs);
        CHECKERROR(m_model);
        return indicator;
    }

    Cone AddCone(int dim, int type, char vtype, const char* szPrefix)
    {
        Cone cone = m_model->AddCone(dim, type, vtype, szPrefix);
        CHECKERROR(m_model);
        return cone;
    }

    Cone AddCone(const ConeBuilder &builder)
    {
        Cone cone = m_model->AddCone(builder.Get());
        CHECKERROR(m_model);
        return cone;
    }

    Cone AddCone(const VarArray &vars, int type)
    {
        Cone cone = m_model->AddCone(vars.Get(), type);
        CHECKERROR(m_model);
        return cone;
    }

    void GetSolution(double *pValue)
    {
        m_model->GetSolution(pValue);
        CHECKERROR(m_model);
    }

    void GetLpSolution(double *pValue, double *pSlack, double *pRowDual, double *pRedCost)
    {
        m_model->GetLpSolution(pValue, pSlack, pRowDual, pRedCost);
        CHECKERROR(m_model);
    }

    void SetLpSolution(double *pValue, double *pSlack, double *pRowDual, double *pRedCost)
    {
        m_model->SetLpSolution(pValue, pSlack, pRowDual, pRedCost);
        CHECKERROR(m_model);
    }

    int GetColBasis(int *pBasis)
    {
        int status = m_model->GetColBasis(pBasis);
        CHECKERROR(m_model);
        return status;
    }

    int GetRowBasis(int *pBasis)
    {
        int status = m_model->GetRowBasis(pBasis);
        CHECKERROR(m_model);
        return status;
    }

    void SetBasis(int *pColBasis, int *pRowBasis)
    {
        m_model->SetBasis(pColBasis, pRowBasis);
        CHECKERROR(m_model);
    }

    void SetSlackBasis()
    {
        m_model->SetSlackBasis();
        CHECKERROR(m_model);
    }

    double GetPoolObjVal(int iSol)
    {
        double objVal = m_model->GetPoolObjVal(iSol);
        CHECKERROR(m_model);
        return objVal;
    }

    int GetPoolSolution(int iSol, const VarArray &vars, double *pColVals)
    {
        int len = m_model->GetPoolSolution(iSol, vars.Get(), pColVals);
        CHECKERROR(m_model);
        return len;
    }

    double GetCoeff(const Constraint &constr, const Var &var)
    {
        double elem = m_model->GetCoeff(constr.Get(), var.Get());
        CHECKERROR(m_model);
        return elem;
    }

    void SetCoeff(const Constraint &constr, const Var &var, double newVal)
    {
        m_model->SetCoeff(constr.Get(), var.Get(), newVal);
        CHECKERROR(m_model);
    }

    Var GetVar(int idx) const
    {
        Var var = m_model->GetVar(idx);
        CHECKERROR(m_model);
        return var;
    }

    Var GetVarByName(const char *szName)
    {
        Var var = m_model->GetVarByName(szName);
        CHECKERROR(m_model);
        return var;
    }

    VarArray GetVars()
    {
        VarArray vars = m_model->GetVars();
        CHECKERROR(m_model);
        return vars;
    }

    Column GetCol(const Var &var)
    {
        Column col = m_model->GetCol(var.Get());
        CHECKERROR(m_model);
        return col;
    }

    Constraint GetConstr(int idx) const
    {
        Constraint constr = m_model->GetConstr(idx);
        CHECKERROR(m_model);
        return constr;
    }

    Constraint GetConstrByName(const char *szName)
    {
        Constraint constr = m_model->GetConstrByName(szName);
        CHECKERROR(m_model);
        return constr;
    }

    ConstrArray GetConstrs()
    {
        ConstrArray constrs = m_model->GetConstrs();
        CHECKERROR(m_model);
        return constrs;
    }

    ConstrBuilderArray GetConstrBuilders()
    {
        ConstrBuilderArray builders = m_model->GetConstrBuilders();
        CHECKERROR(m_model);
        return builders;
    }

    ConstrBuilder GetConstrBuilder(const Constraint &constr)
    {
        ConstrBuilder builder = m_model->GetConstrBuilder(constr.Get());
        CHECKERROR(m_model);
        return builder;
    }

    Expr GetRow(const Constraint &constr)
    {
        Expr expr = m_model->GetRow(constr.Get());
        CHECKERROR(m_model);
        return expr;
    }

    Sos GetSos(int idx)
    {
        Sos sos = m_model->GetSos(idx);
        CHECKERROR(m_model);
        return sos;
    }

    SosArray GetSoss()
    {
        SosArray soss = m_model->GetSoss();
        CHECKERROR(m_model);
        return soss;
    }

    SosBuilderArray GetSosBuilders()
    {
        SosBuilderArray builders = m_model->GetSosBuilders();
        CHECKERROR(m_model);
        return builders;
    }

    SosBuilderArray GetSosBuilders(SosArray &soss)
    {
        SosBuilderArray builders = m_model->GetSosBuilders(soss.Get());
        CHECKERROR(m_model);
        return builders;
    }

    GenConstrBuilder GetGenConstrIndicator(const GenConstr &indicator)
    {
        GenConstrBuilder ret = m_model->GetGenConstrIndicator(indicator.Get());
        CHECKERROR(m_model);
        return ret;
    }

    Cone GetCone(int idx)
    {
        Cone cone = m_model->GetCone(idx);
        CHECKERROR(m_model);
        return cone;
    }

    ConeArray GetCones()
    {
        ConeArray cones = m_model->GetCones();
        CHECKERROR(m_model);
        return cones;
    }

    ConeBuilderArray GetConeBuilders()
    {
        ConeBuilderArray builders = m_model->GetConeBuilders();
        CHECKERROR(m_model);
        return builders;
    }

    ConeBuilderArray GetConeBuilders(ConeArray &cones)
    {
        ConeBuilderArray builders = m_model->GetConeBuilders(cones.Get());
        CHECKERROR(m_model);
        return builders;
    }

    void SetObjSense(int sense)
    {
        m_model->SetObjSense(sense);
        CHECKERROR(m_model);
    }

    void SetObjConst(double constant)
    {
        m_model->SetObjConst(constant);
        CHECKERROR(m_model);
    }

    void SetObjective(const Expr &expr, int sense = 0)
    {
        m_model->SetObjective(expr.Get(), sense);
        CHECKERROR(m_model);
    }

    Expr GetObjective() const
    {
        Expr expr = m_model->GetObjective();
        CHECKERROR(m_model);
        return expr;
    }

    void SetMipStart(int count, double *pVals)
    {
        m_model->SetMipStart(count, pVals);
        CHECKERROR(m_model);
    }

    void SetMipStart(const Var &var, double val)
    {
        m_model->SetMipStart(var.Get(), val);
        CHECKERROR(m_model);
    }

    void SetMipStart(const VarArray &vars, double *pVals)
    {
        m_model->SetMipStart(vars.Get(), pVals);
        CHECKERROR(m_model);
    }

    void LoadMipStart()
    {
        m_model->LoadMipStart();
        CHECKERROR(m_model);
    }

    int Get(const char *szName, const VarArray &vars, double *pOut)
    {
        int ret = m_model->Get(szName, vars.Get(), pOut);
        CHECKERROR(m_model);
        return ret;
    }

    int Get(const char *szName, const ConstrArray &constrs, double *pOut)
    {
        int ret = m_model->Get(szName, constrs.Get(), pOut);
        CHECKERROR(m_model);
        return ret;
    }

    void Set(const char *szName, const VarArray &vars, double *pVals, int len)
    {
        return m_model->Set(szName, vars.Get(), pVals, len);
        CHECKERROR(m_model);
    }

    void Set(const char *szName, const ConstrArray &constrs, double *pVals, int len)
    {
        return m_model->Set(szName, constrs.Get(), pVals, len);
        CHECKERROR(m_model);
    }

    void Solve()
    {
        m_model->Solve();
        CHECKERROR(m_model);
    }
    void SolveLp()
    {
        m_model->SolveLp();
        CHECKERROR(m_model);
    }
    void Interrupt()
    {
        m_model->Interrupt();
        CHECKERROR(m_model);
    }

    void Remove(const VarArray &vars) { m_model->Remove(vars.Get()); }
    void Remove(const ConstrArray &constrs) { m_model->Remove(constrs.Get()); }
    void Remove(const SosArray &soss) { m_model->Remove(soss.Get()); }
    void Remove(const ConeArray &cones) { m_model->Remove(cones.Get()); }
    void Remove(const GenConstrArray &genConstrs) { m_model->Remove(genConstrs.Get()); }

    void ResetParam()
    {
        m_model->ResetParam();
        CHECKERROR(m_model);
    }

    void ResetAll()
    {
        m_model->ResetAll();
        CHECKERROR(m_model);
    }

    void Reset()
    {
        m_model->Reset();
        CHECKERROR(m_model);
    }

    void Clear()
    {
        m_model->Clear();
        CHECKERROR(m_model);
    }

    Model Clone()
    {
        Model model = m_model->Clone();
        CHECKERROR(m_model);
        return model;
    }

    void SetSolverLogFile(const char *szLogFile)
    {
        m_model->SetSolverLogFile(szLogFile);
        CHECKERROR(m_model);
    }

    void SetSolverLogCallback(void(COPT_CALL *logcb)(char *msg, void *userdata), void *userdata)
    {
        m_model->SetSolverLogCallback(logcb, userdata);
    }

private:
    std::shared_ptr<Copt::IModel> m_model;
};
