

#include <stdio.h>

#include "math/inspect.h"


int inspect_matrix( const matrix_t * M ) {
  fprintf(stdout, "|%.2e %.2e %.2e|\r\n", M->m[0][0], M->m[0][1], M->m[0][2]);
  fprintf(stdout, "|%.2e %.2e %.2e|\r\n", M->m[1][0], M->m[1][1], M->m[1][2]);
  fprintf(stdout, "|%.2e %.2e %.2e|\r\n", M->m[2][0], M->m[2][1], M->m[2][2]);
  return 0;
}

int inspect_vector( const vector_t * V ) {
  fprintf(stdout, "<%.2e %.2e %.2e>\r\n", V->x, V->y, V->z);
  return 0;
}
