/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Adaptive.c
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

#include "Adaptive.h"
#include "Adaptive_private.h"

/* Named constants for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
#define Adaptive_nu                    (2.0)
#define Adaptive_ny                    (3.0)

/* Block signals (default storage) */
B_Adaptive_T Adaptive_B;

/* Block states (default storage) */
DW_Adaptive_T Adaptive_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Adaptive_T Adaptive_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Adaptive_T Adaptive_Y;

/* Real-time model */
RT_MODEL_Adaptive_T Adaptive_M_;
RT_MODEL_Adaptive_T *const Adaptive_M = &Adaptive_M_;

/* Forward declaration for local functions */
static void Adaptive_mpc_plantupdate(const real_T a[9], real_T b[6], const
  real_T c[9], real_T b_A[16], real_T b_B[28], real_T b_C[12], const real_T b_D
  [21], const real_T b_mvindex[2], const real_T b_myindex[3], const real_T
  b_Uscale[2], const real_T b_Yscale[3], real_T Bu[8], real_T Bv[4], real_T Cm
  [12], real_T Dv[3], real_T Dvm[3], real_T QQ[16], real_T RR[9], real_T NN[12]);
static real_T Adaptive_mod_g(real_T x);
static real_T Adaptive_mod(real_T x);
static void Adaptive_mpc_updateFromNominal(real_T b_Mlim[16], const real_T
  b_Mrows[16], const real_T U0[32], const real_T b_Uscale[2], const real_T
  old_mvoff[2], const real_T b_mvindex[2], real_T b_utarget[30], const real_T
  Y0[48], const real_T b_Yscale[3], const real_T old_yoff[3], const real_T
  b_myindex[3], const real_T X0[48], real_T b_xoff[4], const real_T DX0[48],
  const real_T b_A[256], const real_T Bu[128], real_T Bv[64], const real_T b_C
  [192], real_T Dv[48], real_T new_mvoff[2], real_T new_yoff[3], real_T
  new_myoff[3]);
static void Adaptive_mpcblock_refmd(const real_T ref[3], const real_T b_yoff[3],
  const real_T b_RYscale[3], real_T rseq[45], real_T vseq[16], real_T *v);
static void Adaptive_eye(real_T b_I[9]);
static void Adaptive_mrdivide_helper(const real_T b_A[9], const real_T b_B[9],
  real_T Y[9]);
static void Adaptive_mpc_constraintcoef(const real_T b_A[256], const real_T Bu
  [128], const real_T Bv[64], const real_T b_C[192], const real_T Dv[48], const
  real_T b_Jm[240], real_T b_SuJm[360], real_T b_Sx[180], real_T b_Su1[90],
  real_T b_Hv[720]);
static void Adaptive_updateWeights(real_T W[3], const real_T b_signal[3], real_T
  ZERO);
static void Adaptive_updateWeights_e(real_T W[2], const real_T b_signal[2],
  real_T ZERO);
static void Adaptive_eye_o(real_T b_I[4]);
static void Adaptive_kron(const real_T b_A[225], const real_T b_B[4], real_T K
  [900]);
static void Adaptive_WtMult(const real_T W[3], const real_T M[360], real_T nwt,
  real_T WM[360]);
static void Adaptive_WtMult_a(const real_T W[2], const real_T M[240], real_T nwt,
  real_T WM[240]);
static void Adaptive_mpc_calculatehessian(const real_T b_Wy[3], const real_T
  b_Wu[2], const real_T b_Wdu[2], const real_T b_SuJm[360], const real_T I2Jm
  [240], const real_T b_Jm[240], const real_T b_I1[60], const real_T b_Su1[90],
  const real_T b_Sx[180], const real_T b_Hv[720], real_T nmv, real_T b_ny,
  real_T b_H[64], real_T b_Ku1[16], real_T b_Kut[240], real_T b_Kx[32], real_T
  b_Kv[128], real_T b_Kr[360]);
static int32_T Adaptive_xpotrf(real_T b_A[81]);
static void Adaptive_mpc_checkhessian(real_T b_H[81], real_T L[81], real_T *BadH);
static void Adaptive_eye_oi(real_T b_I[81]);
static void Adaptive_trisolve(const real_T b_A[81], real_T b_B[81]);
static void Adaptive_linsolve(const real_T b_A[81], const real_T b_B[81], real_T
  b_C[81]);
static void Adaptive_Unconstrained(const real_T b_Hinv[81], const real_T f[9],
  real_T x[9], int16_T n);
static real_T Adaptive_norm(const real_T x[9]);
static void Adaptive_abs(const real_T x[9], real_T y[9]);
static void Adaptive_abs_e(const real_T x[16], real_T y[16]);
static real_T Adaptive_xnrm2(int32_T n, const real_T x[81], int32_T ix0);
static void Adaptive_xgemv(int32_T m, int32_T n, const real_T b_A[81], int32_T
  ia0, const real_T x[81], int32_T ix0, real_T y[9]);
static void Adaptive_xgerc(int32_T m, int32_T n, real_T alpha1, int32_T ix0,
  const real_T y[9], real_T b_A[81], int32_T ia0);
static void Adaptive_xgeqrf(real_T b_A[81], real_T tau[9]);
static void Adaptive_qr(const real_T b_A[81], real_T Q[81], real_T R[81]);
static real_T Adaptive_KWIKfactor(const real_T b_Ac[144], const int16_T iC[16],
  int16_T nA, const real_T b_Linv[81], real_T RLinv[81], real_T b_D[81], real_T
  b_H[81], int16_T n);
static void Adaptive_DropConstraint(int16_T kDrop, int16_T iA[16], int16_T *nA,
  int16_T iC[16]);
static int16_T Adaptive_rdivide_helper(int16_T x, int16_T y);
static void Adaptive_qpkwik(const real_T b_Linv[81], const real_T b_Hinv[81],
  const real_T f[9], const real_T b_Ac[144], const real_T b[16], int16_T iA[16],
  int16_T b_maxiter, real_T FeasTol, real_T x[9], real_T lambda[16], real_T
  *status);
static void Adaptive_mpc_solveQP(const real_T xQP[4], const real_T b_Kx[32],
  const real_T b_Kr[360], const real_T rseq[45], const real_T b_Ku1[16], const
  real_T old_u[2], const real_T b_Kv[128], const real_T vseq[16], const real_T
  b_Kut[240], const real_T b_utarget[30], const real_T b_Linv[81], const real_T
  b_Hinv[81], const real_T b_Ac[144], const real_T Bc[16], boolean_T iA[16],
  real_T zopt[9], real_T f[9], real_T *status);
