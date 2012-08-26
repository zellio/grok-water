#ifndef __GROKWATER_MATH_MATRIX__
#define __GROKWATER_MATH_MATRIX__


#ifdef __cplusplus
extern "C" {
#endif

  //types and structs

  // forward define the vector type so that source will compile properly
  typedef struct vector vector_t;

  typedef struct matrix matrix_t;
  struct matrix {
    double m[3][3];
  };


  //prototypes
  matrix_t matrix_add( matrix_t * A, matrix_t * B );

  matrix_t matrix_multiply_ms( matrix_t * A, double s );
  matrix_t matrix_multiply( matrix_t * A, matrix_t * B );
  matrix_t matrix_similarity_transform( matrix_t * A, matrix_t * B );
  matrix_t matrix_reorthogonalize( matrix_t * A );
  matrix_t matrix_transpose( matrix_t * A );
  matrix_t matrix_inverse( matrix_t * T );

  double matrix_determinant( matrix_t * T );
  double matrix_determinant_inverse( matrix_t * T );


#ifdef __cplusplus
};
#endif

#endif
