#pragma once
#ifdef _WIN32
#define COPT_CALL __stdcall
#else
#define COPT_CALL
#endif
#include <memory>
#include <vector>

namespace Copt {
class IVar {
public:
  virtual ~IVar() = default;

  virtual int GetIdx() const = 0;
  virtual const char* GetName() const = 0;
  virtual void SetName(const char* szName) = 0;
  virtual char GetType() const = 0;
  virtual void SetType(char type) = 0;
  virtual int GetBasis() const = 0;

  virtual double Get(const char* szAttr) = 0;
  virtual void Set(const char* szAttr, double value) = 0;

  virtual void Remove() = 0;

  virtual int GetLastError() const = 0;
  virtual const char* GetErrorMessage() const = 0;
};

class IVarArray {
public:
  virtual ~IVarArray() = default;

  virtual void PushBack(const IVar* pVar) = 0;

  virtual int Size() const = 0;
  virtual IVar* GetVar(int idx) const = 0;
  virtual std::vector<IVar*> GetAll() = 0;
  virtual void Reserve(int n) = 0;
};

class IConstraint {
public:
  virtual ~IConstraint() = default;

  virtual int GetIdx() const = 0;
  virtual const char* GetName() const = 0;
  virtual void SetName(const char* szName) = 0;
  virtual int GetBasis() const = 0;

  virtual double Get(const char* szAttr) = 0;
  virtual void Set(const char* szAttr, double value) = 0;

  virtual void Remove() = 0;

  virtual int GetLastError() const = 0;
  virtual const char* GetErrorMessage() const = 0;
};

class IConstrArray {
public:
  virtual ~IConstrArray() = default;

  virtual void PushBack(const IConstraint* pConstr) = 0;

  virtual int Size() const = 0;
  virtual IConstraint* GetConstr(int idx) const = 0;
  virtual std::vector<IConstraint*> GetAll() = 0;
  virtual void Reserve(int n) = 0;
};

class IColumn {
public:
  virtual ~IColumn() = default;

  virtual int Size() const = 0;
  virtual IConstraint* GetConstr(int i) const = 0;
  virtual double GetCoeff(int i) const = 0;

  virtual void AddTerm(const IConstraint* pConstr, double coeff) = 0;
  virtual int AddTerms(const IConstrArray* pConstrs, double* pCoeff, int len) = 0;
  virtual void AddColumn(const IColumn* pCol, double mult) = 0;

  virtual void Remove(int idx) = 0;
  virtual void Remove(const IConstraint* pConstr) = 0;
  virtual void Reserve(int n) = 0;
  virtual void Clear() = 0;
  virtual IColumn* Clone() const = 0;
};

class IColumnArray {
public:
  virtual ~IColumnArray() = default;

  virtual void PushBack(const IColumn* pCol) = 0;

  virtual int Size() const = 0;
  virtual IColumn* GetColumn(int idx) const = 0;
  virtual void Reserve(int n) = 0;
  virtual void Clear() = 0;
};

class IExpr {
public:
  virtual ~IExpr() = default;

  virtual size_t Size() const = 0;
  virtual IVar* GetVar(int i) const = 0;
  virtual double GetCoeff(int i) const = 0;
  virtual double GetConstant() const = 0;

  virtual void SetCoeff(int i, double value) = 0;
  virtual void SetConstant(double constant) = 0;
  virtual void AddConstant(double constant) = 0;

  virtual void AddTerm(const IVar* pVar, double coeff) = 0;
  virtual int AddTerms(const IVarArray* pVars, double* pCoeff, int len) = 0;
  virtual void AddExpr(const IExpr* pExpr, double mult) = 0;

  virtual double Evaluate() = 0;
  virtual void Remove(int idx) = 0;
  virtual void Remove(const IVar* pVar) = 0;
  virtual void Reserve(size_t n) = 0;
  virtual IExpr* Clone() const = 0;
};

class IConstrBuilder {
public:
  virtual ~IConstrBuilder() = default;

  virtual IExpr* GetExpr() const = 0;
  virtual char GetSense() const = 0;
  virtual double GetRange() const = 0;
  virtual void Set(const IExpr* expr, char sense, double rhs) const = 0;
  virtual void SetRange(const IExpr* expr, double range) const = 0;
};

class IConstrBuilderArray {
public:
  virtual ~IConstrBuilderArray() = default;

  virtual void PushBack(const IConstrBuilder* pcb) = 0;

