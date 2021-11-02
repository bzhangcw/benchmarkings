#ifndef __COPT_H__
#define __COPT_H__

#ifdef _WIN32
#define COPT_CALL __stdcall
#else
#define COPT_CALL
#endif

#ifdef _WIN32
#define COPT_INT64 __int64
#elif defined(__LP64__) || defined(_LP64) || defined(__ILP64__) || defined(_ILP64)
#define COPT_INT64 long
#else
#define COPT_INT64 long long
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define COPT_VERSION_MAJOR                      3
#define COPT_VERSION_MINOR                      0
#define COPT_VERSION_TECHNICAL                  1


/*
 * Constants
 */

/* Optimization direction */
#define COPT_MINIMIZE                           1
#define COPT_MAXIMIZE                          -1

/* Default infinity value */
#define COPT_INFINITY                           1e30

/* Recommended buffer size for messages */
#define COPT_BUFFSIZE                           1000

/* Constraint types */
#define COPT_LESS_EQUAL                        'L'
#define COPT_GREATER_EQUAL                     'G'
#define COPT_EQUAL                             'E'
#define COPT_FREE                              'N'
#define COPT_RANGE                             'R'

/* Variable types */
#define COPT_CONTINUOUS                        'C'
#define COPT_BINARY                            'B'
#define COPT_INTEGER                           'I'

/* SOS types */
#define COPT_SOS_TYPE1                          1
#define COPT_SOS_TYPE2                          2

/* Cone types */
#define COPT_CONE_QUAD                          1
#define COPT_CONE_RQUAD                         2

/* API function return code */
#define COPT_RETCODE_OK                         0
#define COPT_RETCODE_MEMORY                     1
#define COPT_RETCODE_FILE                       2
#define COPT_RETCODE_INVALID                    3
#define COPT_RETCODE_LICENSE                    4
#define COPT_RETCODE_INTERNAL                   5
#define COPT_RETCODE_THREAD                     6
#define COPT_RETCODE_SERVER                     7

/* Basis status */
#define COPT_BASIS_LOWER                        0
#define COPT_BASIS_BASIC                        1
#define COPT_BASIS_UPPER                        2
#define COPT_BASIS_SUPERBASIC                   3
#define COPT_BASIS_FIXED                        4

/* LP status */
#define COPT_LPSTATUS_UNSTARTED                 0
#define COPT_LPSTATUS_OPTIMAL                   1
#define COPT_LPSTATUS_INFEASIBLE                2
#define COPT_LPSTATUS_UNBOUNDED                 3
#define COPT_LPSTATUS_NUMERICAL                 5
#define COPT_LPSTATUS_TIMEOUT                   8
#define COPT_LPSTATUS_UNFINISHED                9
#define COPT_LPSTATUS_INTERRUPTED              10

/* MIP status */
#define COPT_MIPSTATUS_UNSTARTED                0
#define COPT_MIPSTATUS_OPTIMAL                  1
#define COPT_MIPSTATUS_INFEASIBLE               2
#define COPT_MIPSTATUS_UNBOUNDED                3
#define COPT_MIPSTATUS_INF_OR_UNB               4
#define COPT_MIPSTATUS_NODELIMIT                6
#define COPT_MIPSTATUS_TIMEOUT                  8
#define COPT_MIPSTATUS_UNFINISHED               9
#define COPT_MIPSTATUS_INTERRUPTED              10

/*
 * Parameters and attributes
 */

/* Double parameters */
#define COPT_DBLPARAM_TIMELIMIT                 "TimeLimit"
#define COPT_DBLPARAM_MATRIXTOL                 "MatrixTol"
#define COPT_DBLPARAM_FEASTOL                   "FeasTol"
#define COPT_DBLPARAM_DUALTOL                   "DualTol"
#define COPT_DBLPARAM_INTTOL                    "IntTol"
#define COPT_DBLPARAM_RELGAP                    "RelGap"

