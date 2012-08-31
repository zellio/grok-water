
#ifndef __GROKWATER_MATH_VECTOR__
#define __GROKWATER_MATH_VECTOR__

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

  //macros
#define CREATE_VECTOR(X, Y, Z) (vector_t){ (X), (Y), (Z) }


  //prototypes

  vector_t vector_add( const vector_t * A, const vector_t * B );
  vector_t vector_subtract( const vector_t * A, const vector_t * B );
  vector_t vector_multiply( const vector_t * A, const double s );
  vector_t vector_scale( const vector_t * A, const double s );
  vector_t vector_cross( const vector_t * A, const vector_t * B );
  vector_t vector_rotate( const matrix_t * T, const vector_t * V );

  double vector_length_squared( const vector_t * A );
  matrix_t tilde( const vector_t * W );


#ifdef __cplusplus
};
#endif

#endif