  virtual int Size() const = 0;
  virtual void Reserve(int n) = 0;
  virtual IConstrBuilder* GetBuilder(int idx) const = 0;
};

class ISos {
public:
  virtual ~ISos() = default;

  virtual int GetIdx() const = 0;
  virtual void Remove() = 0;
};

class ISosArray {
public:
  virtual ~ISosArray() = default;

  virtual void PushBack(const ISos* pSos) = 0;

  virtual int Size() const = 0;
  virtual ISos* GetSos(int idx) const = 0;
};

class ISosBuilder {
public:
  virtual ~ISosBuilder() = default;

  virtual int GetType() const = 0;
  virtual int GetSize() const = 0;
  virtual IVar* GetVar(int idx) const = 0;
  virtual IVarArray* GetVars() const = 0;
  virtual double GetWeight(int idx) const = 0;
  virtual void GetWeights(double* pOut) const = 0;

  virtual void Set(const IVarArray* vars, double* pWeights, int type) = 0;
};

class ISosBuilderArray {
public:
  virtual ~ISosBuilderArray() = default;

  virtual void PushBack(const ISosBuilder* pcb) = 0;

  virtual int Size() const = 0;
  virtual ISosBuilder* GetBuilder(int idx) const = 0;
};

class IGenConstr {
public:
  virtual ~IGenConstr() = default;

  virtual int GetIdx() const = 0;
  virtual void Remove() = 0;
};

class IGenConstrArray {
public:
  virtual ~IGenConstrArray() = default;

  virtual void PushBack(const IGenConstr* pConstr) = 0;

  virtual int Size() const = 0;
  virtual IGenConstr* GetGenConstr(int idx) const = 0;
};

class IGenConstrBuilder {
public:
  virtual ~IGenConstrBuilder() = default;

  virtual IVar* GetBinVar() const = 0;
  virtual int GetBinVal() const = 0;
  virtual IExpr* GetExpr() const = 0;
  virtual char GetSense() const = 0;

  virtual void Set(const IVar* binVar, int binVal, const IExpr* expr, char sense) = 0;
};

class IGenConstrBuilderArray {
public:
  virtual ~IGenConstrBuilderArray() = default;

  virtual void PushBack(const IGenConstrBuilder* pcb) = 0;

  virtual int Size() const = 0;
  virtual IGenConstrBuilder* GetBuilder(int idx) const = 0;
};

class ICone {
public:
  virtual ~ICone() = default;

  virtual int GetIdx() const = 0;
  virtual void Remove() = 0;
};

class IConeArray {
public:
  virtual ~IConeArray() = default;

  virtual void PushBack(const ICone* pCone) = 0;

  virtual int Size() const = 0;
  virtual ICone* GetCone(int idx) const = 0;
};

class IConeBuilder {
public:
  virtual ~IConeBuilder() = default;

  virtual int GetType() const = 0;
  virtual int GetSize() const = 0;
  virtual IVar* GetVar(int idx) const = 0;
  virtual IVarArray* GetVars() const = 0;

  virtual void Set(const IVarArray* vars, int type) = 0;
};

class IConeBuilderArray {
public:
  virtual ~IConeBuilderArray() = default;

  virtual void PushBack(const IConeBuilder* pcb) = 0;

  virtual int Size() const = 0;
  virtual IConeBuilder* GetBuilder(int idx) const = 0;
};

class IProbBuffer {
public:
  virtual ~IProbBuffer() = default;

  virtual char* GetData() = 0;
  virtual int Size() const = 0;
  virtual void Resize(int sz) = 0;
};

class IModel {
public:
  virtual ~IModel() = default;

  virtual void Read(const char* szFileName) = 0;
  virtual void ReadMps(const char* szFileName) = 0;
  virtual void ReadLp(const char* szFileName) = 0;
  virtual void ReadBin(const char* szFileName) = 0;
  virtual void ReadSol(const char* szFileName) = 0;
  virtual void ReadBasis(const char* szFileName) = 0;
  virtual void ReadMst(const char* szFileName) = 0;
  virtual void ReadParam(const char* szFileName) = 0;

  virtual void GetParamInfo(const char* szParam, int* pnCur, int* pnDef, int* pnMin, int* pnMax) = 0;
  virtual void GetParamInfo(const char* szParam, double* pdCur, double* pdDef, double* pdMin, double* pdMax) = 0;

  virtual int GetIntParam(const char* szParam) = 0;
  virtual double GetDblParam(const char* szParam) = 0;
  virtual void SetIntParam(const char* szParam, int nVal) = 0;
  virtual void SetDblParam(const char* szParam, double dVal) = 0;

