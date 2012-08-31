

#include "math/fast.h"

#include <stdint.h>


#define MASK_UNION(u, v) union { int64_t m; double d; } u; u.d = (v);
#define PI 3.1415926535898


double fast_sqrt( double n ) {
  MASK_UNION(u, n);
  u.m = ((int64_t)1 << 61) + (u.m >> 1) - ((int64_t)1 << 51);
  return u.d;
}

double fast_abs( double n ) {
  MASK_UNION(u, n);
  u.m &= (int64_t)0x7fffffffffffffff;
  return u.d;
}

double fast_acos( double n ) {
  return (n >= 0) ?
    fast_sqrt( 1 - n ) * ((PI/2.0) + n * (-0.213300989 + n * (0.077980478 + n * -0.02164095))) :
    PI - fast_acos( -n );
}

double fast_atan2( double a, double b ) {
  return
    (fast_abs( a ) > fast_abs( b )) ?
    (-a * b / (a * a + 0.28088 * b * b) + PI / 2 * (a > 0 ? 1.0 : -1.0)) :
    (-PI / 2 * (a * b > 0 ? 1.0 : -1.0) + PI / 2 * (a > 0 ? 1.0 : -1.0) + a * b / (b * b + 0.28088 * a * a));
}
