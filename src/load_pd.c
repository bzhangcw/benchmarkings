

#include "copt.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int errcode = 0;

  copt_env *env = NULL;
  copt_prob *prob = NULL;

  // Create COPT environment
  errcode = COPT_CreateEnv(&env);
  if (errcode)
    goto COPT_EXIT;

  // Create COPT problem
  errcode = COPT_CreateProb(env, &prob);
  if (errcode)
    goto COPT_EXIT;

  errcode = COPT_ReadMps(&prob, argv[1]);
  if (errcode)
    goto COPT_EXIT;

  // Set parameters and attributes
  errcode = COPT_Setlp(prob, COPT_DBLPARAM_TIMELIMIT, 10);
  if (errcode)
    goto COPT_EXIT;
  errcode = COPT_SetObjSense(prob, COPT_MAXIMIZE);
  if (errcode)
    goto COPT_EXIT;

  // Solve problem
  errcode = COPT_SolveLp(prob);
  if (errcode)
    goto COPT_EXIT;

  // Analyze solution
  int lpstat = COPT_LPSTATUS_UNSTARTED;
  double lpobjval;
  double *lpsol = NULL;
  int *colstat = NULL;

  errcode = COPT_GetIntAttr(prob, COPT_INTATTR_LPSTATUS, &lpstat);
  if (errcode)
    goto COPT_EXIT;

  if (lpstat == COPT_LPSTATUS_OPTIMAL)
  {
    lpsol = (double *)malloc(ncol * sizeof(double));
    colstat = (int *)malloc(ncol * sizeof(int));

    errcode = COPT_GetLpSolution(prob, lpsol, NULL, NULL, NULL);
    if (errcode)
      goto COPT_EXIT;

    errcode = COPT_GetBasis(prob, colstat, NULL);
    if (errcode)
      goto COPT_EXIT;

    errcode = COPT_GetDblAttr(prob, COPT_DBLATTR_LPOBJVAL, &lpobjval);
    if (errcode)
      goto COPT_EXIT;

    printf("\nObjective value: %.6f\n", lpobjval);

    printf("Variable solution: \n");
    for (int i = 0; i < ncol; ++i)
      printf("  x[%d] = %.6f\n", i, lpsol[i]);

    printf("Variable basis status: \n");
    for (int i = 0; i < ncol; ++i)
      printf("  x[%d]: %d\n", i, colstat[i]);

    free(lpsol);
    free(colstat);
  }

  // Write problem, solution and modified parameters to files
  errcode = COPT_WriteMps(prob, "lp_ex1.mps");
  if (errcode)
    goto COPT_EXIT;
  errcode = COPT_WriteBasis(prob, "lp_ex1.bas");
  if (errcode)
    goto COPT_EXIT;
  errcode = COPT_WriteSol(prob, "lp_ex1.sol");
  if (errcode)
    goto COPT_EXIT;
  errcode = COPT_WriteParam(prob, "lp_ex1.par");
  if (errcode)
    goto COPT_EXIT;

  // Error handling
COPT_EXIT:
  if (errcode)
  {
    char errmsg[COPT_BUFFSIZE];

    COPT_GetRetcodeMsg(errcode, errmsg, COPT_BUFFSIZE);
    printf("ERROR %d: %s\n", errcode, errmsg);

    return 0;
  }

  // Delete problem and environment
  COPT_DeleteProb(&prob);

  COPT_DeleteEnv(&env);

  return 0;
}