  virtual void Write(const char* szFileName) = 0;
  virtual void WriteMps(const char* szFileName) = 0;
  virtual IProbBuffer* WriteMpsStr() = 0;
  virtual void WriteLp(const char* szFileName) = 0;
  virtual void WriteBin(const char* szFileName) = 0;
  virtual void WriteSol(const char* szFileName) = 0;
  virtual void WriteBasis(const char* szFileName) = 0;
  virtual void WriteMst(const char* szFileName) = 0;
  virtual void WriteParam(const char* szFileName) = 0;

  virtual int GetIntAttr(const char* szAttr) = 0;
  virtual double GetDblAttr(const char* szAttr) = 0;
  virtual int GetParamAttrType(const char* szName) = 0;

  virtual IVar* AddVar(double lb, double ub, double obj, char vtype, const char* szName) = 0;
  virtual IVar* AddVar(double lb, double ub, double obj, char vtype, const IColumn* col, const char* szName) = 0;
  virtual IVarArray* AddVars(int count, char vtype, const char* szPrefix) = 0;
  virtual IVarArray* AddVars(int count, char vtype, const char* szNames, int len) = 0;
  virtual IVarArray* AddVars(int count, double lb, double ub, double obj, char vtype, const char* szPrefix) = 0;
  virtual IVarArray* AddVars(int count, double lb, double ub, double obj, char vtype, const char* szNames, int len) = 0;
  virtual IVarArray* AddVars(int count, double* plb, double* pub, double* pobj, char* pvtype, const char* szPrefix) = 0;
  virtual IVarArray*
  AddVars(int count, double* plb, double* pub, double* pobj, char* pvtype, const char* szNames, int len) = 0;
  virtual IVarArray* AddVars(int count,
    double* plb,
    double* pub,
    double* pobj,
    char* pvtype,
    const IColumnArray* cols,
    const char* szPrefix) = 0;

  virtual IConstraint* AddConstr(const IExpr* expr, char sense, double rhs, const char* szName) = 0;
  virtual IConstraint* AddConstr(const IExpr* lhs, char sense, const IExpr* rhs, const char* szName) = 0;
  virtual IConstraint* AddConstr(const IExpr* expr, double lb, double ub, const char* szName) = 0;
  virtual IConstraint* AddConstr(const IConstrBuilder* builder, const char* szName) = 0;
  virtual IConstrArray* AddConstrs(int count, char* pSense, double* pRhs, const char* szPrefix) = 0;
  virtual IConstrArray* AddConstrs(int count, double* pLower, double* pUpper, const char* szPrefix) = 0;
  virtual IConstrArray* AddConstrs(int count, double* pLower, double* pUpper, const char* szNames, int len) = 0;
  virtual IConstrArray* AddConstrs(const IConstrBuilderArray* builders, const char* szPrefix) = 0;
  virtual IConstrArray* AddConstrs(const IConstrBuilderArray* builders, const char* szNames, int len) = 0;
  virtual ISos* AddSos(const ISosBuilder* builder) = 0;
  virtual ISos* AddSos(const IVarArray* pVars, const double* pWeights, int type) = 0;

  virtual IGenConstr* AddGenConstrIndicator(const IGenConstrBuilder* pBuilder) = 0;
  virtual IGenConstr* AddGenConstrIndicator(const IVar* binVar, int binVal, const IConstrBuilder* pConstr) = 0;
  virtual IGenConstr*
  AddGenConstrIndicator(const IVar* binVar, int binVal, const IExpr* expr, char sense, double rhs) = 0;

  virtual ICone* AddCone(int dim, int type, char vtype, const char* szPrefix) = 0;
  virtual ICone* AddCone(const IConeBuilder* builder) = 0;
  virtual ICone* AddCone(const IVarArray* pVars, int type) = 0;

  virtual void GetSolution(double* pValue) = 0;
  virtual void GetLpSolution(double* pValue, double* pSlack, double* pRowDual, double* pRedCost) = 0;
  virtual void SetLpSolution(double* pValue, double* pSlack, double* pRowDual, double* pRedCost) = 0;
  virtual int GetColBasis(int* pBasis) = 0;
  virtual int GetRowBasis(int* pBasis) = 0;
  virtual void SetBasis(int* pColBasis, int* pRowBasis) = 0;
  virtual void SetSlackBasis() = 0;

  virtual double GetPoolObjVal(int iSol) = 0;
  virtual int GetPoolSolution(int iSol, const IVarArray* pVars, double* pColVals) = 0;

