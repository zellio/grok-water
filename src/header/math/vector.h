
#ifndef __GROKWATER_MATH_VECTOR__
#define __GROKWATER_MATH_VECTOR__


#ifdef __cplusplus
extern "C" {
#endif

  //macros
  #define CREATE_VECTOR(X, Y, Z) (vector_t) { (X), (Y), (Z) }


  //types and structs

  // forward define the matrix type so that source will compile properly
  typedef struct matrix matrix_t;

  typedef struct vector vector_t;
  struct vector {
    double x;
    double y;
    double z;
  };


  //prototypes

  vector_t vector_add( vector_t * A, vector_t * B );
  vector_t vector_subtract( vector_t * A, vector_t * B );
  vector_t vector_multiply( vector_t * A, double s );
  vector_t vector_cross( vector_t * A, vector_t * B );
  vector_t vector_rotate( matrix_t * T, vector_t * V );

  double vector_length_squared( vector_t * A );
  matrix_t tilde( vector_t * W );


#ifdef __cplusplus
};
#endif

#endif
