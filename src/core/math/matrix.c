

#include "math/matrix.h"


matrix_t matrix_add( const matrix_t * A, const matrix_t * B ) {
    matrix_t C;
    C.m[0][0] = A->m[0][0] + B->m[0][0];
    C.m[0][1] = A->m[0][1] + B->m[0][1];
    C.m[0][2] = A->m[0][2] + B->m[0][2];

    C.m[1][0] = A->m[1][0] + B->m[1][0];
    C.m[1][1] = A->m[1][1] + B->m[1][1];
    C.m[1][2] = A->m[1][2] + B->m[1][2];

    C.m[2][0] = A->m[2][0] + B->m[2][0];
    C.m[2][1] = A->m[2][1] + B->m[2][1];
    C.m[2][2] = A->m[2][2] + B->m[2][2];
    return C;
}


matrix_t matrix_scale( const matrix_t * A, const double s ) {
    matrix_t C;
    C.m[0][0] = A->m[0][0] * s;
    C.m[0][1] = A->m[0][1] * s;
    C.m[0][2] = A->m[0][2] * s;

    C.m[1][0] = A->m[1][0] * s;
    C.m[1][1] = A->m[1][1] * s;
    C.m[1][2] = A->m[1][2] * s;

    C.m[2][0] = A->m[2][0] * s;
    C.m[2][1] = A->m[2][1] * s;
    C.m[2][2] = A->m[2][2] * s;
    return C;
}
matrix_t matrix_multiply_ms( const matrix_t * A, const double s ) {
    return matrix_scale( A, s );
}


matrix_t matrix_multiply( const matrix_t * A, const matrix_t * B ) {
    matrix_t C;
    C.m[0][0] = A->m[0][0] * B->m[0][0] + A->m[0][1] * B->m[1][0] + A->m[0][2] * B->m[2][0];
    C.m[0][1] = A->m[0][0] * B->m[0][1] + A->m[0][1] * B->m[1][1] + A->m[0][2] * B->m[2][1];
    C.m[0][2] = A->m[0][0] * B->m[0][2] + A->m[0][1] * B->m[1][2] + A->m[0][2] * B->m[2][2];

    C.m[1][0] = A->m[1][0] * B->m[0][0] + A->m[1][1] * B->m[1][0] + A->m[1][2] * B->m[2][0];
    C.m[1][1] = A->m[1][0] * B->m[0][1] + A->m[1][1] * B->m[1][1] + A->m[1][2] * B->m[2][1];
    C.m[1][2] = A->m[1][0] * B->m[0][2] + A->m[1][1] * B->m[1][2] + A->m[1][2] * B->m[2][2];

    C.m[2][0] = A->m[2][0] * B->m[0][0] + A->m[2][1] * B->m[1][0] + A->m[2][2] * B->m[2][0];
    C.m[2][1] = A->m[2][0] * B->m[0][1] + A->m[2][1] * B->m[1][1] + A->m[2][2] * B->m[2][1];
    C.m[2][2] = A->m[2][0] * B->m[0][2] + A->m[2][1] * B->m[1][2] + A->m[2][2] * B->m[2][2];
    return C;
}


matrix_t matrix_similarity_transform( const matrix_t * A, const matrix_t * B ) {
    matrix_t AB = matrix_multiply( A, B );
    matrix_t AT = matrix_transpose( A );
    return matrix_multiply( &AB, &AT );
}


//reorthogonalize: repeatedly average the rotation matrix with its inverse
//transpose (itself, if it is already orthogonal). there is a more optimized
//way to do this, or tell if you don't have to - check paper.
matrix_t matrix_reorthogonalize( const matrix_t * A ) {
    matrix_t average = *A;
    for ( int j = 0; j < 3; j++ ) {
        matrix_t At = matrix_transpose( &average );
        matrix_t IAt = matrix_inverse( &At );
        average = matrix_add( &average, &IAt );
        average = matrix_scale( A, 0.5 );
    }
    return average;
}


matrix_t matrix_transpose( const matrix_t * A ) {
    matrix_t C;
    C.m[0][0] = A->m[0][0];  C.m[0][1] = A->m[1][0];  C.m[0][2] = A->m[2][0];
    C.m[1][0] = A->m[0][1];  C.m[1][1] = A->m[1][1];  C.m[1][2] = A->m[2][1];
    C.m[2][0] = A->m[0][2];  C.m[2][1] = A->m[1][2];  C.m[2][2] = A->m[2][2];
    return C;
}


matrix_t matrix_adjugate( const matrix_t * T ) {
    matrix_t C;
    C.m[0][0] =  T->m[1][1] * T->m[2][2] - T->m[1][2] * T->m[2][1];
    C.m[0][1] =  T->m[1][2] * T->m[2][0] - T->m[1][0] * T->m[2][2];
    C.m[0][2] =  T->m[1][0] * T->m[2][1] - T->m[1][1] * T->m[2][0];

    C.m[1][0] =  T->m[0][2] * T->m[2][1] - T->m[0][1] * T->m[2][2];
    C.m[1][1] =  T->m[0][0] * T->m[2][2] - T->m[0][2] * T->m[2][0];
    C.m[1][2] =  T->m[0][1] * T->m[2][0] - T->m[0][0] * T->m[2][1];

    C.m[2][0] =  T->m[0][1] * T->m[1][2] - T->m[0][2] * T->m[1][1];
    C.m[2][1] =  T->m[0][2] * T->m[1][0] - T->m[0][0] * T->m[1][2];
    C.m[2][2] =  T->m[0][0] * T->m[1][1] - T->m[0][1] * T->m[1][0];
    return C;
}


matrix_t matrix_inverse( const matrix_t * T ) {
  matrix_t adjugate = matrix_adjugate( T );
  return matrix_scale( &adjugate, matrix_determinant_inverse( T ));
}


double matrix_determinant( const matrix_t * T ) {
  return (T->m[0][0] * (T->m[2][2] * T->m[1][1]-T->m[2][1] * T->m[1][2]) -
            T->m[1][0] * (T->m[2][2] * T->m[0][1]-T->m[2][1] * T->m[0][2]) +
            T->m[2][0] * (T->m[1][2] * T->m[0][1]-T->m[1][1] * T->m[0][2]));
}


double matrix_determinant_inverse ( const matrix_t * T ) {
    return 1.0 / matrix_determinant( T );
}