  virtual double GetCoeff(const IConstraint* pConstr, const IVar* pVar) = 0;
  virtual void SetCoeff(const IConstraint* pConstr, const IVar* pVar, double newVal) = 0;

  virtual void GetCoeffMatrix(int* pMatBeg, int* pMatCnt, int* pMatIdx, double* pMatElem) = 0;
  virtual void LoadMatrix(int nCol,
    int nRow,
    double* pCost,
    int* pMatBeg,
    int* pMatCnt,
    int* pMatIdx,
    double* pMatElem,
    double* pLHS,
    double* pRHS,
    double* pLB,
    double* pUB,
    char* pType) = 0;

  virtual IVar* GetVar(int idx) const = 0;
  virtual IVar* GetVarByName(const char* szName) = 0;
  virtual IVarArray* GetVars() = 0;
  virtual IColumn* GetCol(const IVar* pVar) = 0;
  virtual IConstraint* GetConstr(int idx) const = 0;
  virtual IConstraint* GetConstrByName(const char* szName) = 0;
  virtual IConstrArray* GetConstrs() = 0;
  virtual IConstrBuilderArray* GetConstrBuilders() = 0;
  virtual IConstrBuilder* GetConstrBuilder(const IConstraint* pConstr) = 0;
  virtual IExpr* GetRow(const IConstraint* pConstr) = 0;
  virtual ISos* GetSos(int idx) const = 0;
  virtual ISosArray* GetSoss() = 0;
  virtual ISosBuilderArray* GetSosBuilders() = 0;
  virtual ISosBuilderArray* GetSosBuilders(const ISosArray* pSoss) = 0;
  virtual IGenConstrBuilder* GetGenConstrIndicator(const IGenConstr* pIndicator) = 0;

  virtual ICone* GetCone(int idx) const = 0;
  virtual IConeArray* GetCones() = 0;
  virtual IConeBuilderArray* GetConeBuilders() = 0;
  virtual IConeBuilderArray* GetConeBuilders(const IConeArray* pCones) = 0;

  virtual void SetObjSense(int sense) = 0;
  virtual void SetObjConst(double constant) = 0;
  virtual void SetObjective(const IExpr* expr, int sense) = 0;
  virtual IExpr* GetObjective() const = 0;

  virtual void SetMipStart(int count, double* pVals) = 0;
  virtual void SetMipStart(const IVar* pVar, double val) = 0;
  virtual void SetMipStart(const IVarArray* pVars, double* pVals) = 0;
  virtual void LoadMipStart() = 0;

  virtual int Get(const char* szName, const IVarArray* pVars, double* pOut) = 0;
  virtual int Get(const char* szName, const IConstrArray* pConstrs, double* pOut) = 0;
  virtual void Set(const char* szName, const IVarArray* pVars, double* pVals, int len) = 0;
  virtual void Set(const char* szName, const IConstrArray* pConstrs, double* pVals, int len) = 0;

  virtual void Solve() = 0;
  virtual void SolveLp() = 0;
  virtual void Interrupt() = 0;

  virtual void Remove(IVarArray* pVars) = 0;
  virtual void Remove(IConstrArray* pConstrs) = 0;
  virtual void Remove(ISosArray* pSoss) = 0;
  virtual void Remove(IConeArray* pCones) = 0;
  virtual void Remove(IGenConstrArray* pGenConstrs) = 0;

  virtual void ResetParam() = 0;
  virtual void ResetAll() = 0;
  virtual void Reset() = 0;

  virtual void Clear() = 0;
  virtual IModel* Clone() = 0;

  virtual void SetSolverLogFile(const char* szLogFile) = 0;
  virtual void SetSolverLogCallback(void(COPT_CALL* logcb)(char* msg, void* userdata), void* userdata) = 0;

  virtual int GetLastError() const = 0;
  virtual const char* GetErrorMessage() const = 0;
};

class IEnvrConfig {
public:
  virtual ~IEnvrConfig() = default;

  virtual void Set(const char* szName, const char* szValue) = 0;

  virtual int GetLastError() const = 0;
  virtual const char* GetErrorMessage() const = 0;
};

class IEnvr {
public:
  virtual ~IEnvr() = default;

  virtual IModel* CreateModel(const char* szName) = 0;
  virtual void Close() = 0;

  virtual int GetLastError() const = 0;
  virtual const char* GetErrorMessage() const = 0;
};
}  // namespace Copt
