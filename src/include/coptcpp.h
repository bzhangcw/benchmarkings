#ifdef _WIN32
#define COPT_CALL __stdcall
#else
#define COPT_CALL
#endif

#define COPTCPP_API extern "C"

#include "coptcpp.idl.h"

COPTCPP_API
Copt::IVarArray* COPT_CALL CreateVarArray();

COPTCPP_API
Copt::IConstrArray* COPT_CALL CreateConstrArray();

COPTCPP_API
Copt::IColumn* COPT_CALL CreateColumn();

COPTCPP_API
Copt::IColumnArray* COPT_CALL CreateColumnArray();

COPTCPP_API
Copt::IExpr* COPT_CALL CreateExpr(double constant);

COPTCPP_API
Copt::IExpr* COPT_CALL CreateLinExpr(Copt::IVar* var, double coeff);

COPTCPP_API
Copt::IConstrBuilder* COPT_CALL CreateConstrBuilder();

COPTCPP_API
Copt::IConstrBuilderArray* COPT_CALL CreateConstrBuilderArray();

COPTCPP_API
Copt::ISosArray* COPT_CALL CreateSosArray();

COPTCPP_API
Copt::ISosBuilder* COPT_CALL CreateSosBuilder();

COPTCPP_API
Copt::ISosBuilderArray* COPT_CALL CreateSosBuilderArray();

COPTCPP_API
Copt::IGenConstrArray* COPT_CALL CreateGenConstrArray();

COPTCPP_API
Copt::IGenConstrBuilder* COPT_CALL CreateGenConstrBuilder();

COPTCPP_API
Copt::IGenConstrBuilderArray* COPT_CALL CreateGenConstrBuilderArray();

COPTCPP_API
Copt::IConeArray* COPT_CALL CreateConeArray();

COPTCPP_API
Copt::IConeBuilder* COPT_CALL CreateConeBuilder();

COPTCPP_API
Copt::IConeBuilderArray* COPT_CALL CreateConeBuilderArray();

COPTCPP_API
Copt::IModel* COPT_CALL CreateModel(Copt::IEnvr* env, const char* szName);

COPTCPP_API
Copt::IEnvr* COPT_CALL CreateEnvr();

COPTCPP_API
Copt::IEnvr* COPT_CALL CreateEnvrWithPath(const char* szLicDir);

COPTCPP_API
Copt::IEnvr* COPT_CALL CreateEnvrWithConfig(Copt::IEnvrConfig* config);

COPTCPP_API
Copt::IEnvrConfig* COPT_CALL CreateEnvrConfig();

COPTCPP_API
Copt::IProbBuffer* COPT_CALL CreateProbBuffer(int sz);
