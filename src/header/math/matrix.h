
#ifndef __GROKWATER_MATH_MATRIX__
#define __GROKWATER_MATH_MATRIX__

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

  //prototypes
  matrix_t matrix_add( const matrix_t * A, const matrix_t * B );

  matrix_t matrix_multiply_ms( const  matrix_t * A, const double s );
  matrix_t matrix_multiply( const matrix_t * A, const matrix_t * B );
  matrix_t matrix_similarity_transform( const matrix_t * A, const matrix_t * B );
  matrix_t matrix_reorthogonalize( const matrix_t * A );
  matrix_t matrix_transpose( const matrix_t * A );
  matrix_t matrix_inverse( const matrix_t * T );

  double matrix_determinant( const matrix_t * T );
  double matrix_determinant_inverse( const matrix_t * T );


  matrix_t matrix_scale( const matrix_t * A, const double s );
  matrix_t matrix_adjugate( const matrix_t * T );

#ifdef __cplusplus
};
#endif

#endif
