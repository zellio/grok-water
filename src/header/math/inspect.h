

#ifndef __GROKWATER_MATH_INSPECT__
#define __GROKWATER_MATH_INSPECT__


#ifdef __cplusplus
extern "C" {
#endif


  // typedefs and structs

  typedef matrix_t matrix;
  typedef vector_t vector;


  //prototypes

  int inspect_matrix( matrix_t matrix );

  int inspect_vector( vector_t vector );


#ifdef __cplusplus
};
#endif

#endif