static void Adaptive_mpcblock_optimizer(const real_T rseq[45], const real_T
  vseq[16], const real_T umin[2], const real_T umax[2], const real_T ymin[3],
  const real_T ymax[3], const real_T x[4], const real_T old_u[2], const
  boolean_T iA[16], const real_T b_Mlim[16], real_T b_Mx[64], real_T b_Mu1[32],
  real_T b_Mv[256], const real_T b_utarget[30], const real_T b_uoff[2], const
  real_T b_yoff[3], real_T b_H[81], real_T b_Ac[144], const real_T ywt[3], const
  real_T duwt[2], real_T b_Wy[3], real_T b_Wdu[2], const real_T b_Jm[240], const
  real_T b_Wu[2], const real_T b_I1[60], const real_T b_A[256], const real_T Bu
  [128], const real_T Bv[64], const real_T b_C[192], const real_T Dv[48], const
  real_T b_Mrows[16], real_T u[2], real_T useq[32], real_T *status, boolean_T
  iAout[16]);

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_mpc_plantupdate(const real_T a[9], real_T b[6], const
  real_T c[9], real_T b_A[16], real_T b_B[28], real_T b_C[12], const real_T b_D
  [21], const real_T b_mvindex[2], const real_T b_myindex[3], const real_T
  b_Uscale[2], const real_T b_Yscale[3], real_T Bu[8], real_T Bv[4], real_T Cm
  [12], real_T Dv[3], real_T Dvm[3], real_T QQ[16], real_T RR[9], real_T NN[12])
{
  int8_T UnknownIn[6];
  real_T CovMat[49];
  real_T b_B_0[42];
  real_T b_B_1[42];
  int32_T i;
  int32_T b_tmp;
  int32_T b_B_tmp;
  int32_T b_B_tmp_0;
  int32_T b_B_tmp_1;
  for (i = 0; i < 2; i++) {
    b[3 * i] *= b_Uscale[i];
    b_tmp = 3 * i + 1;
    b[b_tmp] *= b_Uscale[i];
    b_tmp = 3 * i + 2;
    b[b_tmp] *= b_Uscale[i];
  }

  for (i = 0; i < 3; i++) {
    b_C[3 * i] = c[3 * i] / b_Yscale[0];
    b_tmp = i << 2;
    b_A[b_tmp] = a[3 * i];
    b_B_tmp = 3 * i + 1;
    b_C[b_B_tmp] = c[b_B_tmp] / b_Yscale[1];
    b_A[1 + b_tmp] = a[b_B_tmp];
    b_B_tmp = 3 * i + 2;
    b_C[b_B_tmp] = c[b_B_tmp] / b_Yscale[2];
    b_A[2 + b_tmp] = a[b_B_tmp];
  }

  for (i = 0; i < 2; i++) {
    b_tmp = ((int32_T)b_mvindex[i] - 1) * 3;
    b_B_tmp = i << 2;
    b_B[b_B_tmp] = b[b_tmp];
    b_B_tmp_0 = 1 + b_B_tmp;
    b_B[b_B_tmp_0] = b[b_tmp + 1];
    b_B_tmp_1 = 2 + b_B_tmp;
    b_B[b_B_tmp_1] = b[b_tmp + 2];
    Bu[b_B_tmp] = b_B[b_B_tmp];
    Bu[b_B_tmp_0] = b_B[b_B_tmp_0];
    Bu[b_B_tmp_1] = b_B[b_B_tmp_1];
    Bu[3 + (i << 2)] = b_B[b_B_tmp + 3];
  }

  for (i = 0; i < 4; i++) {
    Bv[i] = b_B[8 + i];
    Cm[3 * i] = b_C[(3 * i + (int32_T)b_myindex[0]) - 1];
    Cm[1 + 3 * i] = b_C[(3 * i + (int32_T)b_myindex[1]) - 1];
    Cm[2 + 3 * i] = b_C[(3 * i + (int32_T)b_myindex[2]) - 1];
  }

  Dv[0] = b_D[6];
  b_B_tmp = (int32_T)b_myindex[0];
  Dvm[0] = b_D[b_B_tmp + 5];
  Dv[1] = b_D[7];
  Dvm[1] = b_D[(int32_T)b_myindex[1] + 5];
  Dv[2] = b_D[8];
  Dvm[2] = b_D[(int32_T)b_myindex[2] + 5];
  UnknownIn[0] = 1;
  UnknownIn[1] = 2;
  UnknownIn[2] = 4;
  UnknownIn[3] = 5;
  UnknownIn[4] = 6;
  UnknownIn[5] = 7;
  for (i = 0; i < 6; i++) {
    b_B_tmp_0 = UnknownIn[i] - 1;
    b_tmp = b_B_tmp_0 << 2;
    b_B_0[7 * i] = b_B[b_tmp];
    b_B_0[1 + 7 * i] = b_B[b_tmp + 1];
    b_B_0[2 + 7 * i] = b_B[b_tmp + 2];
    b_B_0[3 + 7 * i] = b_B[b_tmp + 3];
    b_tmp = b_B_tmp_0 * 3;
    b_B_0[4 + 7 * i] = b_D[(b_tmp + b_B_tmp) - 1];
    b_B_0[5 + 7 * i] = b_D[(b_tmp + (int32_T)b_myindex[1]) - 1];
    b_B_0[6 + 7 * i] = b_D[(b_tmp + (int32_T)b_myindex[2]) - 1];
  }

  for (i = 0; i < 4; i++) {
    for (b_tmp = 0; b_tmp < 6; b_tmp++) {
      b_B_1[b_tmp + 6 * i] = b_B[((UnknownIn[b_tmp] - 1) << 2) + i];
    }
  }

  for (i = 0; i < 3; i++) {
    for (b_tmp = 0; b_tmp < 6; b_tmp++) {
      b_B_1[b_tmp + 6 * (i + 4)] = b_D[((UnknownIn[b_tmp] - 1) * 3 + (int32_T)
        b_myindex[i]) - 1];
    }
  }

  for (i = 0; i < 7; i++) {
    for (b_tmp = 0; b_tmp < 7; b_tmp++) {
      b_B_tmp_0 = b_tmp + 7 * i;
      CovMat[b_B_tmp_0] = 0.0;
      for (b_B_tmp = 0; b_B_tmp < 6; b_B_tmp++) {
        CovMat[b_B_tmp_0] += b_B_0[7 * b_B_tmp + b_tmp] * b_B_1[6 * i + b_B_tmp];
      }
    }
  }

  for (i = 0; i < 4; i++) {
    b_tmp = i << 2;
    QQ[b_tmp] = CovMat[7 * i];
    QQ[1 + b_tmp] = CovMat[7 * i + 1];
    QQ[2 + b_tmp] = CovMat[7 * i + 2];
    QQ[3 + b_tmp] = CovMat[7 * i + 3];
  }

  for (i = 0; i < 3; i++) {
    b_tmp = (4 + i) * 7;
    RR[3 * i] = CovMat[b_tmp + 4];
    RR[1 + 3 * i] = CovMat[b_tmp + 5];
    RR[2 + 3 * i] = CovMat[b_tmp + 6];
    b_B_tmp = i << 2;
    NN[b_B_tmp] = CovMat[b_tmp];
    NN[1 + b_B_tmp] = CovMat[b_tmp + 1];
    NN[2 + b_B_tmp] = CovMat[b_tmp + 2];
    NN[3 + b_B_tmp] = CovMat[b_tmp + 3];
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static real_T Adaptive_mod_g(real_T x)
{
  real_T r;
  if (rtIsNaN(x)) {
    r = (rtNaN);
  } else if (rtIsInf(x)) {
    r = (rtNaN);
  } else if (x == 0.0) {
    r = 0.0;
  } else {
    r = fmod(x, Adaptive_nu);
    if (r == 0.0) {
      r = 0.0;
    } else {
      if (x < 0.0) {
        r += Adaptive_nu;
      }
    }
  }

  return r;
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static real_T Adaptive_mod(real_T x)
{
  real_T r;
  if (rtIsNaN(x)) {
    r = (rtNaN);
  } else if (rtIsInf(x)) {
    r = (rtNaN);
  } else if (x == 0.0) {
    r = 0.0;
  } else {
    r = fmod(x, Adaptive_ny);
    if (r == 0.0) {
      r = 0.0;
    } else {
      if (x < 0.0) {
        r += Adaptive_ny;
      }
    }
  }

  return r;
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_mpc_updateFromNominal(real_T b_Mlim[16], const real_T
  b_Mrows[16], const real_T U0[32], const real_T b_Uscale[2], const real_T
  old_mvoff[2], const real_T b_mvindex[2], real_T b_utarget[30], const real_T
  Y0[48], const real_T b_Yscale[3], const real_T old_yoff[3], const real_T
  b_myindex[3], const real_T X0[48], real_T b_xoff[4], const real_T DX0[48],
  const real_T b_A[256], const real_T Bu[128], real_T Bv[64], const real_T b_C
  [192], real_T Dv[48], real_T new_mvoff[2], real_T new_yoff[3], real_T
  new_myoff[3])
{
  real_T U[2];
  real_T b_k;
  int32_T b_ct;
  real_T U0_0[2];
  real_T b_utarget_0[15];
  real_T tmp;
  real_T new_mvoff_idx_0;
  real_T new_mvoff_idx_1;
  real_T U_tmp;
  int32_T tmp_0;
  int32_T new_mvoff_tmp;
  int32_T new_mvoff_tmp_0;
  int32_T new_mvoff_idx_0_tmp;
  int32_T new_mvoff_tmp_1;
  int32_T new_mvoff_tmp_2;
  int32_T Bu_tmp;
  int32_T tmp_1;
  int32_T tmp_2;
  b_k = U0[0] / b_Uscale[0];
  U[0] = b_k;
  U_tmp = U0[1] / b_Uscale[1];
  U[1] = U_tmp;
  new_yoff[0] = Y0[0] / b_Yscale[0];
  new_yoff[1] = Y0[1] / b_Yscale[1];
  new_yoff[2] = Y0[2] / b_Yscale[2];
  U0_0[0] = b_k;
  U0_0[1] = U_tmp;
  new_mvoff_tmp = (int32_T)b_mvindex[0];
  new_mvoff_tmp_0 = new_mvoff_tmp - 1;
  new_mvoff[0] = U0_0[new_mvoff_tmp_0];
  new_mvoff_tmp_1 = (int32_T)b_mvindex[1];
  new_mvoff_tmp_2 = new_mvoff_tmp_1 - 1;
  new_mvoff[1] = U0_0[new_mvoff_tmp_2];
  new_myoff[0] = new_yoff[(int32_T)b_myindex[0] - 1];
  new_myoff[1] = new_yoff[(int32_T)b_myindex[1] - 1];
  new_myoff[2] = new_yoff[(int32_T)b_myindex[2] - 1];
  for (b_ct = 0; b_ct < 16; b_ct++) {
    if (b_Mrows[b_ct] <= 45.0) {
      new_mvoff_idx_0_tmp = (int32_T)(Adaptive_mod(b_Mrows[b_ct] - 1.0) + 1.0) -
        1;
      b_Mlim[b_ct] += old_yoff[new_mvoff_idx_0_tmp] -
        new_yoff[new_mvoff_idx_0_tmp];
    } else if (b_Mrows[b_ct] <= 90.0) {
      new_mvoff_idx_0_tmp = (int32_T)(Adaptive_mod((b_Mrows[b_ct] - 45.0) - 1.0)
        + 1.0) - 1;
      b_Mlim[b_ct] -= old_yoff[new_mvoff_idx_0_tmp] -
        new_yoff[new_mvoff_idx_0_tmp];
    } else if (b_Mrows[b_ct] <= 120.0) {
      new_mvoff_idx_0_tmp = (int32_T)(Adaptive_mod_g((b_Mrows[b_ct] - 90.0) -
        1.0) + 1.0) - 1;
      b_Mlim[b_ct] += old_mvoff[new_mvoff_idx_0_tmp] - U[(int32_T)
        b_mvindex[new_mvoff_idx_0_tmp] - 1];
    } else {
      if (b_Mrows[b_ct] <= 150.0) {
        b_k = Adaptive_mod_g(((b_Mrows[b_ct] - 90.0) - 30.0) - 1.0) + 1.0;
        b_Mlim[b_ct] -= old_mvoff[(int32_T)b_k - 1] - U[(int32_T)b_mvindex
          [(int32_T)b_k - 1] - 1];
      }
    }
  }

  for (b_ct = 0; b_ct < 2; b_ct++) {
    b_k = U[(int32_T)b_mvindex[b_ct] - 1];
    for (new_mvoff_idx_0_tmp = 0; new_mvoff_idx_0_tmp < 15; new_mvoff_idx_0_tmp
         ++) {
      b_utarget_0[new_mvoff_idx_0_tmp] = (b_utarget[(int32_T)Adaptive_nu *
        new_mvoff_idx_0_tmp + b_ct] + old_mvoff[b_ct]) - b_k;
    }

    for (new_mvoff_idx_0_tmp = 0; new_mvoff_idx_0_tmp < 15; new_mvoff_idx_0_tmp
         ++) {
      b_utarget[(int32_T)Adaptive_nu * new_mvoff_idx_0_tmp + b_ct] =
        b_utarget_0[new_mvoff_idx_0_tmp];
    }
  }

  b_xoff[0] = X0[0];
  Bv[0] = DX0[0];
  b_xoff[1] = X0[1];
  Bv[1] = DX0[1];
  b_xoff[2] = X0[2];
  Bv[2] = DX0[2];
  for (b_ct = 0; b_ct < 15; b_ct++) {
    tmp_0 = (b_ct + 1) * 3;
    b_k = b_xoff[0] - X0[tmp_0];
    U_tmp = b_xoff[1] - X0[tmp_0 + 1];
    tmp = b_xoff[2] - X0[tmp_0 + 2];
    new_mvoff_idx_0_tmp = (b_ct + 1) << 1;
    new_mvoff_idx_0 = new_mvoff[0] - U0[(new_mvoff_idx_0_tmp + new_mvoff_tmp) -
      1] / b_Uscale[new_mvoff_tmp_0];
    new_mvoff_idx_1 = new_mvoff[1] - U0[(new_mvoff_idx_0_tmp + new_mvoff_tmp_1)
      - 1] / b_Uscale[new_mvoff_tmp_2];
    for (new_mvoff_idx_0_tmp = 0; new_mvoff_idx_0_tmp < 3; new_mvoff_idx_0_tmp++)
    {
      Bu_tmp = ((b_ct + 1) << 3) + new_mvoff_idx_0_tmp;
      tmp_1 = ((b_ct + 1) << 4) + new_mvoff_idx_0_tmp;
      tmp_2 = tmp_0 + new_mvoff_idx_0_tmp;
      Bv[new_mvoff_idx_0_tmp + ((b_ct + 1) << 2)] = (((b_A[tmp_1 + 4] * U_tmp +
        b_A[tmp_1] * b_k) + b_A[tmp_1 + 8] * tmp) + ((DX0[tmp_2] + X0[tmp_2]) -
        b_xoff[new_mvoff_idx_0_tmp])) + (Bu[Bu_tmp + 4] * new_mvoff_idx_1 +
        Bu[Bu_tmp] * new_mvoff_idx_0);
      tmp_1 = (b_ct + 1) * 12 + new_mvoff_idx_0_tmp;
      Dv[tmp_2] = ((b_C[tmp_1 + 3] * U_tmp + b_C[tmp_1] * b_k) + b_C[tmp_1 + 6] *
                   tmp) + (Y0[tmp_2] / b_Yscale[new_mvoff_idx_0_tmp] -
                           new_yoff[new_mvoff_idx_0_tmp]);
    }
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_mpcblock_refmd(const real_T ref[3], const real_T b_yoff[3],
  const real_T b_RYscale[3], real_T rseq[45], real_T vseq[16], real_T *v)
{
  int32_T i;
  int32_T rseq_tmp;
  for (i = 0; i < 16; i++) {
    vseq[i] = 1.0;
  }

  memset(&rseq[0], 0, 45U * sizeof(real_T));
  for (i = 0; i < 15; i++) {
    rseq_tmp = i * (int32_T)Adaptive_ny;
    rseq[rseq_tmp] = ref[0] * b_RYscale[0] - b_yoff[0];
    rseq[1 + rseq_tmp] = ref[1] * b_RYscale[1] - b_yoff[1];
    rseq[2 + rseq_tmp] = ref[2] * b_RYscale[2] - b_yoff[2];
  }

  *v = 1.0;
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_eye(real_T b_I[9])
{
  memset(&b_I[0], 0, 9U * sizeof(real_T));
  b_I[0] = 1.0;
  b_I[4] = 1.0;
  b_I[8] = 1.0;
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_mrdivide_helper(const real_T b_A[9], const real_T b_B[9],
  real_T Y[9])
{
  real_T c_A[9];
  int32_T r1;
  int32_T r2;
  int32_T r3;
  real_T maxval;
  real_T a21;
  int32_T rtemp;
  int32_T Y_tmp;
  real_T Y_tmp_0;
  int32_T Y_tmp_1;
  real_T Y_tmp_2;
  real_T Y_tmp_3;
  real_T Y_tmp_4;
  memcpy(&c_A[0], &b_B[0], 9U * sizeof(real_T));
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = fabs(b_B[0]);
  a21 = fabs(b_B[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }

  if (fabs(b_B[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  c_A[r2] = b_B[r2] / b_B[r1];
  c_A[r3] /= c_A[r1];
  c_A[3 + r2] -= c_A[3 + r1] * c_A[r2];
  c_A[3 + r3] -= c_A[3 + r1] * c_A[r3];
  c_A[6 + r2] -= c_A[6 + r1] * c_A[r2];
  c_A[6 + r3] -= c_A[6 + r1] * c_A[r3];
  if (fabs(c_A[3 + r3]) > fabs(c_A[3 + r2])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  c_A[3 + r3] /= c_A[3 + r2];
  c_A[6 + r3] -= c_A[3 + r3] * c_A[6 + r2];
  Y[3 * r1] = b_A[0] / c_A[r1];
  maxval = c_A[3 + r1];
  Y[3 * r2] = b_A[3] - Y[3 * r1] * maxval;
  a21 = c_A[6 + r1];
  Y[3 * r3] = b_A[6] - Y[3 * r1] * a21;
  Y_tmp_0 = c_A[3 + r2];
  Y[3 * r2] /= Y_tmp_0;
  Y_tmp_2 = c_A[6 + r2];
  Y[3 * r3] -= Y[3 * r2] * Y_tmp_2;
  Y_tmp_3 = c_A[6 + r3];
  Y[3 * r3] /= Y_tmp_3;
  Y_tmp_4 = c_A[3 + r3];
  Y[3 * r2] -= Y[3 * r3] * Y_tmp_4;
  Y[3 * r1] -= Y[3 * r3] * c_A[r3];
  Y[3 * r1] -= Y[3 * r2] * c_A[r2];
  rtemp = 1 + 3 * r1;
  Y[rtemp] = b_A[1] / c_A[r1];
  Y_tmp = 1 + 3 * r2;
  Y[Y_tmp] = b_A[4] - Y[rtemp] * maxval;
  Y_tmp_1 = 1 + 3 * r3;
  Y[Y_tmp_1] = b_A[7] - Y[rtemp] * a21;
  Y[Y_tmp] /= Y_tmp_0;
  Y[Y_tmp_1] -= Y[Y_tmp] * Y_tmp_2;
  Y[Y_tmp_1] /= Y_tmp_3;
  Y[Y_tmp] -= Y[Y_tmp_1] * Y_tmp_4;
  Y[rtemp] -= Y[Y_tmp_1] * c_A[r3];
  Y[rtemp] -= Y[Y_tmp] * c_A[r2];
  rtemp = 2 + 3 * r1;
  Y[rtemp] = b_A[2] / c_A[r1];
  Y_tmp = 2 + 3 * r2;
  Y[Y_tmp] = b_A[5] - Y[rtemp] * maxval;
  Y_tmp_1 = 2 + 3 * r3;
  Y[Y_tmp_1] = b_A[8] - Y[rtemp] * a21;
  Y[Y_tmp] /= Y_tmp_0;
  Y[Y_tmp_1] -= Y[Y_tmp] * Y_tmp_2;
  Y[Y_tmp_1] /= Y_tmp_3;
  Y[Y_tmp] -= Y[Y_tmp_1] * Y_tmp_4;
  Y[rtemp] -= Y[Y_tmp_1] * c_A[r3];
  Y[rtemp] -= Y[Y_tmp] * c_A[r2];
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_mpc_constraintcoef(const real_T b_A[256], const real_T Bu
  [128], const real_T Bv[64], const real_T b_C[192], const real_T Dv[48], const
  real_T b_Jm[240], real_T b_SuJm[360], real_T b_Sx[180], real_T b_Su1[90],
  real_T b_Hv[720])
{
  real_T AA[224];
  int8_T rows[3];
  int32_T i;
  int32_T b_j;
  real_T b_C_0[12];
  real_T b_C_1[6];
  int8_T i_0;
  int32_T i_1;
  real_T AA_0[16];
  int32_T i_2;
  real_T b_C_2;
  int32_T b_Hv_tmp;
  int32_T b_C_tmp;
  int32_T b_Su1_tmp;
  int32_T b_C_tmp_0;
  int32_T AA_tmp;
  for (i_2 = 0; i_2 < 3; i_2++) {
    b_C_2 = b_C[i_2 + 21] * Bv[3] + (b_C[i_2 + 18] * Bv[2] + (b_C[i_2 + 15] *
      Bv[1] + b_C[12 + i_2] * Bv[0]));
    b_Hv[i_2] = b_C_2;
    b_Hv[45 + i_2] = Dv[3 + i_2];
  }

  for (i_2 = 0; i_2 < 14; i_2++) {
    b_Hv_tmp = 45 * (i_2 + 2);
    b_Hv[b_Hv_tmp] = 0.0;
    b_Hv[1 + b_Hv_tmp] = 0.0;
    b_Hv[2 + b_Hv_tmp] = 0.0;
  }

  for (i_2 = 0; i_2 < 16; i_2++) {
    memset(&b_Hv[i_2 * 45 + 3], 0, 42U * sizeof(real_T));
  }

  for (i_2 = 0; i_2 < 4; i_2++) {
    for (i_1 = 0; i_1 < 3; i_1++) {
      b_Hv_tmp = i_1 + 3 * i_2;
      b_C_0[b_Hv_tmp] = 0.0;
      b_C_tmp = i_2 << 2;
      b_C_0[b_Hv_tmp] += b_C[12 + i_1] * b_A[b_C_tmp];
      b_C_0[b_Hv_tmp] += b_A[b_C_tmp + 1] * b_C[i_1 + 15];
      b_C_0[b_Hv_tmp] += b_A[b_C_tmp + 2] * b_C[i_1 + 18];
      b_C_0[b_Hv_tmp] += b_A[b_C_tmp + 3] * b_C[i_1 + 21];
    }
  }

  for (i_2 = 0; i_2 < 4; i_2++) {
    b_Sx[45 * i_2] = b_C_0[3 * i_2];
    b_Sx[1 + 45 * i_2] = b_C_0[3 * i_2 + 1];
    b_Sx[2 + 45 * i_2] = b_C_0[3 * i_2 + 2];
    memset(&b_Sx[i_2 * 45 + 3], 0, 42U * sizeof(real_T));
  }

  for (i_2 = 0; i_2 < 2; i_2++) {
    for (i_1 = 0; i_1 < 3; i_1++) {
      b_Hv_tmp = i_1 + 3 * i_2;
      b_C_1[b_Hv_tmp] = 0.0;
      b_C_tmp = i_2 << 2;
      b_C_1[b_Hv_tmp] += b_C[12 + i_1] * Bu[b_C_tmp];
      b_C_1[b_Hv_tmp] += Bu[b_C_tmp + 1] * b_C[i_1 + 15];
      b_C_1[b_Hv_tmp] += Bu[b_C_tmp + 2] * b_C[i_1 + 18];
      b_C_1[b_Hv_tmp] += Bu[b_C_tmp + 3] * b_C[i_1 + 21];
    }
  }

  for (i_2 = 0; i_2 < 2; i_2++) {
    b_Su1[45 * i_2] = b_C_1[3 * i_2];
    b_Hv_tmp = 1 + 45 * i_2;
    b_Su1[b_Hv_tmp] = b_C_1[3 * i_2 + 1];
    b_C_tmp = 2 + 45 * i_2;
    b_Su1[b_C_tmp] = b_C_1[3 * i_2 + 2];
    memset(&b_Su1[i_2 * 45 + 3], 0, 42U * sizeof(real_T));
    Adaptive_B.Su[45 * i_2] = b_Su1[45 * i_2];
    Adaptive_B.Su[b_Hv_tmp] = b_Su1[b_Hv_tmp];
    Adaptive_B.Su[b_C_tmp] = b_Su1[b_C_tmp];
  }

  for (i_2 = 0; i_2 < 28; i_2++) {
    b_Hv_tmp = 45 * (i_2 + 2);
    Adaptive_B.Su[b_Hv_tmp] = 0.0;
    Adaptive_B.Su[1 + b_Hv_tmp] = 0.0;
    Adaptive_B.Su[2 + b_Hv_tmp] = 0.0;
  }

  for (i_2 = 0; i_2 < 30; i_2++) {
    memset(&Adaptive_B.Su[i_2 * 45 + 3], 0, 42U * sizeof(real_T));
  }

  for (i_2 = 0; i_2 < 4; i_2++) {
    b_Hv_tmp = i_2 << 2;
    AA[b_Hv_tmp] = b_A[b_Hv_tmp + 16];
    AA[1 + b_Hv_tmp] = b_A[b_Hv_tmp + 17];
    AA[2 + b_Hv_tmp] = b_A[b_Hv_tmp + 18];
    AA[3 + b_Hv_tmp] = b_A[b_Hv_tmp + 19];
  }

  for (i_2 = 0; i_2 < 52; i_2++) {
    b_Hv_tmp = (i_2 + 4) << 2;
    AA[b_Hv_tmp] = 0.0;
    AA[1 + b_Hv_tmp] = 0.0;
    AA[2 + b_Hv_tmp] = 0.0;
    AA[3 + b_Hv_tmp] = 0.0;
  }

  for (i = 0; i < 14; i++) {
    i_0 = (int8_T)((i + 1) * 3 + 1);
    rows[0] = i_0;
    rows[1] = (int8_T)(1 + i_0);
    rows[2] = (int8_T)(2 + i_0);
    for (i_2 = 0; i_2 < 3; i_2++) {
      for (i_1 = 0; i_1 < 2; i_1++) {
        b_Hv_tmp = (rows[i_2] + 45 * i_1) - 1;
        b_Su1[b_Hv_tmp] = 0.0;
        b_C_tmp = (i + 2) * 12 + i_2;
        b_Su1_tmp = ((i + 1) << 3) + (i_1 << 2);
        b_Su1[b_Hv_tmp] += b_C[b_C_tmp] * Bu[b_Su1_tmp];
        b_Su1[b_Hv_tmp] += b_C[b_C_tmp + 3] * Bu[b_Su1_tmp + 1];
        b_Su1[b_Hv_tmp] += b_C[b_C_tmp + 6] * Bu[b_Su1_tmp + 2];
        b_Su1[b_Hv_tmp] += b_C[b_C_tmp + 9] * Bu[b_Su1_tmp + 3];
      }
    }

    i_1 = (i + 1) << 1;
    for (i_2 = 0; i_2 < 2; i_2++) {
      b_Hv_tmp = 45 * (i_2 + i_1);
      Adaptive_B.Su[(i_0 + b_Hv_tmp) - 1] = b_Su1[(45 * i_2 + i_0) - 1];
      Adaptive_B.Su[(rows[1] + b_Hv_tmp) - 1] = b_Su1[(45 * i_2 + rows[1]) - 1];
      Adaptive_B.Su[(rows[2] + b_Hv_tmp) - 1] = b_Su1[(45 * i_2 + rows[2]) - 1];
    }

    b_Su1_tmp = (int32_T)(((-1.0 - ((2.0 + (real_T)i) - 1.0)) + 1.0) / -1.0);
    for (b_j = 0; b_j < b_Su1_tmp; b_j++) {
      AA_tmp = i - b_j;
      i_1 = AA_tmp << 2;
      for (i_2 = 0; i_2 < 4; i_2++) {
        b_Hv_tmp = (i_2 + i_1) << 2;
        b_C_tmp = i_2 << 2;
        AA_0[b_C_tmp] = AA[b_Hv_tmp];
        AA_0[1 + b_C_tmp] = AA[b_Hv_tmp + 1];
        AA_0[2 + b_C_tmp] = AA[b_Hv_tmp + 2];
        AA_0[3 + b_C_tmp] = AA[b_Hv_tmp + 3];
      }

      for (i_2 = 0; i_2 < 3; i_2++) {
        for (i_1 = 0; i_1 < 4; i_1++) {
          b_Hv_tmp = i_2 + 3 * i_1;
          b_C_0[b_Hv_tmp] = 0.0;
          b_C_tmp = (i + 2) * 12 + i_2;
          b_C_tmp_0 = i_1 << 2;
          b_C_0[b_Hv_tmp] += b_C[b_C_tmp] * AA_0[b_C_tmp_0];
          b_C_0[b_Hv_tmp] += b_C[b_C_tmp + 3] * AA_0[b_C_tmp_0 + 1];
          b_C_0[b_Hv_tmp] += b_C[b_C_tmp + 6] * AA_0[b_C_tmp_0 + 2];
          b_C_0[b_Hv_tmp] += b_C[b_C_tmp + 9] * AA_0[b_C_tmp_0 + 3];
        }

        for (i_1 = 0; i_1 < 2; i_1++) {
          b_Hv_tmp = (i_1 << 2) + (AA_tmp << 3);
          b_C_1[i_2 + 3 * i_1] = (((Bu[b_Hv_tmp + 1] * b_C_0[i_2 + 3] +
            Bu[b_Hv_tmp] * b_C_0[i_2]) + Bu[b_Hv_tmp + 2] * b_C_0[i_2 + 6]) +
            Bu[b_Hv_tmp + 3] * b_C_0[i_2 + 9]) + b_Su1[(45 * i_1 + rows[i_2]) -
            1];
        }
      }

      for (i_2 = 0; i_2 < 2; i_2++) {
        b_Su1[(i_0 + 45 * i_2) - 1] = b_C_1[3 * i_2];
        b_Su1[(rows[1] + 45 * i_2) - 1] = b_C_1[3 * i_2 + 1];
        b_Su1[(rows[2] + 45 * i_2) - 1] = b_C_1[3 * i_2 + 2];
      }

      AA_tmp <<= 1;
      for (i_2 = 0; i_2 < 2; i_2++) {
        b_Hv_tmp = 45 * (i_2 + AA_tmp);
        Adaptive_B.Su[(i_0 + b_Hv_tmp) - 1] = b_Su1[(45 * i_2 + i_0) - 1];
        Adaptive_B.Su[(rows[1] + b_Hv_tmp) - 1] = b_Su1[(45 * i_2 + rows[1]) - 1];
        Adaptive_B.Su[(rows[2] + b_Hv_tmp) - 1] = b_Su1[(45 * i_2 + rows[2]) - 1];
      }
    }

    b_Hv_tmp = (i + 2) * 3;
    b_C_tmp = 45 * (i + 2);
    b_Hv[(i_0 + b_C_tmp) - 1] = Dv[b_Hv_tmp];
    b_Hv[(rows[1] + b_C_tmp) - 1] = Dv[b_Hv_tmp + 1];
    b_Hv[(rows[2] + b_C_tmp) - 1] = Dv[b_Hv_tmp + 2];
    i_1 = i + 1;
    for (i_2 = 0; i_2 < 3; i_2++) {
      b_Hv_tmp = (rows[i_2] + 45 * i_1) - 1;
      b_Hv[b_Hv_tmp] = 0.0;
      b_C_tmp = (i + 2) * 12 + i_2;
      b_Su1_tmp = (i + 1) << 2;
      b_Hv[b_Hv_tmp] += b_C[b_C_tmp] * Bv[b_Su1_tmp];
      b_Hv[b_Hv_tmp] += b_C[b_C_tmp + 3] * Bv[b_Su1_tmp + 1];
      b_Hv[b_Hv_tmp] += b_C[b_C_tmp + 6] * Bv[b_Su1_tmp + 2];
      b_Hv[b_Hv_tmp] += b_C[b_C_tmp + 9] * Bv[b_Su1_tmp + 3];
    }

    for (b_Su1_tmp = 0; b_Su1_tmp <= i; b_Su1_tmp++) {
      b_j = b_Su1_tmp << 2;
      for (i_2 = 0; i_2 < 4; i_2++) {
        b_Hv_tmp = (i_2 + b_j) << 2;
        b_C_tmp = i_2 << 2;
        AA_0[b_C_tmp] = AA[b_Hv_tmp];
        AA_0[1 + b_C_tmp] = AA[b_Hv_tmp + 1];
        AA_0[2 + b_C_tmp] = AA[b_Hv_tmp + 2];
        AA_0[3 + b_C_tmp] = AA[b_Hv_tmp + 3];
      }

      for (i_2 = 0; i_2 < 3; i_2++) {
        b_Hv[(rows[i_2] + 45 * b_Su1_tmp) - 1] = 0.0;
        for (i_1 = 0; i_1 < 4; i_1++) {
          b_Hv_tmp = i_2 + 3 * i_1;
          b_C_0[b_Hv_tmp] = 0.0;
          b_C_tmp = (i + 2) * 12 + i_2;
          b_C_tmp_0 = i_1 << 2;
          b_C_0[b_Hv_tmp] += b_C[b_C_tmp] * AA_0[b_C_tmp_0];
          b_C_0[b_Hv_tmp] += b_C[b_C_tmp + 3] * AA_0[b_C_tmp_0 + 1];
          b_C_0[b_Hv_tmp] += b_C[b_C_tmp + 6] * AA_0[b_C_tmp_0 + 2];
          b_C_0[b_Hv_tmp] += b_C[b_C_tmp + 9] * AA_0[b_C_tmp_0 + 3];
          b_Hv[(rows[i_2] + 45 * b_Su1_tmp) - 1] += b_C_0[b_Hv_tmp] * Bv[b_j +
            i_1];
        }
      }
    }

    for (i_2 = 0; i_2 < 3; i_2++) {
      for (i_1 = 0; i_1 < 4; i_1++) {
        b_Hv_tmp = i_2 + 3 * i_1;
        b_C_0[b_Hv_tmp] = 0.0;
        b_C_tmp = (i + 2) * 12 + i_2;
        b_C_tmp_0 = i_1 << 2;
        b_C_0[b_Hv_tmp] += b_C[b_C_tmp] * AA[b_C_tmp_0];
        b_C_0[b_Hv_tmp] += b_C[b_C_tmp + 3] * AA[b_C_tmp_0 + 1];
        b_C_0[b_Hv_tmp] += b_C[b_C_tmp + 6] * AA[b_C_tmp_0 + 2];
        b_C_0[b_Hv_tmp] += b_C[b_C_tmp + 9] * AA[b_C_tmp_0 + 3];
      }

      for (i_1 = 0; i_1 < 4; i_1++) {
        b_Hv_tmp = (rows[i_2] + 45 * i_1) - 1;
        b_Sx[b_Hv_tmp] = 0.0;
        b_C_tmp = i_1 << 2;
        b_Sx[b_Hv_tmp] += b_A[b_C_tmp] * b_C_0[i_2];
        b_Sx[b_Hv_tmp] += b_A[b_C_tmp + 1] * b_C_0[i_2 + 3];
        b_Sx[b_Hv_tmp] += b_A[b_C_tmp + 2] * b_C_0[i_2 + 6];
        b_Sx[b_Hv_tmp] += b_A[b_C_tmp + 3] * b_C_0[i_2 + 9];
      }
    }

    if (2 + i < 15) {
      for (b_Su1_tmp = 0; b_Su1_tmp <= i; b_Su1_tmp++) {
        b_j = b_Su1_tmp << 2;
        for (i_2 = 0; i_2 < 4; i_2++) {
          b_Hv_tmp = (i_2 + b_j) << 2;
          b_C_tmp = i_2 << 2;
          AA_0[b_C_tmp] = AA[b_Hv_tmp];
          AA_0[1 + b_C_tmp] = AA[b_Hv_tmp + 1];
          AA_0[2 + b_C_tmp] = AA[b_Hv_tmp + 2];
          AA_0[3 + b_C_tmp] = AA[b_Hv_tmp + 3];
        }

        for (i_2 = 0; i_2 < 4; i_2++) {
          for (i_1 = 0; i_1 < 4; i_1++) {
            b_Hv_tmp = i_2 + ((i_1 + b_j) << 2);
            AA[b_Hv_tmp] = 0.0;
            b_C_tmp = ((i + 2) << 4) + i_2;
            AA_tmp = i_1 << 2;
            AA[b_Hv_tmp] += b_A[b_C_tmp] * AA_0[AA_tmp];
            AA[b_Hv_tmp] += b_A[b_C_tmp + 4] * AA_0[AA_tmp + 1];
            AA[b_Hv_tmp] += b_A[b_C_tmp + 8] * AA_0[AA_tmp + 2];
            AA[b_Hv_tmp] += b_A[b_C_tmp + 12] * AA_0[AA_tmp + 3];
          }
        }
      }

      i_1 = (i + 1) << 2;
      for (i_2 = 0; i_2 < 4; i_2++) {
        b_Hv_tmp = ((i + 2) << 4) + (i_2 << 2);
        b_C_tmp = (i_2 + i_1) << 2;
        AA[b_C_tmp] = b_A[b_Hv_tmp];
        AA[1 + b_C_tmp] = b_A[b_Hv_tmp + 1];
        AA[2 + b_C_tmp] = b_A[b_Hv_tmp + 2];
        AA[3 + b_C_tmp] = b_A[b_Hv_tmp + 3];
      }
    }
  }

  for (i_2 = 0; i_2 < 8; i_2++) {
    for (i_1 = 0; i_1 < 45; i_1++) {
      i = i_1 + 45 * i_2;
      b_SuJm[i] = 0.0;
      for (b_Hv_tmp = 0; b_Hv_tmp < 30; b_Hv_tmp++) {
        b_SuJm[i] += Adaptive_B.Su[45 * b_Hv_tmp + i_1] * b_Jm[30 * i_2 +
          b_Hv_tmp];
      }
    }
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_updateWeights(real_T W[3], const real_T b_signal[3], real_T
  ZERO)
{
  if (b_signal[0] < ZERO) {
    W[0] = ZERO;
  } else {
    W[0] = b_signal[0] * b_signal[0];
  }

  if (b_signal[1] < ZERO) {
    W[1] = ZERO;
  } else {
    W[1] = b_signal[1] * b_signal[1];
  }

  if (b_signal[2] < ZERO) {
    W[2] = ZERO;
  } else {
    W[2] = b_signal[2] * b_signal[2];
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_updateWeights_e(real_T W[2], const real_T b_signal[2],
  real_T ZERO)
{
  if (b_signal[0] < ZERO) {
    W[0] = ZERO;
  } else {
    W[0] = b_signal[0] * b_signal[0];
  }

  if (b_signal[1] < ZERO) {
    W[1] = ZERO;
  } else {
    W[1] = b_signal[1] * b_signal[1];
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_eye_o(real_T b_I[4])
{
  b_I[1] = 0.0;
  b_I[2] = 0.0;
  b_I[0] = 1.0;
  b_I[3] = 1.0;
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_kron(const real_T b_A[225], const real_T b_B[4], real_T K
  [900])
{
  int32_T kidx;
  int32_T b_j1;
  int32_T j2;
  int32_T i1;
  int32_T K_tmp;
  real_T K_tmp_0;
  kidx = -1;
  for (b_j1 = 0; b_j1 < 15; b_j1++) {
    for (j2 = 0; j2 < 2; j2++) {
      for (i1 = 0; i1 < 15; i1++) {
        kidx++;
        K_tmp = j2 << 1;
        K_tmp_0 = b_A[15 * b_j1 + i1];
        K[kidx] = K_tmp_0 * b_B[K_tmp];
        kidx++;
        K[kidx] = K_tmp_0 * b_B[K_tmp + 1];
      }
    }
  }
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_WtMult(const real_T W[3], const real_T M[360], real_T nwt,
  real_T WM[360])
{
  int16_T ixw;
  int32_T i;
  real_T W_0;
  int32_T i_0;
  int32_T WM_tmp;
  ixw = 1;
  for (i = 0; i < 45; i++) {
    W_0 = W[ixw - 1];
    for (i_0 = 0; i_0 < 8; i_0++) {
      WM_tmp = 45 * i_0 + i;
      WM[WM_tmp] = M[WM_tmp] * W_0;
    }

    i_0 = ixw + 1;
    if (i_0 > 32767) {
      i_0 = 32767;
    }

    ixw = (int16_T)i_0;
    if ((int16_T)i_0 > 3) {
      W_0 = rt_roundd_snf(3.0 - nwt);
      if (W_0 < 32768.0) {
        if (W_0 >= -32768.0) {
          ixw = (int16_T)W_0;
        } else {
          ixw = MIN_int16_T;
        }
      } else {
        ixw = MAX_int16_T;
      }

      i_0 = ixw + 1;
      if (i_0 > 32767) {
        i_0 = 32767;
      }

      ixw = (int16_T)i_0;
    }
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_WtMult_a(const real_T W[2], const real_T M[240], real_T nwt,
  real_T WM[240])
{
  int16_T ixw;
  int32_T i;
  real_T W_0;
  int32_T i_0;
  int32_T WM_tmp;
  ixw = 1;
  for (i = 0; i < 30; i++) {
    W_0 = W[ixw - 1];
    for (i_0 = 0; i_0 < 8; i_0++) {
      WM_tmp = 30 * i_0 + i;
      WM[WM_tmp] = M[WM_tmp] * W_0;
    }

    i_0 = ixw + 1;
    if (i_0 > 32767) {
      i_0 = 32767;
    }

    ixw = (int16_T)i_0;
    if ((int16_T)i_0 > 2) {
      W_0 = rt_roundd_snf(2.0 - nwt);
      if (W_0 < 32768.0) {
        if (W_0 >= -32768.0) {
          ixw = (int16_T)W_0;
        } else {
          ixw = MIN_int16_T;
        }
      } else {
        ixw = MAX_int16_T;
      }

      i_0 = ixw + 1;
      if (i_0 > 32767) {
        i_0 = 32767;
      }

      ixw = (int16_T)i_0;
    }
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_mpc_calculatehessian(const real_T b_Wy[3], const real_T
  b_Wu[2], const real_T b_Wdu[2], const real_T b_SuJm[360], const real_T I2Jm
  [240], const real_T b_Jm[240], const real_T b_I1[60], const real_T b_Su1[90],
  const real_T b_Sx[180], const real_T b_Hv[720], real_T nmv, real_T b_ny,
  real_T b_H[64], real_T b_Ku1[16], real_T b_Kut[240], real_T b_Kx[32], real_T
  b_Kv[128], real_T b_Kr[360])
{
  real_T tmp[240];
  real_T b_SuJm_0[64];
  real_T b_Jm_0[64];
  real_T b_Su1_0[16];
  real_T b_I1_0[16];
  int32_T i;
  int32_T i_0;
  int32_T i_1;
  real_T tmp_0;
  int32_T b_SuJm_tmp;
  int32_T tmp_1;
  int32_T tmp_2;
  Adaptive_WtMult(b_Wy, b_SuJm, b_ny, b_Kr);
  Adaptive_WtMult_a(b_Wu, I2Jm, nmv, b_Kut);
  Adaptive_WtMult_a(b_Wdu, b_Jm, nmv, tmp);
  for (i = 0; i < 8; i++) {
    for (i_0 = 0; i_0 < 8; i_0++) {
      b_SuJm_tmp = i + (i_0 << 3);
      b_SuJm_0[b_SuJm_tmp] = 0.0;
      for (i_1 = 0; i_1 < 45; i_1++) {
        b_SuJm_0[b_SuJm_tmp] += b_SuJm[45 * i + i_1] * b_Kr[45 * i_0 + i_1];
      }

      b_Jm_0[b_SuJm_tmp] = 0.0;
      tmp_0 = 0.0;
      for (i_1 = 0; i_1 < 30; i_1++) {
        tmp_1 = 30 * i + i_1;
        tmp_2 = 30 * i_0 + i_1;
        tmp_0 += I2Jm[tmp_1] * b_Kut[tmp_2];
        b_Jm_0[b_SuJm_tmp] = b_Jm[tmp_1] * tmp[tmp_2] + b_Jm_0[(i_0 << 3) + i];
      }

      b_H[b_SuJm_tmp] = (b_SuJm_0[b_SuJm_tmp] + b_Jm_0[b_SuJm_tmp]) + tmp_0;
    }
  }

  for (i = 0; i < 2; i++) {
    for (i_0 = 0; i_0 < 8; i_0++) {
      b_SuJm_tmp = i + (i_0 << 1);
      b_Su1_0[b_SuJm_tmp] = 0.0;
      for (i_1 = 0; i_1 < 45; i_1++) {
        b_Su1_0[b_SuJm_tmp] += b_Su1[45 * i + i_1] * b_Kr[45 * i_0 + i_1];
      }

      b_I1_0[b_SuJm_tmp] = 0.0;
      for (i_1 = 0; i_1 < 30; i_1++) {
        b_I1_0[b_SuJm_tmp] += b_I1[30 * i + i_1] * b_Kut[30 * i_0 + i_1];
      }
    }
  }

  for (i = 0; i < 16; i++) {
    b_Ku1[i] = b_Su1_0[i] + b_I1_0[i];
  }

  for (i = 0; i < 240; i++) {
    b_Kut[i] = -b_Kut[i];
  }

  for (i = 0; i < 4; i++) {
    for (i_0 = 0; i_0 < 8; i_0++) {
      b_SuJm_tmp = i + (i_0 << 2);
      b_Kx[b_SuJm_tmp] = 0.0;
      for (i_1 = 0; i_1 < 45; i_1++) {
        b_Kx[b_SuJm_tmp] += b_Sx[45 * i + i_1] * b_Kr[45 * i_0 + i_1];
      }
    }
  }

  for (i = 0; i < 16; i++) {
    for (i_0 = 0; i_0 < 8; i_0++) {
      b_SuJm_tmp = i + (i_0 << 4);
      b_Kv[b_SuJm_tmp] = 0.0;
      for (i_1 = 0; i_1 < 45; i_1++) {
        b_Kv[b_SuJm_tmp] += b_Hv[45 * i + i_1] * b_Kr[45 * i_0 + i_1];
      }
    }
  }

  for (i = 0; i < 360; i++) {
    b_Kr[i] = -b_Kr[i];
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static int32_T Adaptive_xpotrf(real_T b_A[81])
{
  int32_T info;
  int32_T jj;
  real_T ajj;
  int32_T j;
  int32_T ix;
  int32_T iy;
  int32_T k;
  real_T c;
  int32_T b_iy;
  int32_T e;
  int32_T ia;
  boolean_T exitg1;
  info = 0;
  j = 1;
  exitg1 = false;
  while ((!exitg1) && (j - 1 < 9)) {
    jj = ((j - 1) * 9 + j) - 1;
    ajj = 0.0;
    if (j - 1 >= 1) {
      ix = j;
      iy = j;
      for (k = 0; k <= j - 2; k++) {
        ajj += b_A[ix - 1] * b_A[iy - 1];
        ix += 9;
        iy += 9;
      }
    }

    ajj = b_A[jj] - ajj;
    if (ajj > 0.0) {
      ajj = sqrt(ajj);
      b_A[jj] = ajj;
      if (j < 9) {
        if (j - 1 != 0) {
          ix = j;
          iy = ((j - 2) * 9 + j) + 1;
          for (k = j + 1; k <= iy; k += 9) {
            c = -b_A[ix - 1];
            b_iy = jj + 1;
            e = (k - j) + 8;
            for (ia = k; ia <= e; ia++) {
              b_A[b_iy] += b_A[ia - 1] * c;
              b_iy++;
            }

            ix += 9;
          }
        }

        ajj = 1.0 / ajj;
        ix = (jj - j) + 10;
        for (jj++; jj < ix; jj++) {
          b_A[jj] *= ajj;
        }
      }

      j++;
    } else {
      b_A[jj] = ajj;
      info = j;
      exitg1 = true;
    }
  }

  return info;
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_mpc_checkhessian(real_T b_H[81], real_T L[81], real_T *BadH)
{
  real_T normH;
  real_T d[9];
  int32_T idx;
  real_T s;
  int8_T b_I[81];
  int32_T b_idx;
  int32_T f_k;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  *BadH = 0.0;
  memcpy(&L[0], &b_H[0], 81U * sizeof(real_T));
  idx = Adaptive_xpotrf(L);
  guard1 = false;
  if (idx == 0) {
    for (idx = 0; idx < 9; idx++) {
      d[idx] = L[9 * idx + idx];
    }

    if (!rtIsNaN(d[0])) {
      idx = 1;
    } else {
      idx = 0;
      b_idx = 2;
      exitg2 = false;
      while ((!exitg2) && (b_idx < 10)) {
        if (!rtIsNaN(d[b_idx - 1])) {
          idx = b_idx;
          exitg2 = true;
        } else {
          b_idx++;
        }
      }
    }

    if (idx == 0) {
      normH = d[0];
    } else {
      normH = d[idx - 1];
      while (idx + 1 < 10) {
        if (normH > d[idx]) {
          normH = d[idx];
        }

        idx++;
      }
    }

    if (normH > 1.4901161193847656E-7) {
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    normH = 0.0;
    idx = 0;
    exitg2 = false;
    while ((!exitg2) && (idx < 9)) {
      s = 0.0;
      for (b_idx = 0; b_idx < 9; b_idx++) {
        s += fabs(b_H[9 * b_idx + idx]);
      }

      if (rtIsNaN(s)) {
        normH = (rtNaN);
        exitg2 = true;
      } else {
        if (s > normH) {
          normH = s;
        }

        idx++;
      }
    }

    if (normH >= 1.0E+10) {
      *BadH = 2.0;
    } else {
      idx = 0;
      exitg1 = false;
      while ((!exitg1) && (idx <= 4)) {
        memset(&b_I[0], 0, 81U * sizeof(int8_T));
        for (b_idx = 0; b_idx < 9; b_idx++) {
          b_I[b_idx + 9 * b_idx] = 1;
        }

        normH = rt_powd_snf(10.0, (real_T)idx) * 1.4901161193847656E-7;
        for (b_idx = 0; b_idx < 81; b_idx++) {
          s = normH * (real_T)b_I[b_idx] + b_H[b_idx];
          L[b_idx] = s;
          b_H[b_idx] = s;
        }

        b_idx = Adaptive_xpotrf(L);
        guard2 = false;
        if (b_idx == 0) {
          for (b_idx = 0; b_idx < 9; b_idx++) {
            d[b_idx] = L[9 * b_idx + b_idx];
          }

          if (!rtIsNaN(d[0])) {
            b_idx = 1;
          } else {
            b_idx = 0;
            f_k = 2;
            exitg2 = false;
            while ((!exitg2) && (f_k < 10)) {
              if (!rtIsNaN(d[f_k - 1])) {
                b_idx = f_k;
                exitg2 = true;
              } else {
                f_k++;
              }
            }
          }

          if (b_idx == 0) {
            normH = d[0];
          } else {
            normH = d[b_idx - 1];
            while (b_idx + 1 < 10) {
              if (normH > d[b_idx]) {
                normH = d[b_idx];
              }

              b_idx++;
            }
          }

          if (normH > 1.4901161193847656E-7) {
            *BadH = 1.0;
            exitg1 = true;
          } else {
            guard2 = true;
          }
        } else {
          guard2 = true;
        }

        if (guard2) {
          *BadH = 3.0;
          idx++;
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_eye_oi(real_T b_I[81])
{
  int32_T k;
  memset(&b_I[0], 0, 81U * sizeof(real_T));
  for (k = 0; k < 9; k++) {
    b_I[k + 9 * k] = 1.0;
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_trisolve(const real_T b_A[81], real_T b_B[81])
{
  int32_T jBcol;
  int32_T kAcol;
  int32_T j;
  int32_T k;
  int32_T i;
  int32_T tmp;
  int32_T tmp_0;
  for (j = 0; j < 9; j++) {
    jBcol = 9 * j;
    for (k = 0; k < 9; k++) {
      kAcol = 9 * k;
      tmp = k + jBcol;
      if (b_B[tmp] != 0.0) {
        b_B[tmp] /= b_A[k + kAcol];
        for (i = k + 2; i < 10; i++) {
          tmp_0 = (i + jBcol) - 1;
          b_B[tmp_0] -= b_A[(i + kAcol) - 1] * b_B[tmp];
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_linsolve(const real_T b_A[81], const real_T b_B[81], real_T
  b_C[81])
{
  int32_T j;
  for (j = 0; j < 9; j++) {
    memcpy(&b_C[j * 9], &b_B[j * 9], 9U * sizeof(real_T));
  }

  Adaptive_trisolve(b_A, b_C);
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_Unconstrained(const real_T b_Hinv[81], const real_T f[9],
  real_T x[9], int16_T n)
{
  int32_T i;
  real_T b_Hinv_0;
  int32_T i_0;
  int32_T i_1;
  for (i = 1; i - 1 < n; i++) {
    i_0 = (int16_T)i;
    b_Hinv_0 = 0.0;
    for (i_1 = 0; i_1 < 9; i_1++) {
      b_Hinv_0 += -b_Hinv[(9 * i_1 + i_0) - 1] * f[i_1];
    }

    x[(int16_T)i - 1] = b_Hinv_0;
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static real_T Adaptive_norm(const real_T x[9])
{
  real_T y;
  real_T scale;
  real_T absxk;
  real_T t;
  int32_T k;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  for (k = 0; k < 9; k++) {
    absxk = fabs(x[k]);
    if (absxk > scale) {
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_abs(const real_T x[9], real_T y[9])
{
  int32_T k;
  for (k = 0; k < 9; k++) {
    y[k] = fabs(x[k]);
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_abs_e(const real_T x[16], real_T y[16])
{
  int32_T k;
  for (k = 0; k < 16; k++) {
    y[k] = fabs(x[k]);
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static real_T Adaptive_xnrm2(int32_T n, const real_T x[81], int32_T ix0)
{
  real_T y;
  real_T scale;
  int32_T kend;
  real_T absxk;
  real_T t;
  int32_T k;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T a;
  a = fabs(u0);
  y = fabs(u1);
  if (a < y) {
    a /= y;
    y *= sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = sqrt(y * y + 1.0) * a;
  } else {
    if (!rtIsNaN(y)) {
      y = a * 1.4142135623730951;
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_xgemv(int32_T m, int32_T n, const real_T b_A[81], int32_T
  ia0, const real_T x[81], int32_T ix0, real_T y[9])
{
  int32_T ix;
  real_T c;
  int32_T b_iy;
  int32_T b;
  int32_T iac;
  int32_T d;
  int32_T ia;
  if ((m != 0) && (n != 0)) {
    for (b_iy = 0; b_iy < n; b_iy++) {
      y[b_iy] = 0.0;
    }

    b_iy = 0;
    b = (n - 1) * 9 + ia0;
    for (iac = ia0; iac <= b; iac += 9) {
      ix = ix0;
      c = 0.0;
      d = (iac + m) - 1;
      for (ia = iac; ia <= d; ia++) {
        c += b_A[ia - 1] * x[ix - 1];
        ix++;
      }

      y[b_iy] += c;
      b_iy++;
    }
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_xgerc(int32_T m, int32_T n, real_T alpha1, int32_T ix0,
  const real_T y[9], real_T b_A[81], int32_T ia0)
{
  int32_T jA;
  int32_T jy;
  real_T temp;
  int32_T ix;
  int32_T j;
  int32_T b;
  int32_T ijA;
  if (!(alpha1 == 0.0)) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 0; j < n; j++) {
      if (y[jy] != 0.0) {
        temp = y[jy] * alpha1;
        ix = ix0;
        b = m + jA;
        for (ijA = jA; ijA < b; ijA++) {
          b_A[ijA] += b_A[ix - 1] * temp;
          ix++;
        }
      }

      jy++;
      jA += 9;
    }
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_xgeqrf(real_T b_A[81], real_T tau[9])
{
  real_T work[9];
  int32_T i_i;
  real_T b_atmp;
  int32_T i;
  real_T xnorm;
  int32_T knt;
  int32_T lastv;
  int32_T lastc;
  int32_T coltop;
  int32_T ia;
  int32_T exitg1;
  boolean_T exitg2;
  memset(&work[0], 0, 9U * sizeof(real_T));
  for (i = 0; i < 9; i++) {
    i_i = i * 9 + i;
    if (1 + i < 9) {
      b_atmp = b_A[i_i];
      tau[i] = 0.0;
      xnorm = Adaptive_xnrm2(8 - i, b_A, i_i + 2);
      if (xnorm != 0.0) {
        xnorm = rt_hypotd_snf(b_A[i_i], xnorm);
        if (b_A[i_i] >= 0.0) {
          xnorm = -xnorm;
        }

        if (fabs(xnorm) < 1.0020841800044864E-292) {
          knt = -1;
          lastv = i_i - i;
          do {
            knt++;
            for (lastc = i_i + 1; lastc < lastv + 9; lastc++) {
              b_A[lastc] *= 9.9792015476736E+291;
            }

            xnorm *= 9.9792015476736E+291;
            b_atmp *= 9.9792015476736E+291;
          } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

          xnorm = rt_hypotd_snf(b_atmp, Adaptive_xnrm2(8 - i, b_A, i_i + 2));
          if (b_atmp >= 0.0) {
            xnorm = -xnorm;
          }

          tau[i] = (xnorm - b_atmp) / xnorm;
          b_atmp = 1.0 / (b_atmp - xnorm);
          for (lastc = i_i + 1; lastc < lastv + 9; lastc++) {
            b_A[lastc] *= b_atmp;
          }

          for (lastv = 0; lastv <= knt; lastv++) {
            xnorm *= 1.0020841800044864E-292;
          }

          b_atmp = xnorm;
        } else {
          tau[i] = (xnorm - b_A[i_i]) / xnorm;
          b_atmp = 1.0 / (b_A[i_i] - xnorm);
          knt = i_i - i;
          for (lastv = i_i + 1; lastv < knt + 9; lastv++) {
            b_A[lastv] *= b_atmp;
          }

          b_atmp = xnorm;
        }
      }

      b_A[i_i] = b_atmp;
      b_atmp = b_A[i_i];
      b_A[i_i] = 1.0;
      knt = ((1 + i) * 9 + i) + 1;
      if (tau[i] != 0.0) {
        lastv = 9 - i;
        lastc = i_i - i;
        while ((lastv > 0) && (b_A[lastc + 8] == 0.0)) {
          lastv--;
          lastc--;
        }

        lastc = 8 - i;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          coltop = (lastc - 1) * 9 + knt;
          ia = coltop;
          do {
            exitg1 = 0;
            if (ia <= (coltop + lastv) - 1) {
              if (b_A[ia - 1] != 0.0) {
                exitg1 = 1;
              } else {
                ia++;
              }
            } else {
              lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        lastc = 0;
      }

      if (lastv > 0) {
        Adaptive_xgemv(lastv, lastc, b_A, knt, b_A, i_i + 1, work);
        Adaptive_xgerc(lastv, lastc, -tau[i], i_i + 1, work, b_A, knt);
      }

      b_A[i_i] = b_atmp;
    } else {
      tau[8] = 0.0;
    }
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_qr(const real_T b_A[81], real_T Q[81], real_T R[81])
{
  real_T c_A[81];
  real_T tau[9];
  int32_T d_i;
  int32_T itau;
  real_T work[9];
  int32_T iaii;
  int32_T lastv;
  int32_T lastc;
  int32_T coltop;
  int32_T ia;
  int32_T exitg1;
  boolean_T exitg2;
  memcpy(&c_A[0], &b_A[0], 81U * sizeof(real_T));
  Adaptive_xgeqrf(c_A, tau);
  itau = 8;
  for (d_i = 0; d_i < 9; d_i++) {
    for (iaii = 0; iaii <= d_i; iaii++) {
      R[iaii + 9 * d_i] = c_A[9 * d_i + iaii];
    }

    for (iaii = d_i; iaii + 2 < 10; iaii++) {
      R[(iaii + 9 * d_i) + 1] = 0.0;
    }

    work[d_i] = 0.0;
  }

  for (d_i = 8; d_i >= 0; d_i--) {
    iaii = (d_i * 9 + d_i) + 1;
    if (d_i + 1 < 9) {
      c_A[iaii - 1] = 1.0;
      if (tau[itau] != 0.0) {
        lastv = 9 - d_i;
        lastc = (iaii - d_i) + 7;
        while ((lastv > 0) && (c_A[lastc] == 0.0)) {
          lastv--;
          lastc--;
        }

        lastc = 8 - d_i;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          coltop = ((lastc - 1) * 9 + iaii) + 8;
          ia = coltop;
          do {
            exitg1 = 0;
            if (ia + 1 <= coltop + lastv) {
              if (c_A[ia] != 0.0) {
                exitg1 = 1;
              } else {
                ia++;
              }
            } else {
              lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        lastc = 0;
      }

      if (lastv > 0) {
        Adaptive_xgemv(lastv, lastc, c_A, iaii + 9, c_A, iaii, work);
        Adaptive_xgerc(lastv, lastc, -tau[itau], iaii, work, c_A, iaii + 9);
      }

      lastv = (iaii - d_i) + 8;
      for (lastc = iaii; lastc < lastv; lastc++) {
        c_A[lastc] *= -tau[itau];
      }
    }

    c_A[iaii - 1] = 1.0 - tau[itau];
    for (lastv = 0; lastv < d_i; lastv++) {
      c_A[(iaii - lastv) - 2] = 0.0;
    }

    itau--;
  }

  for (itau = 0; itau < 9; itau++) {
    memcpy(&Q[itau * 9], &c_A[itau * 9], 9U * sizeof(real_T));
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static real_T Adaptive_KWIKfactor(const real_T b_Ac[144], const int16_T iC[16],
  int16_T nA, const real_T b_Linv[81], real_T RLinv[81], real_T b_D[81], real_T
  b_H[81], int16_T n)
{
  real_T Status;
  real_T TL[81];
  real_T QQ[81];
  real_T RR[81];
  int32_T i;
  int32_T b_i;
  int16_T b_j;
  int32_T e_i;
  int16_T c_k;
  int32_T f_i;
  real_T b_Linv_0;
  int32_T j;
  int32_T i_0;
  int32_T i_1;
  int32_T exitg1;
  int32_T exitg2;
  Status = 1.0;
  memset(&RLinv[0], 0, 81U * sizeof(real_T));
  i = 1;
  do {
    exitg1 = 0;
    i_0 = nA - 1;
    if (i - 1 <= i_0) {
      e_i = (int16_T)i - 1;
      for (i_0 = 0; i_0 < 9; i_0++) {
        b_i = i_0 + 9 * e_i;
        RLinv[b_i] = 0.0;
        for (i_1 = 0; i_1 < 9; i_1++) {
          RLinv[b_i] += b_Ac[((i_1 << 4) + iC[e_i]) - 1] * b_Linv[9 * i_1 + i_0];
        }
      }

      i++;
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  Adaptive_qr(RLinv, QQ, RR);
  b_i = 1;
  do {
    exitg1 = 0;
    if (b_i - 1 <= i_0) {
      if (fabs(RR[(((int16_T)b_i - 1) * 9 + (int16_T)b_i) - 1]) < 1.0E-12) {
        Status = -2.0;
        exitg1 = 1;
      } else {
        b_i++;
      }
    } else {
      i = 1;
      do {
        exitg2 = 0;
        b_i = n - 1;
        if (i - 1 <= b_i) {
          for (e_i = 1; e_i - 1 <= b_i; e_i++) {
            f_i = (int16_T)i;
            j = (int16_T)e_i;
            b_Linv_0 = 0.0;
            for (i_1 = 0; i_1 < 9; i_1++) {
              b_Linv_0 += b_Linv[(f_i - 1) * 9 + i_1] * QQ[(j - 1) * 9 + i_1];
            }

            TL[((int16_T)i + 9 * ((int16_T)e_i - 1)) - 1] = b_Linv_0;
          }

          i++;
        } else {
          exitg2 = 1;
        }
      } while (exitg2 == 0);

      memset(&RLinv[0], 0, 81U * sizeof(real_T));
      b_j = nA;
      while (b_j > 0) {
        i_1 = b_j - 1;
        i = 9 * i_1;
        e_i = (b_j + i) - 1;
        RLinv[e_i] = 1.0;
        for (c_k = b_j; c_k <= nA; c_k++) {
          j = ((c_k - 1) * 9 + b_j) - 1;
          RLinv[j] /= RR[e_i];
        }

        if (b_j > 1) {
          for (f_i = 1; f_i - 1 <= b_j - 2; f_i++) {
            for (c_k = b_j; c_k <= nA; c_k++) {
              e_i = (c_k - 1) * 9;
              j = (e_i + (int16_T)f_i) - 1;
              RLinv[j] -= RR[(i + (int16_T)f_i) - 1] * RLinv[(e_i + b_j) - 1];
            }
          }
        }

        b_j = (int16_T)i_1;
      }

      for (e_i = 1; e_i - 1 <= b_i; e_i++) {
        for (b_j = (int16_T)e_i; b_j <= n; b_j++) {
          i_1 = ((int16_T)e_i + 9 * (b_j - 1)) - 1;
          b_H[i_1] = 0.0;
          i = nA + 1;
          if (i > 32767) {
            i = 32767;
          }

          for (c_k = (int16_T)i; c_k <= n; c_k++) {
            i = (c_k - 1) * 9;
            b_H[i_1] -= TL[(i + (int16_T)e_i) - 1] * TL[(i + b_j) - 1];
          }

          b_H[(b_j + 9 * ((int16_T)e_i - 1)) - 1] = b_H[i_1];
        }
      }

      for (e_i = 1; e_i - 1 <= i_0; e_i++) {
        for (f_i = 1; f_i - 1 <= b_i; f_i++) {
          i_1 = ((int16_T)f_i + 9 * ((int16_T)e_i - 1)) - 1;
          b_D[i_1] = 0.0;
          for (b_j = (int16_T)e_i; b_j <= nA; b_j++) {
            i = (b_j - 1) * 9;
            b_D[i_1] += TL[(i + (int16_T)f_i) - 1] * RLinv[(i + (int16_T)e_i) -
              1];
          }
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Status;
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_DropConstraint(int16_T kDrop, int16_T iA[16], int16_T *nA,
  int16_T iC[16])
{
  int16_T i;
  int32_T tmp;
  iA[iC[kDrop - 1] - 1] = 0;
  if (kDrop < *nA) {
    tmp = *nA - 1;
    if (tmp < -32768) {
      tmp = -32768;
    }

    for (i = kDrop; i <= (int16_T)tmp; i++) {
      iC[i - 1] = iC[i];
    }
  }

  iC[*nA - 1] = 0;
  tmp = *nA - 1;
  if (tmp < -32768) {
    tmp = -32768;
  }

  *nA = (int16_T)tmp;
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static int16_T Adaptive_rdivide_helper(int16_T x, int16_T y)
{
  int16_T z;
  uint16_T b_y;
  uint16_T c_y;
  uint16_T q;
  int32_T tmp;
  switch (y) {
   case 0:
    if (x == 0) {
      z = 0;
    } else if (x < 0) {
      z = MIN_int16_T;
    } else {
      z = MAX_int16_T;
    }
    break;

   case 1:
    z = x;
    break;

   case -1:
    tmp = -x;
    if (tmp > 32767) {
      tmp = 32767;
    }

    z = (int16_T)tmp;
    break;

   default:
    if (x >= 0) {
      b_y = (uint16_T)x;
    } else if (x == -32768) {
      b_y = 32768U;
    } else {
      b_y = (uint16_T)-x;
    }

    if (y >= 0) {
      c_y = (uint16_T)y;
    } else if (y == -32768) {
      c_y = 32768U;
    } else {
      c_y = (uint16_T)-y;
    }

    q = (uint16_T)(c_y == 0U ? MAX_uint32_T : (uint32_T)b_y / c_y);
    b_y = (uint16_T)((uint32_T)b_y - (uint16_T)((uint32_T)q * c_y));
    if ((b_y > 0) && (b_y >= (int32_T)((uint32_T)c_y >> 1) + (c_y & 1))) {
      q++;
    }

    z = (int16_T)q;
    if ((x < 0) != (y < 0)) {
      z = (int16_T)-(int16_T)q;
    }
    break;
  }

  return z;
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_qpkwik(const real_T b_Linv[81], const real_T b_Hinv[81],
  const real_T f[9], const real_T b_Ac[144], const real_T b[16], int16_T iA[16],
  int16_T b_maxiter, real_T FeasTol, real_T x[9], real_T lambda[16], real_T
  *status)
{
  real_T r[9];
  real_T rMin;
  real_T RLinv[81];
  real_T b_D[81];
  real_T b_H[81];
  real_T U[81];
  real_T cTol[16];
  boolean_T cTolComputed;
  int16_T iC[16];
  int16_T nA;
  real_T Opt[18];
  real_T Rhs[18];
  boolean_T DualFeasible;
  boolean_T ColdReset;
  int16_T kDrop;
  real_T Xnorm0;
  real_T cMin;
  int16_T kNext;
  real_T cVal;
  real_T AcRow[9];
  real_T t;
  int32_T j;
  int32_T c_i;
  int32_T c_k;
  int32_T f_i;
  real_T varargin_1[16];
  int32_T idx;
  int32_T i;
  real_T b_Ac_0[9];
  int32_T tmp;
  int32_T U_tmp;
  int16_T tmp_0;
  int32_T exitg1;
  int32_T exitg2;
  int32_T exitg3;
  boolean_T exitg4;
  int32_T exitg5;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  *status = 1.0;
  memset(&lambda[0], 0, sizeof(real_T) << 4U);
  memset(&x[0], 0, 9U * sizeof(real_T));
  memset(&r[0], 0, 9U * sizeof(real_T));
  rMin = 0.0;
  cTolComputed = false;
  for (i = 0; i < 16; i++) {
    cTol[i] = 1.0;
    iC[i] = 0;
  }

  nA = 0;
  for (i = 0; i < 16; i++) {
    if (iA[i] == 1) {
      idx = nA + 1;
      if (idx > 32767) {
        idx = 32767;
      }

      nA = (int16_T)idx;
      iC[(int16_T)idx - 1] = (int16_T)(1 + i);
    }
  }

  guard1 = false;
  if (nA > 0) {
    memset(&Opt[0], 0, 18U * sizeof(real_T));
    for (i = 0; i < 9; i++) {
      Rhs[i] = f[i];
      Rhs[i + 9] = 0.0;
    }

    DualFeasible = false;
    idx = 3 * nA;
    if (idx > 32767) {
      idx = 32767;
    }

    ColdReset = false;
    do {
      exitg3 = 0;
      if ((!DualFeasible) && (nA > 0) && ((int32_T)*status <= b_maxiter)) {
        Xnorm0 = Adaptive_KWIKfactor(b_Ac, iC, nA, b_Linv, RLinv, b_D, b_H, 9);
        if (Xnorm0 < 0.0) {
          if (ColdReset) {
            *status = -2.0;
            exitg3 = 2;
          } else {
            nA = 0;
            for (i = 0; i < 16; i++) {
              iA[i] = 0;
              iC[i] = 0;
            }

            ColdReset = true;
          }
        } else {
          j = 1;
          do {
            exitg5 = 0;
            i = nA - 1;
            if (j - 1 <= i) {
              f_i = 9 + (int16_T)j;
              if (f_i > 32767) {
                f_i = 32767;
              }

              c_i = (int16_T)j - 1;
              Rhs[f_i - 1] = b[iC[c_i] - 1];
              for (kNext = (int16_T)j; kNext <= nA; kNext++) {
                f_i = (kNext + 9 * c_i) - 1;
                U[f_i] = 0.0;
                for (c_k = 1; c_k - 1 <= i; c_k++) {
                  U_tmp = ((int16_T)c_k - 1) * 9;
                  U[f_i] += RLinv[(U_tmp + kNext) - 1] * RLinv[(U_tmp + (int16_T)
                    j) - 1];
                }

                U[((int16_T)j + 9 * (kNext - 1)) - 1] = U[f_i];
              }

              j++;
            } else {
              exitg5 = 1;
            }
          } while (exitg5 == 0);

          for (c_i = 0; c_i < 9; c_i++) {
            f_i = 1 + c_i;
            Xnorm0 = 0.0;
            for (j = 0; j < 9; j++) {
              Xnorm0 += b_H[(9 * j + f_i) - 1] * Rhs[j];
            }

            Opt[c_i] = Xnorm0;
            for (j = 1; j - 1 <= i; j++) {
              f_i = 9 + (int16_T)j;
              if (f_i > 32767) {
                f_i = 32767;
              }

              Opt[c_i] += b_D[((int16_T)j - 1) * 9 + c_i] * Rhs[f_i - 1];
            }
          }

          for (c_i = 1; c_i - 1 <= i; c_i++) {
            j = (int16_T)c_i;
            Xnorm0 = 0.0;
            for (f_i = 0; f_i < 9; f_i++) {
              Xnorm0 += b_D[(j - 1) * 9 + f_i] * Rhs[f_i];
            }

            f_i = 9 + (int16_T)c_i;
            j = f_i;
            if (f_i > 32767) {
              j = 32767;
            }

            Opt[j - 1] = Xnorm0;
            for (c_k = 1; c_k - 1 <= i; c_k++) {
              j = f_i;
              if (f_i > 32767) {
                j = 32767;
              }

              U_tmp = f_i;
              if (f_i > 32767) {
                U_tmp = 32767;
              }

              tmp = 9 + (int16_T)c_k;
              if (tmp > 32767) {
                tmp = 32767;
              }

              Opt[j - 1] = U[(((int16_T)c_k - 1) * 9 + (int16_T)c_i) - 1] *
                Rhs[tmp - 1] + Opt[U_tmp - 1];
            }
          }

          Xnorm0 = -1.0E-12;
          kDrop = 0;
          for (c_i = 1; c_i - 1 <= i; c_i++) {
            f_i = 9 + (int16_T)c_i;
            j = f_i;
            if (f_i > 32767) {
              j = 32767;
            }

            lambda[iC[(int16_T)c_i - 1] - 1] = Opt[j - 1];
            j = f_i;
            if (f_i > 32767) {
              j = 32767;
            }

            if ((Opt[j - 1] < Xnorm0) && ((int16_T)c_i <= nA)) {
              kDrop = (int16_T)c_i;
              if (f_i > 32767) {
                f_i = 32767;
              }

              Xnorm0 = Opt[f_i - 1];
            }
          }

          if (kDrop <= 0) {
            DualFeasible = true;
            memcpy(&x[0], &Opt[0], 9U * sizeof(real_T));
          } else {
            (*status)++;
            if ((int16_T)idx > 50) {
              tmp_0 = (int16_T)idx;
            } else {
              tmp_0 = 50;
            }

            if ((int32_T)*status > Adaptive_rdivide_helper(tmp_0, 10)) {
              nA = 0;
              for (i = 0; i < 16; i++) {
                iA[i] = 0;
                iC[i] = 0;
              }

              ColdReset = true;
            } else {
              lambda[iC[kDrop - 1] - 1] = 0.0;
              Adaptive_DropConstraint(kDrop, iA, &nA, iC);
            }
          }
        }
      } else {
        if (nA <= 0) {
          memset(&lambda[0], 0, sizeof(real_T) << 4U);
          Adaptive_Unconstrained(b_Hinv, f, x, 9);
        }

        exitg3 = 1;
      }
    } while (exitg3 == 0);

    if (exitg3 == 1) {
      guard1 = true;
    }
  } else {
    Adaptive_Unconstrained(b_Hinv, f, x, 9);
    guard1 = true;
  }

  if (guard1) {
    Xnorm0 = Adaptive_norm(x);
    do {
      exitg2 = 0;
      if ((int32_T)*status <= b_maxiter) {
        cMin = -FeasTol;
        kNext = 0;
        for (f_i = 0; f_i < 16; f_i++) {
          if (!cTolComputed) {
            idx = 1 + f_i;
            for (i = 0; i < 9; i++) {
              b_Ac_0[i] = b_Ac[((i << 4) + idx) - 1] * x[i];
            }

            Adaptive_abs(b_Ac_0, AcRow);
            if (!rtIsNaN(AcRow[0])) {
              idx = 1;
            } else {
              idx = 0;
              i = 2;
              exitg4 = false;
              while ((!exitg4) && (i < 10)) {
                if (!rtIsNaN(AcRow[i - 1])) {
                  idx = i;
                  exitg4 = true;
                } else {
                  i++;
                }
              }
            }

            if (idx == 0) {
              cVal = AcRow[0];
            } else {
              cVal = AcRow[idx - 1];
              while (idx + 1 < 10) {
                if (cVal < AcRow[idx]) {
                  cVal = AcRow[idx];
                }

                idx++;
              }
            }

            cTol[f_i] = fmax(cTol[f_i], cVal);
          }

          if (iA[f_i] == 0) {
            idx = 1 + f_i;
            cVal = 0.0;
            for (i = 0; i < 9; i++) {
              cVal += b_Ac[((i << 4) + idx) - 1] * x[i];
            }

            cVal = (cVal - b[f_i]) / cTol[f_i];
            if (cVal < cMin) {
              cMin = cVal;
              kNext = (int16_T)(1 + f_i);
            }
          }
        }

        cTolComputed = true;
        if (kNext <= 0) {
          exitg2 = 1;
        } else {
          do {
            exitg1 = 0;
            if ((kNext > 0) && ((int32_T)*status <= b_maxiter)) {
              guard2 = false;
              if (nA == 0) {
                for (idx = 0; idx < 9; idx++) {
                  AcRow[idx] = 0.0;
                  for (i = 0; i < 9; i++) {
                    AcRow[idx] += b_Ac[((i << 4) + kNext) - 1] * b_Hinv[9 * i +
                      idx];
                  }
                }

                guard2 = true;
              } else {
                cMin = Adaptive_KWIKfactor(b_Ac, iC, nA, b_Linv, RLinv, b_D, b_H,
                  9);
                if (cMin <= 0.0) {
                  *status = -2.0;
                  exitg1 = 1;
                } else {
                  for (idx = 0; idx < 81; idx++) {
                    U[idx] = -b_H[idx];
                  }

                  for (idx = 0; idx < 9; idx++) {
                    AcRow[idx] = 0.0;
                    for (i = 0; i < 9; i++) {
                      AcRow[idx] += b_Ac[((i << 4) + kNext) - 1] * U[9 * i + idx];
                    }
                  }

                  for (i = 1; i - 1 < nA; i++) {
                    f_i = (int16_T)i;
                    cVal = 0.0;
                    for (idx = 0; idx < 9; idx++) {
                      cVal += b_Ac[((idx << 4) + kNext) - 1] * b_D[(f_i - 1) * 9
                        + idx];
                    }

                    r[(int16_T)i - 1] = cVal;
                  }

                  guard2 = true;
                }
              }

              if (guard2) {
                kDrop = 0;
                cMin = 0.0;
                DualFeasible = true;
                ColdReset = true;
                if (nA > 0) {
                  idx = 0;
                  exitg4 = false;
                  while ((!exitg4) && (idx <= nA - 1)) {
                    if (r[idx] >= 1.0E-12) {
                      ColdReset = false;
                      exitg4 = true;
                    } else {
                      idx++;
                    }
                  }
                }

                if ((nA != 0) && (!ColdReset)) {
                  for (i = 1; i - 1 < nA; i++) {
                    idx = (int16_T)i - 1;
                    if (r[idx] > 1.0E-12) {
                      cVal = lambda[iC[idx] - 1] / r[idx];
                      if ((kDrop == 0) || (cVal < rMin)) {
                        rMin = cVal;
                        kDrop = (int16_T)i;
                      }
                    }
                  }

                  if (kDrop > 0) {
                    cMin = rMin;
                    DualFeasible = false;
                  }
                }

                t = 0.0;
                for (idx = 0; idx < 9; idx++) {
                  t += b_Ac[((idx << 4) + kNext) - 1] * AcRow[idx];
                }

                if (t <= 0.0) {
                  cVal = 0.0;
                  ColdReset = true;
                } else {
                  cVal = 0.0;
                  for (idx = 0; idx < 9; idx++) {
                    cVal += b_Ac[((idx << 4) + kNext) - 1] * x[idx];
                  }

                  cVal = (b[kNext - 1] - cVal) / t;
                  ColdReset = false;
                }

                if (DualFeasible && ColdReset) {
                  *status = -1.0;
                  exitg1 = 1;
                } else {
                  if (ColdReset) {
                    t = cMin;
                  } else if (DualFeasible) {
                    t = cVal;
                  } else {
                    t = fmin(cMin, cVal);
                  }

                  for (idx = 1; idx - 1 < nA; idx++) {
                    i = (int16_T)idx - 1;
                    f_i = iC[i] - 1;
                    lambda[f_i] -= r[i] * t;
                    if ((iC[(int16_T)idx - 1] <= 16) && (lambda[f_i] < 0.0)) {
                      lambda[f_i] = 0.0;
                    }
                  }

                  lambda[kNext - 1] += t;
                  if (t == cMin) {
                    Adaptive_DropConstraint(kDrop, iA, &nA, iC);
                  }

                  if (!ColdReset) {
                    for (idx = 0; idx < 9; idx++) {
                      x[idx] += t * AcRow[idx];
                    }

                    if (t == cVal) {
                      if (nA == 9) {
                        *status = -1.0;
                        exitg1 = 1;
                      } else {
                        idx = nA + 1;
                        if (idx > 32767) {
                          idx = 32767;
                        }

                        nA = (int16_T)idx;
                        iC[(int16_T)idx - 1] = kNext;
                        kDrop = (int16_T)idx;
                        exitg4 = false;
                        while ((!exitg4) && (kDrop > 1)) {
                          idx = kDrop - 1;
                          tmp_0 = iC[idx];
                          i = kDrop - 2;
                          if (iC[idx] > iC[i]) {
                            exitg4 = true;
                          } else {
                            iC[idx] = iC[i];
                            iC[i] = tmp_0;
                            kDrop = (int16_T)idx;
                          }
                        }

                        iA[kNext - 1] = 1;
                        kNext = 0;
                        (*status)++;
                      }
                    } else {
                      (*status)++;
                    }
                  } else {
                    (*status)++;
                  }
                }
              }
            } else {
              cMin = Adaptive_norm(x);
              if (fabs(cMin - Xnorm0) > 0.001) {
                Xnorm0 = cMin;
                Adaptive_abs_e(b, varargin_1);
                for (idx = 0; idx < 16; idx++) {
                  cTol[idx] = fmax(varargin_1[idx], 1.0);
                }

                cTolComputed = false;
              }

              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = 1;
          }
        }
      } else {
        *status = 0.0;
        exitg2 = 1;
      }
    } while (exitg2 == 0);
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_mpc_solveQP(const real_T xQP[4], const real_T b_Kx[32],
  const real_T b_Kr[360], const real_T rseq[45], const real_T b_Ku1[16], const
  real_T old_u[2], const real_T b_Kv[128], const real_T vseq[16], const real_T
  b_Kut[240], const real_T b_utarget[30], const real_T b_Linv[81], const real_T
  b_Hinv[81], const real_T b_Ac[144], const real_T Bc[16], boolean_T iA[16],
  real_T zopt[9], real_T f[9], real_T *status)
{
  real_T unusedU0[16];
  int16_T iAnew[16];
  int32_T i;
  real_T b_Kr_0;
  real_T b_Kv_0;
  real_T b_Kut_0;
  int32_T f_tmp;
  int32_T f_tmp_0;
  memset(&f[0], 0, 9U * sizeof(real_T));
  for (i = 0; i < 8; i++) {
    b_Kr_0 = 0.0;
    for (f_tmp = 0; f_tmp < 45; f_tmp++) {
      b_Kr_0 += b_Kr[45 * i + f_tmp] * rseq[f_tmp];
    }

    b_Kv_0 = 0.0;
    for (f_tmp = 0; f_tmp < 16; f_tmp++) {
      b_Kv_0 += b_Kv[(i << 4) + f_tmp] * vseq[f_tmp];
    }

    b_Kut_0 = 0.0;
    for (f_tmp = 0; f_tmp < 30; f_tmp++) {
      b_Kut_0 += b_Kut[30 * i + f_tmp] * b_utarget[f_tmp];
    }

    f_tmp = i << 2;
    f_tmp_0 = i << 1;
    f[i] = ((((((b_Kx[f_tmp + 1] * xQP[1] + b_Kx[f_tmp] * xQP[0]) + b_Kx[f_tmp +
                2] * xQP[2]) + b_Kx[f_tmp + 3] * xQP[3]) + b_Kr_0) +
             (b_Ku1[f_tmp_0 + 1] * old_u[1] + b_Ku1[f_tmp_0] * old_u[0])) +
            b_Kv_0) + b_Kut_0;
  }

  for (i = 0; i < 16; i++) {
    iAnew[i] = iA[i];
  }

  Adaptive_qpkwik(b_Linv, b_Hinv, f, b_Ac, Bc, iAnew, 120, 1.0E-6, zopt,
                  unusedU0, status);
  for (i = 0; i < 16; i++) {
    iA[i] = (iAnew[i] != 0);
  }

  if ((*status < 0.0) || (*status == 0.0)) {
    memset(&zopt[0], 0, 9U * sizeof(real_T));
  }
}

/* Function for MATLAB Function: '<S29>/FixedHorizonOptimizer' */
static void Adaptive_mpcblock_optimizer(const real_T rseq[45], const real_T
  vseq[16], const real_T umin[2], const real_T umax[2], const real_T ymin[3],
  const real_T ymax[3], const real_T x[4], const real_T old_u[2], const
  boolean_T iA[16], const real_T b_Mlim[16], real_T b_Mx[64], real_T b_Mu1[32],
  real_T b_Mv[256], const real_T b_utarget[30], const real_T b_uoff[2], const
  real_T b_yoff[3], real_T b_H[81], real_T b_Ac[144], const real_T ywt[3], const
  real_T duwt[2], real_T b_Wy[3], real_T b_Wdu[2], const real_T b_Jm[240], const
  real_T b_Wu[2], const real_T b_I1[60], const real_T b_A[256], const real_T Bu
  [128], const real_T Bv[64], const real_T b_C[192], const real_T Dv[48], const
  real_T b_Mrows[16], real_T u[2], real_T useq[32], real_T *status, boolean_T
  iAout[16])
{
  real_T c_Linv[81];
  real_T Bc[16];
  real_T ymax_incr[3];
  real_T ymin_incr[3];
  real_T umax_incr[2];
  real_T umin_incr[2];
  real_T DelBound;
  real_T ii;
  real_T c_SuJm[360];
  real_T c_Sx[180];
  real_T c_Su1[90];
  real_T b[64];
  real_T c_Ku1[16];
  real_T c_Kut[240];
  real_T c_Kx[32];
  real_T c_Kv[128];
  real_T c_Kr[360];
  real_T d_Linv[81];
  real_T zopt[9];
  real_T f[9];
  static const real_T c[225] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  int32_T i;
  real_T tmp[81];
  real_T tmp_0[4];
  real_T tmp_1[240];
  int32_T i_0;
  int32_T b_Mrows_tmp;
  int32_T c_Linv_tmp;
  boolean_T exitg1;
  boolean_T guard1 = false;
  memset(&useq[0], 0, sizeof(real_T) << 5U);
  for (i = 0; i < 16; i++) {
    iAout[i] = false;
  }

  Adaptive_mpc_constraintcoef(b_A, Bu, Bv, b_C, Dv, b_Jm, c_SuJm, c_Sx, c_Su1,
    Adaptive_B.c_Hv);
  if (b_Mrows[0] > 0.0) {
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i < 16)) {
      if (b_Mrows[i] <= 45.0) {
        b_Mrows_tmp = (int32_T)b_Mrows[i];
        for (i_0 = 0; i_0 < 8; i_0++) {
          b_Ac[i + (i_0 << 4)] = -c_SuJm[(45 * i_0 + b_Mrows_tmp) - 1];
        }

        b_Mx[i] = -c_Sx[b_Mrows_tmp - 1];
        b_Mx[i + 16] = -c_Sx[b_Mrows_tmp + 44];
        b_Mx[i + 32] = -c_Sx[b_Mrows_tmp + 89];
        b_Mx[i + 48] = -c_Sx[b_Mrows_tmp + 134];
        b_Mu1[i] = -c_Su1[b_Mrows_tmp - 1];
        b_Mu1[i + 16] = -c_Su1[b_Mrows_tmp + 44];
        for (i_0 = 0; i_0 < 16; i_0++) {
          b_Mv[i + (i_0 << 4)] = -Adaptive_B.c_Hv[(45 * i_0 + b_Mrows_tmp) - 1];
        }

        i++;
      } else if (b_Mrows[i] <= 90.0) {
        b_Mrows_tmp = (int32_T)(b_Mrows[i] - 45.0);
        for (i_0 = 0; i_0 < 8; i_0++) {
          b_Ac[i + (i_0 << 4)] = c_SuJm[(45 * i_0 + b_Mrows_tmp) - 1];
        }

        b_Mx[i] = c_Sx[b_Mrows_tmp - 1];
        b_Mx[i + 16] = c_Sx[b_Mrows_tmp + 44];
        b_Mx[i + 32] = c_Sx[b_Mrows_tmp + 89];
        b_Mx[i + 48] = c_Sx[b_Mrows_tmp + 134];
        b_Mu1[i] = c_Su1[b_Mrows_tmp - 1];
        b_Mu1[i + 16] = c_Su1[b_Mrows_tmp + 44];
        for (i_0 = 0; i_0 < 16; i_0++) {
          b_Mv[i + (i_0 << 4)] = Adaptive_B.c_Hv[(45 * i_0 + b_Mrows_tmp) - 1];
        }

        i++;
      } else {
        exitg1 = true;
      }
    }
  }

  Adaptive_updateWeights(b_Wy, ywt, 0.0);
  Adaptive_updateWeights_e(b_Wdu, duwt, 0.0);
  Adaptive_eye_o(tmp_0);
  Adaptive_kron(c, tmp_0, Adaptive_B.dv0);
  for (i_0 = 0; i_0 < 8; i_0++) {
    for (i = 0; i < 30; i++) {
      b_Mrows_tmp = i + 30 * i_0;
      tmp_1[b_Mrows_tmp] = 0.0;
      for (c_Linv_tmp = 0; c_Linv_tmp < 30; c_Linv_tmp++) {
        tmp_1[b_Mrows_tmp] += Adaptive_B.dv0[30 * c_Linv_tmp + i] * b_Jm[30 *
          i_0 + c_Linv_tmp];
      }
    }
  }

  Adaptive_mpc_calculatehessian(b_Wy, b_Wu, b_Wdu, c_SuJm, tmp_1, b_Jm, b_I1,
    c_Su1, c_Sx, Adaptive_B.c_Hv, Adaptive_nu, Adaptive_ny, b, c_Ku1, c_Kut,
    c_Kx, c_Kv, c_Kr);
  for (i_0 = 0; i_0 < 8; i_0++) {
    memcpy(&b_H[i_0 * 9], &b[i_0 << 3], sizeof(real_T) << 3U);
  }

  memcpy(&c_Linv[0], &b_H[0], 81U * sizeof(real_T));
  Adaptive_mpc_checkhessian(c_Linv, d_Linv, &ii);
  if (ii > 1.0) {
    for (i = 0; i < 2; i++) {
      u[i] = old_u[i] + b_uoff[i];
      for (i_0 = 0; i_0 < 16; i_0++) {
        useq[i_0 + (i << 4)] = u[i];
      }
    }

    *status = -2.0;
  } else {
    Adaptive_eye_oi(tmp);
    Adaptive_linsolve(d_Linv, tmp, c_Linv);
    for (i_0 = 0; i_0 < 16; i_0++) {
      ii = 0.0;
      for (i = 0; i < 16; i++) {
        ii += b_Mv[(i << 4) + i_0] * vseq[i];
      }

      Bc[i_0] = -((((((b_Mx[i_0 + 16] * x[1] + b_Mx[i_0] * x[0]) + b_Mx[i_0 + 32]
                      * x[2]) + b_Mx[i_0 + 48] * x[3]) + b_Mlim[i_0]) +
                   (b_Mu1[i_0 + 16] * old_u[1] + b_Mu1[i_0] * old_u[0])) + ii);
    }

    ymax_incr[0] = (rtNaN);
    ymin_incr[0] = (rtNaN);
    ymax_incr[1] = (rtNaN);
    ymin_incr[1] = (rtNaN);
    ymax_incr[2] = (rtNaN);
    ymin_incr[2] = (rtNaN);
    umax_incr[0] = (rtNaN);
    umin_incr[0] = (rtNaN);
    umax_incr[1] = (rtNaN);
    umin_incr[1] = (rtNaN);
    if (b_Mrows[0] > 0.0) {
      i = 0;
      exitg1 = false;
      while ((!exitg1) && (i < 16)) {
        guard1 = false;
        if (b_Mrows[i] <= 45.0) {
          ii = Adaptive_mod(b_Mrows[i] - 1.0) + 1.0;
          if (rtIsNaN(ymax_incr[(int32_T)ii - 1])) {
            DelBound = -(ymax[(int32_T)ii - 1] - b_yoff[(int32_T)ii - 1]) -
              (-b_Mlim[i]);
          } else {
            DelBound = ymax_incr[(int32_T)ii - 1];
          }

          ymax_incr[(int32_T)ii - 1] = DelBound;
          guard1 = true;
        } else if (b_Mrows[i] <= 90.0) {
          ii = Adaptive_mod((b_Mrows[i] - 45.0) - 1.0) + 1.0;
          if (rtIsNaN(ymin_incr[(int32_T)ii - 1])) {
            DelBound = (ymin[(int32_T)ii - 1] - b_yoff[(int32_T)ii - 1]) -
              (-b_Mlim[i]);
          } else {
            DelBound = ymin_incr[(int32_T)ii - 1];
          }

          ymin_incr[(int32_T)ii - 1] = DelBound;
          guard1 = true;
        } else if (b_Mrows[i] <= 120.0) {
          ii = Adaptive_mod_g((b_Mrows[i] - 90.0) - 1.0) + 1.0;
          i_0 = (int32_T)ii - 1;
          if (rtIsNaN(umax_incr[i_0])) {
            DelBound = -(umax[i_0] - b_uoff[i_0]) - (-b_Mlim[i]);
          } else {
            DelBound = umax_incr[(int32_T)ii - 1];
          }

          umax_incr[i_0] = DelBound;
          guard1 = true;
        } else if (b_Mrows[i] <= 150.0) {
          ii = Adaptive_mod_g(((b_Mrows[i] - 90.0) - 30.0) - 1.0) + 1.0;
          if (rtIsNaN(umin_incr[(int32_T)ii - 1])) {
            DelBound = (umin[(int32_T)ii - 1] - b_uoff[(int32_T)ii - 1]) -
              (-b_Mlim[i]);
          } else {
            DelBound = umin_incr[(int32_T)ii - 1];
          }

          umin_incr[(int32_T)ii - 1] = DelBound;
          guard1 = true;
        } else {
          exitg1 = true;
        }

        if (guard1) {
          Bc[i] += DelBound;
          i++;
        }
      }
    }

    for (i = 0; i < 16; i++) {
      iAout[i] = iA[i];
    }

    for (i_0 = 0; i_0 < 9; i_0++) {
      for (i = 0; i < 9; i++) {
        c_Linv_tmp = i_0 + 9 * i;
        d_Linv[c_Linv_tmp] = 0.0;
        for (b_Mrows_tmp = 0; b_Mrows_tmp < 9; b_Mrows_tmp++) {
          d_Linv[c_Linv_tmp] += c_Linv[9 * i_0 + b_Mrows_tmp] * c_Linv[9 * i +
            b_Mrows_tmp];
        }
      }
    }

    Adaptive_mpc_solveQP(x, c_Kx, c_Kr, rseq, c_Ku1, old_u, c_Kv, vseq, c_Kut,
                         b_utarget, c_Linv, d_Linv, b_Ac, Bc, iAout, zopt, f,
                         status);
    u[0] = (old_u[0] + zopt[0]) + b_uoff[0];
    u[1] = (old_u[1] + zopt[1]) + b_uoff[1];
  }
}

/* Model step function */
void Adaptive_step(void)
{
  real_T xk[4];
  real_T Bu[128];
  real_T Bv[64];
  real_T Dv[48];
  real_T Dvm[48];
  real_T Cm[192];
  real_T Qk[16];
  real_T Rk[9];
  real_T Nk[12];
  real_T L[12];
  real_T y_innov[3];
  real_T b_Mlim[16];
  real_T b_utarget[30];
  real_T b_uoff[2];
  real_T b_yoff[3];
  real_T b_myoff[3];
  real_T b_xoff[4];
  real_T rseq[45];
  real_T vseq[16];
  real_T v;
  real_T status;
  int32_T i;
  real_T b_A[256];
  real_T b_C[192];
  static const int8_T f[192] = { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0,
    1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0,
    1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0,
    0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1,
    1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0,
    1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 };

  static const real_T g[256] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.032782468744856727, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.032782468744856727, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.032782468744856727, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.032782468744856727, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.032782468744856727, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.032782468744856727, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.032782468744856727, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.032782468744856727, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.032782468744856727, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.032782468744856727, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.032782468744856727, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.032782468744856727, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.032782468744856727, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.032782468744856727, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.032782468744856727, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.032782468744856727, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  static const real_T h[16] = { 91.0, 92.0, 93.0, 94.0, 95.0, 96.0, 97.0, 98.0,
    121.0, 122.0, 123.0, 124.0, 125.0, 126.0, 127.0, 128.0 };

  static const real_T b_B[448] = { -0.1, 0.0, 0.0, 0.0, 0.0,
    -0.0016391234372428363, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1, 0.0, 0.0,
    0.0, 0.0, -0.0016391234372428363, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1,
    0.0, 0.0, 0.0, 0.0, -0.0016391234372428363, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, -0.1, 0.0, 0.0, 0.0, 0.0, -0.0016391234372428363, -0.1, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, -0.1, 0.0, 0.0, 0.0, 0.0, -0.0016391234372428363, -0.1, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, -0.1, 0.0, 0.0, 0.0, 0.0, -0.0016391234372428363,
    -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1, 0.0, 0.0, 0.0, 0.0,
    -0.0016391234372428363, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1, 0.0, 0.0,
    0.0, 0.0, -0.0016391234372428363, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1,
    0.0, 0.0, 0.0, 0.0, -0.0016391234372428363, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, -0.1, 0.0, 0.0, 0.0, 0.0, -0.0016391234372428363, -0.1, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, -0.1, 0.0, 0.0, 0.0, 0.0, -0.0016391234372428363, -0.1, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, -0.1, 0.0, 0.0, 0.0, 0.0, -0.0016391234372428363,
    -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1, 0.0, 0.0, 0.0, 0.0,
    -0.0016391234372428363, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1, 0.0, 0.0,
    0.0, 0.0, -0.0016391234372428363, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1,
    0.0, 0.0, 0.0, 0.0, -0.0016391234372428363, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, -0.1, 0.0, 0.0, 0.0, 0.0, -0.0016391234372428363, -0.1, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0 };

  static const int8_T b_D[336] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 1, 0, 0, 0, 1 };

  static const int8_T n[32] = { -1, 0, -1, 0, -1, 0, -1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 0, -1, 0, -1, 0, -1, 0, -1, 0, 1, 0, 1, 0, 1, 0, 1 };

  static const real_T o[81] = { 12.400100000000002, 0.0, 11.2, 0.0, 10.01, 0.0,
    8.84, 0.0, 0.0, 0.0, 1240.4791754227688, 0.0, 1120.4050292640609, 0.0,
    1001.3376434982209, 0.0, 884.27690469162053, 0.0, 11.2, 0.0,
    10.150099999999998, 0.0, 9.0999999999999979, 0.0, 8.0599999999999987, 0.0,
    0.0, 0.0, 1120.4050292640609, 0.0, 1015.3431599371162, 0.0,
    910.28654466322575, 0.0, 806.23548075566407, 0.0, 10.01, 0.0,
    9.0999999999999979, 0.0, 8.1901, 0.0, 7.2799999999999994, 0.0, 0.0, 0.0,
    1001.3376434982208, 0.0, 910.28654466322587, 0.0, 819.23994668483317, 0.0,
    728.197549563043, 0.0, 8.84, 0.0, 8.0599999999999987, 0.0,
    7.2799999999999994, 0.0, 6.5000999999999989, 0.0, 0.0, 0.0,
    884.27690469162053, 0.0, 806.23548075566418, 0.0, 728.197549563043, 0.0,
    650.16321111375714, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 100000.0 };

  static const int8_T r[144] = { -1, 0, -1, 0, -1, 0, -1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 0, -1, 0, -1, 0, -1, 0, -1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, -1, 0, -1, 0,
    -1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, -1, 0, -1, 0, -1, 0, 0, 0, 1, 0, 1,
    0, 1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, -1, 0,
    -1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0 };

  static const real_T t[240] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static const real_T y[60] = { 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0 };

  real_T rtb_useq[32];
  real_T L_tmp[16];
  real_T L_tmp_0[12];
  real_T xk_0[4];
  boolean_T tmp[16];
  real_T tmp_0[240];
  real_T tmp_1[128];
  real_T tmp_2[64];
  real_T n_0[32];
  real_T tmp_3[256];
  real_T o_0[81];
  real_T r_0[144];
  real_T tmp_4[9];
  real_T Cm_0[9];
  real_T tmp_5[2];
  real_T tmp_6[3];
  real_T tmp_7[6];
  real_T b_B_0[28];
  real_T b_D_0[21];
  boolean_T tmp_8;
  real_T tmp_9[2];
  real_T tmp_a[2];
  real_T tmp_b[3];
  real_T Cm_1[12];
  real_T L_tmp_1[16];
  int32_T i_0;
  real_T tmp_c;
  real_T b_A_0;
  int32_T b_Mlim_tmp;
  int32_T b_Mlim_tmp_0;
  tmp_8 = false;

  /* MATLAB Function: '<S29>/FixedHorizonOptimizer' incorporates:
   *  Inport: '<Root>/A'
   *  Inport: '<Root>/B'
   *  Inport: '<Root>/C'
   *  Inport: '<Root>/DX'
   *  Inport: '<Root>/U'
   *  Inport: '<Root>/X'
   *  Inport: '<Root>/Y'
   *  Inport: '<Root>/mo or x'
   *  Inport: '<Root>/ref'
   *  Memory: '<S2>/LastPcov'
   *  Memory: '<S2>/last_x'
   *  UnitDelay: '<S2>/last_mv'
   */
  for (i_0 = 0; i_0 < 192; i_0++) {
    b_C[i_0] = f[i_0];
  }

  memcpy(&b_A[0], &g[0], sizeof(real_T) << 8U);
  for (i = 0; i < 16; i++) {
    for (i_0 = 0; i_0 < 4; i_0++) {
      b_Mlim_tmp = i_0 << 2;
      b_Mlim_tmp_0 = b_Mlim_tmp + (i << 4);
      b_Mlim[b_Mlim_tmp] = b_A[b_Mlim_tmp_0];
      b_Mlim[1 + b_Mlim_tmp] = b_A[b_Mlim_tmp_0 + 1];
      b_Mlim[2 + b_Mlim_tmp] = b_A[b_Mlim_tmp_0 + 2];
      b_Mlim[3 + b_Mlim_tmp] = b_A[b_Mlim_tmp_0 + 3];
      b_Mlim_tmp_0 = 3 * i_0 + 12 * i;
      L[3 * i_0] = b_C[b_Mlim_tmp_0];
      L[1 + 3 * i_0] = b_C[b_Mlim_tmp_0 + 1];
      L[2 + 3 * i_0] = b_C[b_Mlim_tmp_0 + 2];
    }

    for (i_0 = 0; i_0 < 2; i_0++) {
      b_Mlim_tmp = 3 * i_0 + 6 * i;
      tmp_7[3 * i_0] = Adaptive_U.B[b_Mlim_tmp];
      tmp_7[1 + 3 * i_0] = Adaptive_U.B[b_Mlim_tmp + 1];
      tmp_7[2 + 3 * i_0] = Adaptive_U.B[b_Mlim_tmp + 2];
    }

    for (i_0 = 0; i_0 < 7; i_0++) {
      b_Mlim_tmp = i_0 << 2;
      b_Mlim_tmp_0 = b_Mlim_tmp + 28 * i;
      b_B_0[b_Mlim_tmp] = b_B[b_Mlim_tmp_0];
      b_B_0[1 + b_Mlim_tmp] = b_B[b_Mlim_tmp_0 + 1];
      b_B_0[2 + b_Mlim_tmp] = b_B[b_Mlim_tmp_0 + 2];
      b_B_0[3 + b_Mlim_tmp] = b_B[b_Mlim_tmp_0 + 3];
      b_Mlim_tmp = 3 * i_0 + 21 * i;
      b_D_0[3 * i_0] = b_D[b_Mlim_tmp];
      b_D_0[1 + 3 * i_0] = b_D[b_Mlim_tmp + 1];
      b_D_0[2 + 3 * i_0] = b_D[b_Mlim_tmp + 2];
    }

    if (!tmp_8) {
      tmp_9[0] = 1.0;
      tmp_9[1] = 2.0;
      y_innov[0] = 1.0;
      y_innov[1] = 2.0;
      y_innov[2] = 3.0;
      tmp_a[0] = 1.0;
      tmp_a[1] = 1.0;
      tmp_b[0] = 1.0;
      tmp_b[1] = 1.0;
      tmp_b[2] = 1.0;
      tmp_8 = true;
    }

    Adaptive_mpc_plantupdate(&Adaptive_U.A[9 * i], tmp_7, &Adaptive_U.C[9 * i],
      b_Mlim, b_B_0, L, b_D_0, tmp_9, y_innov, tmp_a, tmp_b, &Bu[i << 3], &Bv[i <<
      2], &Cm[12 * i], &Dv[3 * i], &Dvm[3 * i], Qk, Rk, Nk);
    for (i_0 = 0; i_0 < 4; i_0++) {
      b_Mlim_tmp = i_0 << 2;
      b_Mlim_tmp_0 = b_Mlim_tmp + (i << 4);
      b_A[b_Mlim_tmp_0] = b_Mlim[b_Mlim_tmp];
      b_A[b_Mlim_tmp_0 + 1] = b_Mlim[b_Mlim_tmp + 1];
      b_A[b_Mlim_tmp_0 + 2] = b_Mlim[b_Mlim_tmp + 2];
      b_A[b_Mlim_tmp_0 + 3] = b_Mlim[b_Mlim_tmp + 3];
      b_Mlim_tmp = 3 * i_0 + 12 * i;
      b_C[b_Mlim_tmp] = L[3 * i_0];
      b_C[b_Mlim_tmp + 1] = L[3 * i_0 + 1];
      b_C[b_Mlim_tmp + 2] = L[3 * i_0 + 2];
    }
  }

  for (i = 0; i < 16; i++) {
    b_Mlim[i] = 10.0;
  }

  memset(&b_utarget[0], 0, 30U * sizeof(real_T));
  b_xoff[0] = 0.0;
  b_xoff[1] = 0.0;
  b_xoff[2] = 0.0;
  b_xoff[3] = 0.0;
  tmp_9[0] = 1.0;
  tmp_a[0] = 0.0;
  tmp_5[0] = 1.0;
  tmp_9[1] = 1.0;
  tmp_a[1] = 0.0;
  tmp_5[1] = 2.0;
  y_innov[0] = 1.0;
  tmp_b[0] = 0.0;
  tmp_6[0] = 1.0;
  y_innov[1] = 1.0;
  tmp_b[1] = 0.0;
  tmp_6[1] = 2.0;
  y_innov[2] = 1.0;
  tmp_b[2] = 0.0;
  tmp_6[2] = 3.0;
  Adaptive_mpc_updateFromNominal(b_Mlim, h, Adaptive_U.U, tmp_9, tmp_a, tmp_5,
    b_utarget, Adaptive_U.Y, y_innov, tmp_b, tmp_6, Adaptive_U.X, b_xoff,
    Adaptive_U.DX, b_A, Bu, Bv, b_C, Dv, b_uoff, b_yoff, b_myoff);
  y_innov[0] = 1.0;
  y_innov[1] = 1.0;
  y_innov[2] = 1.0;
  Adaptive_mpcblock_refmd(Adaptive_U.ref, b_yoff, y_innov, rseq, vseq, &v);
  Adaptive_eye(tmp_4);
  for (i_0 = 0; i_0 < 3; i_0++) {
    for (b_Mlim_tmp = 0; b_Mlim_tmp < 4; b_Mlim_tmp++) {
      b_Mlim_tmp_0 = 3 * b_Mlim_tmp + i_0;
      L[b_Mlim_tmp + (i_0 << 2)] = Cm[b_Mlim_tmp_0];
      Cm_1[b_Mlim_tmp_0] = 0.0;
      i = b_Mlim_tmp << 2;
      Cm_1[b_Mlim_tmp_0] += Adaptive_DW.LastPcov_PreviousInput[i] * Cm[i_0];
      Cm_1[b_Mlim_tmp_0] += Adaptive_DW.LastPcov_PreviousInput[i + 1] * Cm[i_0 +
        3];
      Cm_1[b_Mlim_tmp_0] += Adaptive_DW.LastPcov_PreviousInput[i + 2] * Cm[i_0 +
        6];
      Cm_1[b_Mlim_tmp_0] += Adaptive_DW.LastPcov_PreviousInput[i + 3] * Cm[i_0 +
        9];
    }
  }

  for (i_0 = 0; i_0 < 3; i_0++) {
    for (b_Mlim_tmp = 0; b_Mlim_tmp < 3; b_Mlim_tmp++) {
      i = i_0 << 2;
      b_Mlim_tmp_0 = 3 * i_0 + b_Mlim_tmp;
      Cm_0[b_Mlim_tmp_0] = (((L[i + 1] * Cm_1[b_Mlim_tmp + 3] + L[i] *
        Cm_1[b_Mlim_tmp]) + L[i + 2] * Cm_1[b_Mlim_tmp + 6]) + L[i + 3] *
                            Cm_1[b_Mlim_tmp + 9]) + Rk[b_Mlim_tmp_0];
    }
  }

  Adaptive_mrdivide_helper(tmp_4, Cm_0, Rk);
  for (i_0 = 0; i_0 < 4; i_0++) {
    for (b_Mlim_tmp = 0; b_Mlim_tmp < 4; b_Mlim_tmp++) {
      b_Mlim_tmp_0 = b_Mlim_tmp << 2;
      i = i_0 + b_Mlim_tmp_0;
      L_tmp[i] = 0.0;
      L_tmp[i] += Adaptive_DW.LastPcov_PreviousInput[b_Mlim_tmp_0] * b_A[i_0];
      L_tmp[i] += Adaptive_DW.LastPcov_PreviousInput[b_Mlim_tmp_0 + 1] * b_A[i_0
        + 4];
      L_tmp[i] += Adaptive_DW.LastPcov_PreviousInput[b_Mlim_tmp_0 + 2] * b_A[i_0
        + 8];
      L_tmp[i] += Adaptive_DW.LastPcov_PreviousInput[b_Mlim_tmp_0 + 3] * b_A[i_0
        + 12];
    }

    for (b_Mlim_tmp = 0; b_Mlim_tmp < 3; b_Mlim_tmp++) {
      i = b_Mlim_tmp << 2;
      b_Mlim_tmp_0 = i + i_0;
      L_tmp_0[b_Mlim_tmp_0] = (((L[i + 1] * L_tmp[i_0 + 4] + L[i] * L_tmp[i_0])
        + L[i + 2] * L_tmp[i_0 + 8]) + L[i + 3] * L_tmp[i_0 + 12]) +
        Nk[b_Mlim_tmp_0];
    }
  }

  for (i_0 = 0; i_0 < 4; i_0++) {
    for (b_Mlim_tmp = 0; b_Mlim_tmp < 3; b_Mlim_tmp++) {
      b_Mlim_tmp_0 = i_0 + (b_Mlim_tmp << 2);
      L[b_Mlim_tmp_0] = 0.0;
      L[b_Mlim_tmp_0] += Rk[3 * b_Mlim_tmp] * L_tmp_0[i_0];
      L[b_Mlim_tmp_0] += Rk[3 * b_Mlim_tmp + 1] * L_tmp_0[i_0 + 4];
      L[b_Mlim_tmp_0] += Rk[3 * b_Mlim_tmp + 2] * L_tmp_0[i_0 + 8];
    }

    xk[i_0] = (Bu[i_0 + 4] * 0.0 + Bu[i_0] * 0.0) +
      (Adaptive_DW.last_x_PreviousInput[i_0] - b_xoff[i_0]);
  }

  for (i_0 = 0; i_0 < 3; i_0++) {
    y_innov[i_0] = (Adaptive_U.moorx[i_0] - b_myoff[i_0]) - ((((Cm[i_0 + 3] *
      xk[1] + Cm[i_0] * xk[0]) + Cm[i_0 + 6] * xk[2]) + Cm[i_0 + 9] * xk[3]) +
      Dvm[i_0] * v);
  }

  for (i_0 = 0; i_0 < 4; i_0++) {
    for (b_Mlim_tmp = 0; b_Mlim_tmp < 3; b_Mlim_tmp++) {
      i = i_0 + (b_Mlim_tmp << 2);
      Nk[i] = 0.0;
      Nk[i] += Adaptive_DW.LastPcov_PreviousInput[i_0] * Cm[b_Mlim_tmp];
      Nk[i] += Adaptive_DW.LastPcov_PreviousInput[i_0 + 4] * Cm[b_Mlim_tmp + 3];
      Nk[i] += Adaptive_DW.LastPcov_PreviousInput[i_0 + 8] * Cm[b_Mlim_tmp + 6];
      Nk[i] += Adaptive_DW.LastPcov_PreviousInput[i_0 + 12] * Cm[b_Mlim_tmp + 9];
    }

    status = 0.0;
    for (b_Mlim_tmp = 0; b_Mlim_tmp < 3; b_Mlim_tmp++) {
      i = i_0 + (b_Mlim_tmp << 2);
      Cm_1[i] = 0.0;
      Cm_1[i] += Rk[3 * b_Mlim_tmp] * Nk[i_0];
      Cm_1[i] += Rk[3 * b_Mlim_tmp + 1] * Nk[i_0 + 4];
      Cm_1[i] += Rk[3 * b_Mlim_tmp + 2] * Nk[i_0 + 8];
      status += Cm_1[i] * y_innov[b_Mlim_tmp];
    }

    xk_0[i_0] = xk[i_0] + status;
  }

  tmp_9[0] = Adaptive_DW.last_mv_DSTATE[0] - b_uoff[0];
  tmp_9[1] = Adaptive_DW.last_mv_DSTATE[1] - b_uoff[1];

  /* Memory: '<S2>/Memory' */
  for (i_0 = 0; i_0 < 16; i_0++) {
    tmp[i_0] = Adaptive_DW.Memory_PreviousInput[i_0];
  }

  /* End of Memory: '<S2>/Memory' */

  /* MATLAB Function: '<S29>/FixedHorizonOptimizer' */
  memset(&tmp_0[0], 0, 240U * sizeof(real_T));
  memset(&tmp_1[0], 0, sizeof(real_T) << 7U);
  memset(&Adaptive_B.dv1[0], 0, 720U * sizeof(real_T));
  tmp_a[0] = 0.0;
  tmp_a[1] = 0.0;
  memset(&tmp_2[0], 0, sizeof(real_T) << 6U);
  for (i_0 = 0; i_0 < 32; i_0++) {
    n_0[i_0] = n[i_0];
  }

  memset(&tmp_3[0], 0, sizeof(real_T) << 8U);
  memcpy(&o_0[0], &o[0], 81U * sizeof(real_T));
  for (i_0 = 0; i_0 < 144; i_0++) {
    r_0[i_0] = r[i_0];
  }

  b_myoff[0] = 1.0;
  b_myoff[1] = 1.0;
  b_myoff[2] = 100.0;
  tmp_5[0] = 0.0001;
  tmp_5[1] = 0.0001;

  /* Update for Memory: '<S2>/Memory' incorporates:
   *  Inport: '<Root>/du.wt'
   *  Inport: '<Root>/umax'
   *  Inport: '<Root>/umin'
   *  Inport: '<Root>/y.wt'
   *  Inport: '<Root>/ymax'
   *  Inport: '<Root>/ymin'
   *  MATLAB Function: '<S29>/FixedHorizonOptimizer'
   */
  Adaptive_mpcblock_optimizer(rseq, vseq, Adaptive_U.umin, Adaptive_U.umax,
    Adaptive_U.ymin, Adaptive_U.ymax, xk_0, tmp_9, tmp, b_Mlim, tmp_2, n_0,
    tmp_3, b_utarget, b_uoff, b_yoff, o_0, r_0, Adaptive_U.ywt, Adaptive_U.duwt,
    b_myoff, tmp_5, t, tmp_a, y, b_A, Bu, Bv, b_C, Dv, h, Adaptive_Y.mv,
    rtb_useq, &status, Adaptive_DW.Memory_PreviousInput);

  /* MATLAB Function: '<S29>/FixedHorizonOptimizer' */
  for (i_0 = 0; i_0 < 4; i_0++) {
    for (b_Mlim_tmp = 0; b_Mlim_tmp < 4; b_Mlim_tmp++) {
      i = i_0 + (b_Mlim_tmp << 2);
      vseq[i] = 0.0;
      vseq[i] += L_tmp[i_0] * b_A[b_Mlim_tmp];
      vseq[i] += L_tmp[i_0 + 4] * b_A[b_Mlim_tmp + 4];
      vseq[i] += L_tmp[i_0 + 8] * b_A[b_Mlim_tmp + 8];
      vseq[i] += L_tmp[i_0 + 12] * b_A[b_Mlim_tmp + 12];
      L_tmp_1[i] = 0.0;
      L_tmp_1[i] += L_tmp_0[i_0] * L[b_Mlim_tmp];
      L_tmp_1[i] += L_tmp_0[i_0 + 4] * L[b_Mlim_tmp + 4];
      L_tmp_1[i] += L_tmp_0[i_0 + 8] * L[b_Mlim_tmp + 8];
    }
  }

  for (i_0 = 0; i_0 < 16; i_0++) {
    b_Mlim[i_0] = (vseq[i_0] - L_tmp_1[i_0]) + Qk[i_0];
  }

  status = Adaptive_Y.mv[0] - b_uoff[0];
  tmp_c = Adaptive_Y.mv[1] - b_uoff[1];
  for (i_0 = 0; i_0 < 4; i_0++) {
    /* MATLAB Function: '<S29>/FixedHorizonOptimizer' */
    i = i_0 << 2;

    /* Update for Memory: '<S2>/LastPcov' incorporates:
     *  MATLAB Function: '<S29>/FixedHorizonOptimizer'
     */
    Adaptive_DW.LastPcov_PreviousInput[i] = (b_Mlim[i] + b_Mlim[i_0]) * 0.5;

    /* MATLAB Function: '<S29>/FixedHorizonOptimizer' */
    b_Mlim_tmp = i + 1;

    /* Update for Memory: '<S2>/LastPcov' incorporates:
     *  MATLAB Function: '<S29>/FixedHorizonOptimizer'
     */
    Adaptive_DW.LastPcov_PreviousInput[b_Mlim_tmp] = (b_Mlim[b_Mlim_tmp] +
      b_Mlim[i_0 + 4]) * 0.5;

    /* MATLAB Function: '<S29>/FixedHorizonOptimizer' */
    b_Mlim_tmp = i + 2;

    /* Update for Memory: '<S2>/LastPcov' incorporates:
     *  MATLAB Function: '<S29>/FixedHorizonOptimizer'
     */
    Adaptive_DW.LastPcov_PreviousInput[b_Mlim_tmp] = (b_Mlim[b_Mlim_tmp] +
      b_Mlim[i_0 + 8]) * 0.5;

    /* MATLAB Function: '<S29>/FixedHorizonOptimizer' */
    i += 3;

    /* Update for Memory: '<S2>/LastPcov' incorporates:
     *  MATLAB Function: '<S29>/FixedHorizonOptimizer'
     */
    Adaptive_DW.LastPcov_PreviousInput[i] = (b_Mlim[i] + b_Mlim[i_0 + 12]) * 0.5;

    /* MATLAB Function: '<S29>/FixedHorizonOptimizer' */
    b_A_0 = b_A[i_0 + 12] * xk[3] + (b_A[i_0 + 8] * xk[2] + (b_A[i_0 + 4] * xk[1]
      + b_A[i_0] * xk[0]));

    /* Update for Memory: '<S2>/last_x' incorporates:
     *  MATLAB Function: '<S29>/FixedHorizonOptimizer'
     */
    Adaptive_DW.last_x_PreviousInput[i_0] = (((L[i_0 + 4] * y_innov[1] + L[i_0] *
      y_innov[0]) + L[i_0 + 8] * y_innov[2]) + ((b_A_0 + (Bu[i_0 + 4] * tmp_c +
      Bu[i_0] * status)) + Bv[i_0] * v)) + b_xoff[i_0];
  }

  /* Update for UnitDelay: '<S2>/last_mv' */
  Adaptive_DW.last_mv_DSTATE[0] = Adaptive_Y.mv[0];
  Adaptive_DW.last_mv_DSTATE[1] = Adaptive_Y.mv[1];
}

/* Model initialize function */
void Adaptive_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(Adaptive_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&Adaptive_DW, 0,
                sizeof(DW_Adaptive_T));

  /* external inputs */
  (void)memset(&Adaptive_U, 0, sizeof(ExtU_Adaptive_T));

  /* external outputs */
  (void) memset(&Adaptive_Y.mv[0], 0,
                2U*sizeof(real_T));

  /* InitializeConditions for Memory: '<S2>/LastPcov' */
  memcpy(&Adaptive_DW.LastPcov_PreviousInput[0],
         &Adaptive_ConstP.LastPcov_InitialCondition[0], sizeof(real_T) << 4U);
}

/* Model terminate function */
void Adaptive_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
