

#include "math/vector.h"
#include "math/matrix.h"



vector_t vector_add( const vector_t * A, const vector_t * B ) {
    return CREATE_VECTOR( A->x + B->x, A->y + B->y, A->z + B->z );
}


vector_t vector_subtract( const vector_t * A, const vector_t * B ) {
    return CREATE_VECTOR( A->x - B->x, A->y - B->y, A->z - B->z );
}


vector_t vector_scale( const vector_t * A, const double s ) {
    return CREATE_VECTOR( A->x * s, A->y * s, A->z * s);
}

vector_t vector_multiply( const vector_t * A, const double s ) {
    return vector_scale( A, s );
}


vector_t vector_cross( const vector_t * A, const vector_t * B ) {
    return CREATE_VECTOR( A->y * B->z - A->z * B->y,
                          A->z * B->x - A->x * B->z,
                          A->x * B->y - A->y * B->x );
}


vector_t vector_rotate( const matrix_t * T, const vector_t * V ) {
    return CREATE_VECTOR( V->x * T->m[0][0] + V->y * T->m[0][1] + V->z * T->m[0][2],
                          V->x * T->m[1][0] + V->y * T->m[1][1] + V->z * T->m[1][2],
                          V->x * T->m[2][0] + V->y * T->m[2][1] + V->z * T->m[2][2] );
}


double vector_length_squared( const vector_t * A ) {
    return A->x * A->x + A->y * A->y + A->z * A->z;
}

matrix_t tilde( const vector_t * W ) {
  matrix_t C;
  C.m[0][0] = 0;      C.m[0][1] = -W->z;  C.m[0][2] = W->y;
  C.m[1][0] = W->z;   C.m[1][1] = 0;      C.m[1][2] = -W->x;
  C.m[2][0] = -W->y;  C.m[2][1] = W->x;   C.m[2][2] = 0;
  return C;
}
