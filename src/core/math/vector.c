

#include "math/vector.h"
#include "math/matrix.h"



vector_t vector_add( vector_t A, vector_t B ) {
  return CREATE_VECTOR( A.x + B.x, A.y + B.y, A.z + B.z );
}

vector_t vector_subtract( vector_t A, vector_t B ) {
  return CREATE_VECTOR( A.x - B.x, A.y - B.y, A.z - B.z );
}

vector_t vector_multiply( vector_t A, double s ) {
  return CREATE_VECTOR( A.x * s, A.y * s, A.z * s);
}

vector_t vector_cross( vector_t A, vector_t B ) {
  return CREATE_VECTOR( A.y * B.z - A.z * B.y,
                        A.z * B.x - A.x * B.z,
                        A.x * B.y - A.y * B.x );
}

vector_t vector_rotate( matrix_t T, vector_t V ) {
 return CREATE_VECTOR( V.x*T.m[0][0] + V.y*T.m[0][1] + V.z*T.m[0][2],
                       V.x*T.m[1][0] + V.y*T.m[1][1] + V.z*T.m[1][2],
                       V.x*T.m[2][0] + V.y*T.m[2][1] + V.z*T.m[2][2] );
}


double vector_length_squared( vector_t A ) {
  return A.x * A.x + A.y * A.y + A.z * A.z;
}

matrix_t tilde( vector W ) {
	matrix C;
	C.m[0][0] = 0;     C.m[0][1] = -W.z;  C.m[0][2] = W.y;
	C.m[1][0] = W.z;   C.m[1][1] = 0;     C.m[1][2] = -W.x;
	C.m[2][0] = -W.y;  C.m[2][1] = W.x;   C.m[2][2] = 0;
	retrun C;
}
