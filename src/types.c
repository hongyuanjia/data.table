#include <Rdefines.h>
#include "data.table.h"

// find end of a string, used to append verbose message or warnings
char *end(char *start) {
  return strchr(start, 0);
}

/*
 * function to print verbose messages, stderr messages, warnings and errors handled in ans_t struct
 */
void msg(ans_t *ans, int n, bool verbose) {
  for (int i=0; i<n; i++) {
    if (verbose && (ans[i].message[0][0] != '\0'))
      Rprintf("%s", ans[i].message[0]);
    if (ans[i].message[1][0] != '\0')
      REprintf("%s", ans[i].message[1]);
    if (ans[i].message[2][0] != '\0')
      warning("%s", ans[i].message[2]);
    if (ans[i].status == 3)  {
      char err_msg[ANS_MSG_SIZE];
      strncpy(err_msg, ans[i].message[3], ANS_MSG_SIZE);
      free(ans);
      error("%s", err_msg);
    }
  }
}

// a tester function for msg: cc(F); msg(2L, 1L, 1L)
SEXP msgR(SEXP status, SEXP x, SEXP k) {
  if (!isInteger(status) || !isInteger(x) || !isInteger(k))
    error("status, nx, nk must be integer");
  int protecti = 0;
  const bool verbose = GetVerbose();

  int nx = INTEGER(x)[0], nk = INTEGER(k)[0];
  SEXP ans = PROTECT(allocVector(VECSXP, nk * nx)); protecti++;
  ans_t *dans = malloc(sizeof(ans_t)*nx*nk);
  if (!dans)
    error("%s: Unable to allocate memory answer", __func__); // # nocov
  if (verbose)
    Rprintf("%s: allocating memory for results %dx%d\n", __func__, nx, nk);
  for (R_len_t i=0; i<nx; i++) {
    for (R_len_t j=0; j<nk; j++) {
      SET_VECTOR_ELT(ans, i*nk+j, allocVector(REALSXP, 1));
      dans[i*nk+j] = ((ans_t) { .dbl_v=REAL(VECTOR_ELT(ans, i*nk+j)), .status=0, .message={"\0","\0","\0","\0"} });
    }
  }

  int istatus = INTEGER(status)[0];
  #pragma omp parallel for if (nx*nk>1) schedule(auto) collapse(2) num_threads(getDTthreads())
  for (R_len_t i=0; i<nx; i++) {
    for (R_len_t j=0; j<nk; j++) {
      ans_t *ans = &dans[i*nk+j];
      if (verbose) {
        snprintf(end(ans->message[0]), 500, "%s: %d: I am 1 stdout message\n", __func__, i*nk+j+1);
        snprintf(end(ans->message[0]), 500, "%s: %d: I am 2 stdout message\n", __func__, i*nk+j+1);
      }
      if (istatus == 1) {
        snprintf(end(ans->message[1]), 500, "%s: %d: I am 1 stderr message\n", __func__, i*nk+j+1);
        snprintf(end(ans->message[1]), 500, "%s: %d: I am 2 stderr message\n", __func__, i*nk+j+1);
        ans->status = 1;
      } else if (istatus == 2) {
        snprintf(end(ans->message[2]), 500, "%s: %d: I am 1 stderr warning\n", __func__, i*nk+j+1);
        snprintf(end(ans->message[2]), 500, "%s: %d: I am 2 stderr warning\n", __func__, i*nk+j+1);
        ans->status = 2;
      } else if (istatus == 3) {
        snprintf(end(ans->message[3]), 500, "%s: %d: I am 1 stderr error\n", __func__, i*nk+j+1);
        snprintf(end(ans->message[3]), 500, "%s: %d: I am 2 stderr error, also printed because deferred and appended after first error\n", __func__, i*nk+j+1);
        ans->status = 3;
      }
      ans->dbl_v[0] = (double) i*nk+j+1;
    }
  }

  msg(dans, nx*nk, verbose);
  UNPROTECT(protecti);
  free(dans);
  return ans;
}