/* Integer parameters */
#define COPT_INTPARAM_LOGGING                   "Logging"
#define COPT_INTPARAM_LOGTOCONSOLE              "LogToConsole"
#define COPT_INTPARAM_PRESOLVE                  "Presolve"
#define COPT_INTPARAM_SCALING                   "Scaling"
#define COPT_INTPARAM_DUALIZE                   "Dualize"
#define COPT_INTPARAM_LPMETHOD                  "LpMethod"
#define COPT_INTPARAM_DUALPRICE                 "DualPrice"
#define COPT_INTPARAM_DUALPERTURB               "DualPerturb"
#define COPT_INTPARAM_CUTLEVEL                  "CutLevel"
#define COPT_INTPARAM_ROOTCUTLEVEL              "RootCutLevel"
#define COPT_INTPARAM_TREECUTLEVEL              "TreeCutLevel"
#define COPT_INTPARAM_ROOTCUTROUNDS             "RootCutRounds"
#define COPT_INTPARAM_NODECUTROUNDS             "NodeCutRounds"
#define COPT_INTPARAM_HEURLEVEL                 "HeurLevel"
#define COPT_INTPARAM_ROUNDINGHEURLEVEL         "RoundingHeurLevel"
#define COPT_INTPARAM_DIVINGHEURLEVEL           "DivingHeurLevel"
#define COPT_INTPARAM_SUBMIPHEURLEVEL           "SubMipHeurLevel"
#define COPT_INTPARAM_STRONGBRANCHING           "StrongBranching"
#define COPT_INTPARAM_CONFLICTANALYSIS          "ConflictAnalysis"
#define COPT_INTPARAM_NODELIMIT                 "NodeLimit"
#define COPT_INTPARAM_MIPTASKS                  "MipTasks"
#define COPT_INTPARAM_BARHOMOGENEOUS            "BarHomogeneous"
#define COPT_INTPARAM_BARITERLIMIT              "BarIterLimit"
#define COPT_INTPARAM_THREADS                   "Threads"
#define COPT_INTPARAM_BARTHREADS                "BarThreads"
#define COPT_INTPARAM_SIMPLEXTHREADS            "SimplexThreads"
#define COPT_INTPARAM_CROSSOVERTHREADS          "CrossoverThreads"

/* Double attributes */
#define COPT_DBLATTR_SOLVINGTIME                "SolvingTime"
#define COPT_DBLATTR_OBJCONST                   "ObjConst"
#define COPT_DBLATTR_LPOBJVAL                   "LpObjval"
#define COPT_DBLATTR_BESTOBJ                    "BestObj"
#define COPT_DBLATTR_BESTBND                    "BestBnd"
#define COPT_DBLATTR_BESTGAP                    "BestGap"

/* Integer attributes */
#define COPT_INTATTR_COLS                       "Cols"
#define COPT_INTATTR_ROWS                       "Rows"
#define COPT_INTATTR_ELEMS                      "Elems"
#define COPT_INTATTR_BINS                       "Bins"
#define COPT_INTATTR_INTS                       "Ints"
#define COPT_INTATTR_SOSS                       "Soss"
#define COPT_INTATTR_CONES                      "Cones"
#define COPT_INTATTR_INDICATORS                 "Indicators"
#define COPT_INTATTR_OBJSENSE                   "ObjSense"
#define COPT_INTATTR_LPSTATUS                   "LpStatus"
#define COPT_INTATTR_MIPSTATUS                  "MipStatus"
#define COPT_INTATTR_SIMPLEXITER                "SimplexIter"
#define COPT_INTATTR_BARRIERITER                "BarrierIter"
#define COPT_INTATTR_NODECNT                    "NodeCnt"
#define COPT_INTATTR_POOLSOLS                   "PoolSols"
#define COPT_INTATTR_HASLPSOL                   "HasLpSol"
#define COPT_INTATTR_HASBASIS                   "HasBasis"
#define COPT_INTATTR_HASMIPSOL                  "HasMipSol"
#define COPT_INTATTR_ISMIP                      "IsMIP"

/* Variable info types */
#define COPT_DBLINFO_OBJ                        "Obj"
#define COPT_DBLINFO_LB                         "LB"
#define COPT_DBLINFO_UB                         "UB"
#define COPT_DBLINFO_VALUE                      "Value"
#define COPT_DBLINFO_SLACK                      "Slack"
#define COPT_DBLINFO_DUAL                       "Dual"
#define COPT_DBLINFO_REDCOST                    "RedCost"

/* COPT client config keywords */
#define COPT_CLIENT_CLUSTER                     "Cluster"
#define COPT_CLIENT_FLOATING                    "Floating"
#define COPT_CLIENT_PASSWORD                    "PassWord"
#define COPT_CLIENT_PORT                        "Port"
#define COPT_CLIENT_WAITTIME                    "WaitTime"

/*
 * API functions
 */

