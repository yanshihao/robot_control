/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Adaptive_types.h
 *
 * Code generated for Simulink model 'Adaptive'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
 * C/C++ source code generated on : Tue Apr 30 15:52:58 2019
 *
 * Target selection: ert_shrlib.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Adaptive_types_h_
#define RTW_HEADER_Adaptive_types_h_
#include "rtwtypes.h"

/* Custom Type definition for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
#ifndef struct_tag_sjVaXfrJc3wv5faWU7kmQtG
#define struct_tag_sjVaXfrJc3wv5faWU7kmQtG

struct tag_sjVaXfrJc3wv5faWU7kmQtG
{
  boolean_T LT;
};

#endif                                 /*struct_tag_sjVaXfrJc3wv5faWU7kmQtG*/

#ifndef typedef_sjVaXfrJc3wv5faWU7kmQtG_Adapt_T
#define typedef_sjVaXfrJc3wv5faWU7kmQtG_Adapt_T

typedef struct tag_sjVaXfrJc3wv5faWU7kmQtG sjVaXfrJc3wv5faWU7kmQtG_Adapt_T;

#endif                               /*typedef_sjVaXfrJc3wv5faWU7kmQtG_Adapt_T*/

#ifndef struct_tag_sKLpTDgVdadEcWmkZEqDlEH
#define struct_tag_sKLpTDgVdadEcWmkZEqDlEH

struct tag_sKLpTDgVdadEcWmkZEqDlEH
{
  uint32_T LT;
  uint32_T UT;
  uint32_T UHESS;
  uint32_T SYM;
  uint32_T POSDEF;
  uint32_T RECT;
  uint32_T TRANSA;
};

#endif                                 /*struct_tag_sKLpTDgVdadEcWmkZEqDlEH*/

#ifndef typedef_sKLpTDgVdadEcWmkZEqDlEH_Adapt_T
#define typedef_sKLpTDgVdadEcWmkZEqDlEH_Adapt_T

typedef struct tag_sKLpTDgVdadEcWmkZEqDlEH sKLpTDgVdadEcWmkZEqDlEH_Adapt_T;

#endif                               /*typedef_sKLpTDgVdadEcWmkZEqDlEH_Adapt_T*/

#ifndef struct_tag_s9s8BC13iTohZXRbLMSIDHE
#define struct_tag_s9s8BC13iTohZXRbLMSIDHE

struct tag_s9s8BC13iTohZXRbLMSIDHE
{
  boolean_T CaseSensitivity;
  boolean_T StructExpand;
  boolean_T PartialMatching;
};

#endif                                 /*struct_tag_s9s8BC13iTohZXRbLMSIDHE*/

#ifndef typedef_s9s8BC13iTohZXRbLMSIDHE_Adapt_T
#define typedef_s9s8BC13iTohZXRbLMSIDHE_Adapt_T

typedef struct tag_s9s8BC13iTohZXRbLMSIDHE s9s8BC13iTohZXRbLMSIDHE_Adapt_T;

#endif                               /*typedef_s9s8BC13iTohZXRbLMSIDHE_Adapt_T*/

/* Forward declaration for rtModel */
typedef struct tag_RTM_Adaptive_T RT_MODEL_Adaptive_T;

#endif                                 /* RTW_HEADER_Adaptive_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
