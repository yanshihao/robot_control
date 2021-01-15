/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Adaptive.h
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

#ifndef RTW_HEADER_Adaptive_h_
#define RTW_HEADER_Adaptive_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef Adaptive_COMMON_INCLUDES_
# define Adaptive_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Adaptive_COMMON_INCLUDES_ */

#include "Adaptive_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Su[1350];
  real_T dv0[900];
  real_T dv1[720];
  real_T c_Hv[720];
} B_Adaptive_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T last_mv_DSTATE[2];            /* '<S2>/last_mv' */
  real_T last_x_PreviousInput[4];      /* '<S2>/last_x' */
  real_T LastPcov_PreviousInput[16];   /* '<S2>/LastPcov' */
  boolean_T Memory_PreviousInput[16];  /* '<S2>/Memory' */
} DW_Adaptive_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T MathFunction1[2];       /* '<S2>/Math Function1' */
} ConstB_Adaptive_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: lastPcov
   * Referenced by: '<S2>/LastPcov'
   */
  real_T LastPcov_InitialCondition[16];
} ConstP_Adaptive_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T A[144];                       /* '<Root>/A' */
  real_T B[96];                        /* '<Root>/B' */
  real_T C[144];                       /* '<Root>/C' */
  real_T D[96];                        /* '<Root>/D' */
  real_T U[32];                        /* '<Root>/U' */
  real_T Y[48];                        /* '<Root>/Y' */
  real_T X[48];                        /* '<Root>/X' */
  real_T DX[48];                       /* '<Root>/DX' */
  real_T moorx[3];                     /* '<Root>/mo or x' */
  real_T ref[3];                       /* '<Root>/ref' */
  real_T umin[2];                      /* '<Root>/umin' */
  real_T umax[2];                      /* '<Root>/umax' */
  real_T ymin[3];                      /* '<Root>/ymin' */
  real_T ymax[3];                      /* '<Root>/ymax' */
  real_T ywt[3];                       /* '<Root>/y.wt' */
  real_T duwt[2];                      /* '<Root>/du.wt' */
} ExtU_Adaptive_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T mv[2];                        /* '<Root>/mv' */
} ExtY_Adaptive_T;

/* Real-time Model Data Structure */
struct tag_RTM_Adaptive_T {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Adaptive_T Adaptive_B;

/* Block states (default storage) */
extern DW_Adaptive_T Adaptive_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Adaptive_T Adaptive_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Adaptive_T Adaptive_Y;
extern const ConstB_Adaptive_T Adaptive_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_Adaptive_T Adaptive_ConstP;

/* Model entry point functions */
extern void Adaptive_initialize(void);
extern void Adaptive_step(void);
extern void Adaptive_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Adaptive_T *const Adaptive_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Data Type Conversion22' : Unused code path elimination
 * Block '<S2>/Data Type Conversion23' : Unused code path elimination
 * Block '<S3>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S4>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S5>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S6>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S7>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S8>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S9>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S10>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S11>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S12>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S13>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S14>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S15>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S16>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S17>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S18>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S19>/Vector Dimension Check' : Unused code path elimination
 * Block '<S20>/Vector Dimension Check' : Unused code path elimination
 * Block '<S21>/Vector Dimension Check' : Unused code path elimination
 * Block '<S22>/Vector Dimension Check' : Unused code path elimination
 * Block '<S23>/Vector Dimension Check' : Unused code path elimination
 * Block '<S24>/Vector Dimension Check' : Unused code path elimination
 * Block '<S25>/Vector Dimension Check' : Unused code path elimination
 * Block '<S26>/Vector Dimension Check' : Unused code path elimination
 * Block '<S27>/Vector Dimension Check' : Unused code path elimination
 * Block '<S28>/Vector Dimension Check' : Unused code path elimination
 * Block '<S2>/useq_scale' : Unused code path elimination
 * Block '<S2>/useq_scale1' : Unused code path elimination
 * Block '<S2>/ym_zero' : Unused code path elimination
 * Block '<S1>/m_zero' : Unused code path elimination
 * Block '<S1>/p_zero' : Unused code path elimination
 * Block '<S2>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion13' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion14' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion15' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion16' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion17' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion18' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion19' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion20' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion21' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion7' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion8' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S2>/E Conversion' : Eliminate redundant data type conversion
 * Block '<S2>/F Conversion' : Eliminate redundant data type conversion
 * Block '<S2>/G Conversion' : Eliminate redundant data type conversion
 * Block '<S2>/Reshape' : Reshape block reduction
 * Block '<S2>/Reshape1' : Reshape block reduction
 * Block '<S2>/Reshape2' : Reshape block reduction
 * Block '<S2>/Reshape3' : Reshape block reduction
 * Block '<S2>/Reshape4' : Reshape block reduction
 * Block '<S2>/Reshape5' : Reshape block reduction
 * Block '<S2>/S Conversion' : Eliminate redundant data type conversion
 * Block '<S2>/ext.mv_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/mo or x Conversion' : Eliminate redundant data type conversion
 * Block '<S2>/u_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/umax_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/umin_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/umin_scale4' : Eliminated nontunable gain of 1
 * Block '<S2>/uref_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/ymax_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/ymin_scale' : Eliminated nontunable gain of 1
 * Block '<S2>/ymin_scale1' : Eliminated nontunable gain of 1
 * Block '<S2>/ymin_scale2' : Eliminated nontunable gain of 1
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('mpc1_2/Adaptive MPC Controller')    - opens subsystem mpc1_2/Adaptive MPC Controller
 * hilite_system('mpc1_2/Adaptive MPC Controller/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'mpc1_2'
 * '<S1>'   : 'mpc1_2/Adaptive MPC Controller'
 * '<S2>'   : 'mpc1_2/Adaptive MPC Controller/MPC'
 * '<S3>'   : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Matrix Signal Check'
 * '<S4>'   : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Matrix Signal Check A'
 * '<S5>'   : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Matrix Signal Check B'
 * '<S6>'   : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Matrix Signal Check C'
 * '<S7>'   : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Matrix Signal Check D'
 * '<S8>'   : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Matrix Signal Check DX'
 * '<S9>'   : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Matrix Signal Check U'
 * '<S10>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Matrix Signal Check X'
 * '<S11>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Matrix Signal Check Y'
 * '<S12>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Matrix Signal Check1'
 * '<S13>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Matrix Signal Check2'
 * '<S14>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Preview Signal Check'
 * '<S15>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Preview Signal Check1'
 * '<S16>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Preview Signal Check2'
 * '<S17>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Preview Signal Check3'
 * '<S18>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Preview Signal Check4'
 * '<S19>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Scalar Signal Check'
 * '<S20>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Scalar Signal Check1'
 * '<S21>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Vector Signal Check'
 * '<S22>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Vector Signal Check1'
 * '<S23>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Vector Signal Check11'
 * '<S24>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Vector Signal Check2'
 * '<S25>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Vector Signal Check3'
 * '<S26>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Vector Signal Check4'
 * '<S27>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Vector Signal Check5'
 * '<S28>'  : 'mpc1_2/Adaptive MPC Controller/MPC/MPC Vector Signal Check6'
 * '<S29>'  : 'mpc1_2/Adaptive MPC Controller/MPC/optimizer'
 * '<S30>'  : 'mpc1_2/Adaptive MPC Controller/MPC/optimizer/FixedHorizonOptimizer'
 */
#endif                                 /* RTW_HEADER_Adaptive_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