typedef struct copt_env_config_s copt_env_config;
typedef struct copt_env_s  copt_env;
typedef struct copt_prob_s copt_prob;

int COPT_CALL COPT_GetBanner(char *buff, int buffSize);
int COPT_CALL COPT_GetRetcodeMsg(int code, char *buff, int buffSize);

int COPT_CALL COPT_CreateEnvConfig(copt_env_config **p_config);
int COPT_CALL COPT_DeleteEnvConfig(copt_env_config **p_config);
int COPT_CALL COPT_SetEnvConfig(copt_env_config *config, const char *name, const char *value);

int COPT_CALL COPT_CreateEnv(copt_env **p_env);
int COPT_CALL COPT_CreateEnvWithPath(const char *licDir, copt_env **p_env);
int COPT_CALL COPT_CreateEnvWithConfig(copt_env_config *config, copt_env **p_env);
int COPT_CALL COPT_CloseEnv(copt_env **p_env);
int COPT_CALL COPT_DeleteEnv(copt_env **p_env);
int COPT_CALL COPT_GetLicenseMsg(copt_env *env, char *buff, int buffSize);

int COPT_CALL COPT_CreateProb(copt_env *env, copt_prob **p_prob);
int COPT_CALL COPT_CreateCopy(copt_prob *src_prob, copt_prob **p_dst_prob);
int COPT_CALL COPT_DeleteProb(copt_prob **p_prob);

int COPT_CALL COPT_LoadProb(copt_prob *prob,
    int               nCol,
    int               nRow,
    int               iObjSense,
    double            dObjConst,
    const double      *colObj,
    const int         *colMatBeg,
    const int         *colMatCnt,
    const int         *colMatIdx,
    const double      *colMatElem,
    const char        *colType,
    const double      *colLower,
    const double      *colUpper,
    const char        *rowSense,
    const double      *rowBound,
    const double      *rowUpper,
    char const *const *colNames,
    char const *const *rowNames);

int COPT_CALL COPT_AddCol(copt_prob *prob,
    double            dColObj,
    int               nColMatCnt,
    const int         *colMatIdx,
    const double      *colMatElem,
    char              cColType,
    double            dColLower,
    double            dColUpper,
    const char        *colName);

int COPT_CALL COPT_AddRow(copt_prob *prob,
    int               nRowMatCnt,
    const int         *rowMatIdx,
    const double      *rowMatElem,
    char              cRowSense,
    double            dRowBound,
    double            dRowUpper,
    const char        *rowName);

int COPT_CALL COPT_AddCols(copt_prob *prob,
    int               nAddCol,
    const double      *colObj,
    const int         *colMatBeg,
    const int         *colMatCnt,
    const int         *colMatIdx,
    const double      *colMatElem,
    const char        *colType,
    const double      *colLower,
    const double      *colUpper,
    char const *const *colNames);

int COPT_CALL COPT_AddRows(copt_prob *prob,
    int               nAddRow,
    const int         *rowMatBeg,
    const int         *rowMatCnt,
    const int         *rowMatIdx,
    const double      *rowMatElem,
    const char        *rowSense,
    const double      *rowBound,
    const double      *rowUpper,
    char const *const *rowNames);

int COPT_CALL COPT_AddSOSs(copt_prob *prob,
    int               nAddSOS,
    const int         *sosType,
    const int         *sosMatBeg,
    const int         *sosMatCnt,
    const int         *sosMatIdx,
    const double      *sosMatWt);

int COPT_CALL COPT_AddCones(copt_prob *prob,
    int               nAddCone,
    const int         *coneType,
    const int         *coneBeg,
    const int         *coneCnt,
    const int         *coneIdx);

int COPT_CALL COPT_AddIndicator(copt_prob *prob,
    int               binColIdx,
    int               binColVal,
    int               nRowMatCnt,
    const int         *rowMatIdx,
    const double      *rowMatElem,
    char              cRowSense,
    double            dRowBound);

int COPT_CALL COPT_GetCols(copt_prob *prob,
    int               nCol,
    const int         *list,
    int               *colMatBeg,
    int               *colMatCnt,
    int               *colMatIdx,
    double            *colMatElem,
    int               nElemSize,
    int               *pReqSize);

int COPT_CALL COPT_GetRows(copt_prob *prob,
    int               nRow,
    const int         *list,
    int               *rowMatBeg,
    int               *rowMatCnt,
    int               *rowMatIdx,
    double            *rowMatElem,
    int               nElemSize,
    int               *pReqSize);

