
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