int COPT_CALL COPT_GetSOSs(copt_prob *prob,
    int               nSos,
    const int         *list,
    int               *sosType,
    int               *sosMatBeg,
    int               *sosMatCnt,
    int               *sosMatIdx,
    double            *sosMatWt,
    int               nElemSize,
    int               *pReqSize);

int COPT_CALL COPT_GetCones(copt_prob *prob,
    int               nCone,
    const int         *list,
    int               *coneType,
    int               *coneBeg,
    int               *coneCnt,
    int               *coneIdx,
    int               nElemSize,
    int               *pReqSize);

int COPT_CALL COPT_GetIndicator(copt_prob *prob,
    int               rowIdx,
    int               *binColIdx,
    int               *binColVal,
    int               *nRowMatCnt,
    int               *rowMatIdx,
    double            *rowMatElem,
    char              *cRowSense,
    double            *dRowBound,
    int               nElemSize,
    int               *pReqSize);

int COPT_CALL COPT_GetElem(copt_prob *prob, int iCol, int iRow, double *p_elem);
int COPT_CALL COPT_SetElem(copt_prob *prob, int iCol, int iRow, double newElem);

int COPT_CALL COPT_DelCols(copt_prob *prob, int num, const int *list);
int COPT_CALL COPT_DelRows(copt_prob *prob, int num, const int *list);
int COPT_CALL COPT_DelSOSs(copt_prob *prob, int num, const int *list);
int COPT_CALL COPT_DelCones(copt_prob *prob, int num, const int *list);
int COPT_CALL COPT_DelIndicators(copt_prob *prob, int num, const int *list);

int COPT_CALL COPT_SetObjSense(copt_prob *prob, int iObjSense);
int COPT_CALL COPT_SetObjConst(copt_prob *prob, double dObjConst);

int COPT_CALL COPT_SetColObj(copt_prob *prob, int num, const int *list, const double *obj);
int COPT_CALL COPT_SetColType(copt_prob *prob, int num, const int *list, const char *type);
int COPT_CALL COPT_SetColLower(copt_prob *prob, int num, const int *list, const double *lower);
int COPT_CALL COPT_SetColUpper(copt_prob *prob, int num, const int *list, const double *upper);
int COPT_CALL COPT_SetColNames(copt_prob *prob, int num, const int *list, char const *const *names);

int COPT_CALL COPT_SetRowLower(copt_prob *prob, int num, const int *list, const double *lower);
int COPT_CALL COPT_SetRowUpper(copt_prob *prob, int num, const int *list, const double *upper);
int COPT_CALL COPT_SetRowNames(copt_prob *prob, int num, const int *list, char const *const *names);

int COPT_CALL COPT_ReplaceColObj(copt_prob *prob, int num, const int *list, const double *obj);

int COPT_CALL COPT_ReadMps(copt_prob *prob, const char *mpsfilename);
int COPT_CALL COPT_ReadLp(copt_prob *prob, const char *lpfilename);
int COPT_CALL COPT_ReadBin(copt_prob *prob, const char *binfilename);
int COPT_CALL COPT_ReadSol(copt_prob *prob, const char *solfilename);
int COPT_CALL COPT_ReadBasis(copt_prob *prob, const char *basfilename);
int COPT_CALL COPT_ReadMst(copt_prob *prob, const char *mstfilename);
int COPT_CALL COPT_ReadParam(copt_prob *prob, const char *parfilename);
int COPT_CALL COPT_ReadParamStr(copt_prob *prob, const char *strParam);
int COPT_CALL COPT_ReadBlob(copt_prob *prob, void *blob, COPT_INT64 len);

int COPT_CALL COPT_WriteMps(copt_prob *prob, const char *mpsfilename);
int COPT_CALL COPT_WriteLp(copt_prob *prob, const char *lpfilename);
int COPT_CALL COPT_WriteBin(copt_prob *prob, const char *binfilename);
int COPT_CALL COPT_WriteSol(copt_prob *prob, const char *solfilename);
int COPT_CALL COPT_WriteBasis(copt_prob *prob, const char *basfilename);
int COPT_CALL COPT_WriteMst(copt_prob *prob, const char *mstfilename);
int COPT_CALL COPT_WriteParam(copt_prob *prob, const char *parfilename);
int COPT_CALL COPT_WriteMpsStr(copt_prob *prob, char *str, int nStrSize, int *pReqSize);
int COPT_CALL COPT_WriteParamStr(copt_prob *prob, char *str, int nStrSize, int *pReqSize);
int COPT_CALL COPT_WriteBlob(copt_prob *prob, int tryCompress, void **p_blob, COPT_INT64 *pLen);

int COPT_CALL COPT_AddMipStart(copt_prob *prob, int num, const int *list, double *colVal);

int COPT_CALL COPT_SolveLp(copt_prob *prob);
int COPT_CALL COPT_Solve(copt_prob *prob);

int COPT_CALL COPT_GetSolution(copt_prob *prob, double *colVal);
int COPT_CALL COPT_GetLpSolution(copt_prob *prob, double *value, double *slack, double *rowDual, double *redCost);
int COPT_CALL COPT_SetLpSolution(copt_prob *prob, const double *value, const double *slack, const double *rowDual, const double *redCost);
int COPT_CALL COPT_GetBasis(copt_prob *prob, int *colBasis, int *rowBasis);
int COPT_CALL COPT_SetBasis(copt_prob *prob, const int *colBasis, const int *rowBasis);
int COPT_CALL COPT_SetSlackBasis(copt_prob *prob);

int COPT_CALL COPT_GetPoolObjVal(copt_prob *prob, int iSol, double *p_objVal);
int COPT_CALL COPT_GetPoolSolution(copt_prob *prob, int iSol, int num, const int *list, double *colVal);

int COPT_CALL COPT_SetIntParam(copt_prob *prob, const char *paramName, int intParam);
int COPT_CALL COPT_GetIntParam(copt_prob *prob, const char *paramName, int *p_intParam);
int COPT_CALL COPT_GetIntParamDef(copt_prob *prob, const char *paramName, int *p_intParam);
int COPT_CALL COPT_GetIntParamMin(copt_prob *prob, const char *paramName, int *p_intParam);
int COPT_CALL COPT_GetIntParamMax(copt_prob *prob, const char *paramName, int *p_intParam);

int COPT_CALL COPT_SetDblParam(copt_prob *prob, const char *paramName, double dblParam);
int COPT_CALL COPT_GetDblParam(copt_prob *prob, const char *paramName, double *p_dblParam);
int COPT_CALL COPT_GetDblParamDef(copt_prob *prob, const char *paramName, double *p_dblParam);
int COPT_CALL COPT_GetDblParamMin(copt_prob *prob, const char *paramName, double *p_dblParam);
int COPT_CALL COPT_GetDblParamMax(copt_prob *prob, const char *paramName, double *p_dblParam);

int COPT_CALL COPT_ResetParam(copt_prob *prob);
int COPT_CALL COPT_Reset(copt_prob *prob, int iClearAll);

int COPT_CALL COPT_GetIntAttr(copt_prob *prob, const char *attrName, int *p_intAttr);
int COPT_CALL COPT_GetDblAttr(copt_prob *prob, const char *attrName, double *p_dblAttr);

int COPT_CALL COPT_GetColIdx(copt_prob *prob, const char *colName, int *p_iCol);
int COPT_CALL COPT_GetRowIdx(copt_prob *prob, const char *rowName, int *p_iRow);
int COPT_CALL COPT_GetColInfo(copt_prob *prob, const char *infoName, int num, const int *list, double *info);
int COPT_CALL COPT_GetRowInfo(copt_prob *prob, const char *infoName, int num, const int *list, double *info);

int COPT_CALL COPT_GetColType(copt_prob *prob, int num, const int *list, char *type);
int COPT_CALL COPT_GetColBasis(copt_prob *prob, int num, const int *list, int *colBasis);
int COPT_CALL COPT_GetRowBasis(copt_prob *prob, int num, const int *list, int *rowBasis);

int COPT_CALL COPT_GetColName(copt_prob *prob, int iCol, char *buff, int buffSize, int *pReqSize);
int COPT_CALL COPT_GetRowName(copt_prob *prob, int iRow, char *buff, int buffSize, int *pReqSize);

int COPT_CALL COPT_SetLogFile(copt_prob *prob, const char *logfilename);
int COPT_CALL COPT_SetLogCallback(copt_prob *prob, void (COPT_CALL *logcb)(char *msg, void *userdata), void *userdata);

int COPT_CALL COPT_Interrupt(copt_prob *prob);

#ifdef __cplusplus
}
#endif

#endif /* __COPT_H__ */
