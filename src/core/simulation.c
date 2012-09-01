

#include "simulation.h"
#include "math/fast.h"
#include "math/vector.h"
#include "math/matrix.h"


#define N         10
#define R_MIN      1.5
#define R_MAX     15.0
#define COULOMB_K  0.138935444

#define TAU 6.2831853071796

//angstroms and radians:
#define THETA_MIN 0
#define THETA_MAX TAU
#define PHI_MIN 0.0
#define PHI_MAX TAU
#define RX_MIN 0.0
#define RX_MAX TAU
#define RY_MIN 0.0
#define RY_MAX TAU
#define RZ_MIN 0.0
#define RZ_MAX TAU

#define GEN_STEP(X, Y) (((X) - (Y)) / N)

#define R_STEP     GEN_STEP( R_MIN,     R_MAX)// ((R_MAX     - R_MIN)     / N)
#define THETA_STEP GEN_STEP( THETA_MAX, THETA_MIN)// / N)
#define PHI_STEP   GEN_STEP( PHI_MAX,   PHI_MIN)//   / N)
#define RX_STEP    GEN_STEP( RX_MAX,    RX_MIN)//    / N)
#define RY_STEP    GEN_STEP( RY_MAX,    RY_MIN)//    / N)
#define RZ_STEP    GEN_STEP( RZ_MAX,    RZ_MIN)//    / N)



#define CREATE_ATOM(X, Y, Z) (atom_t){(X), (Y), (Z)}
#define CREATE_FORCE_TORQUE(X, Y) (force_torque_t){(X), (Y)}
#define CREATE_POTENTIAL_ELEMENT(X, Y, Z, A, B, C) (potential_element_t){(X), (Y), (Z), (A), (B), (C)}

#define ROUND(A) ((int)((A) < 0)?((A) - 0.5):((A) + 0.5))


//atom_t M0[] = {
//  CREATE_ATOM( CREATE_VECTOR( 0.0,        0.065098, 0.0 ), 0,     15.9994 ),
//  CREATE_ATOM( CREATE_VECTOR( -0.756950, -0.520784, 0.0 ), 0.52,  1.0008  ),
//  CREATE_ATOM( CREATE_VECTOR( 0.756950,  -0.520784, 0.0 ), 0.52,  1.0008  ),
//  CREATE_ATOM( CREATE_VECTOR( 0.0,       -0.084902, 0.0 ), -1.04, 0       )
//}//;


potential_element_t
get_water_potential( potential_element_t * water_potential,
                     int ir, int t, int p, int irx, int iry, int irz)
{
  //assert(ir >= 0 && t >= 0 && p >= 0 && irx >= 0 && iry >= 0 && irz >= 0);
  //assert(ir < N && t < N && p < N && irx < N && iry < N && irz < N);
	return  *(water_potential + ir * (N*N*N*N*N) + t * (N*N*N*N) +
            p * (N*N*N) + irx * (N*N) + iry * N + irz);
}


/*
	static potential_element *water_potential = NULL;
	if(water_potential==NULL) {
		FILE *input = fopen("model.dat", "rb");
		if(input==NULL) {puts("File open failed"); exit(1);}
		water_potential = malloc(sizeof(potential_element)*N*N*N*N*N*N);
		//fread(water_potential, sizeof(potential_element), N*N*N*N*N*N, input);
		int elements_read = 0;
		while(elements_read<N*N*N*N*N*N) {
			elements_read += fread(water_potential+elements_read, sizeof(potential_element), 10000, input);
		}
		if(elements_read != N*N*N*N*N*N) {printf("File read failed, read %d elements out of %d\n", elements_read, N*N*N*N*N*N); exit(1);}
		fclose(input);

		stopwatch(); //for timing
	}

*/



potential_element_t
interpolate_water_potential( double r, double theta, double phi,
                             double rx, double ry, double rz )
{
  if( phi   < 0 ) phi   += TAU;
  if( theta < 0 ) theta += TAU;
  if( rx    < 0 ) rx    += TAU;
  if( ry    < 0 ) ry    += TAU;
  if( rz    < 0 ) rz    += TAU;

	int
    ir  = (int)((r - R_MIN) / R_STEP),
    t   = (int)((theta - THETA_MIN) / THETA_STEP),
    p   = (int)((phi - PHI_MIN)   / PHI_STEP),
    irx = (int)((rx - RX_MIN) / RX_STEP),
    iry = (int)((ry - RY_MIN) / RY_STEP),
    irz = (int)((rz - RZ_MIN) / RZ_STEP); //low indices

  if ( 0 >= ir || ir >= N ) //element is too far or close
    return CREATE_POTENTIAL_ELEMENT( 0, 0, 0, 0, 0, 0 );

	double weights[2][6] = {
    { 0, 0, 0, 0, 0, 0 },
    {
      (r - R_MIN - ir * R_STEP) / R_STEP,
      (theta - THETA_MIN - t * THETA_STEP) / THETA_STEP,
      (phi - PHI_MIN - p * PHI_STEP) / PHI_STEP,
      (rx - RX_MIN - irx * RX_STEP) / RX_STEP,
      (ry - RY_MIN - iry * RY_STEP) / RY_STEP,
      (rz - RZ_MIN - irz * RZ_STEP) / RZ_STEP
    }
  }; //linear weights

	for( int i = 0; i < 6; i++ )
		weights[0][i] = 1 - weights[1][i];


  potential_element_t sum = CREATE_POTENTIAL_ELEMENT(0, 0, 0, 0, 0, 0);
  double weight_sum = 0;
  for ( int a = 0; a < 2; a++ ) {
    for ( int b = 0; b < 2; b++ ) {
      for ( int c = 0; c < 2; c++ ) {
        for ( int d = 0; d < 2; d++ ) {
          for ( int e = 0; e < 2; e++ ) {
            for ( int f = 0; f < 2; f++ ) {
              double w = weights[a][0] * weights[b][1] * weights[c][2] * weights[d][3] * weights[e][4] * weights[f][5];

              potential_element_t current = get_water_potential(water_potential, (ir+a)==N?N-1:(ir+a), (t+b)==N?0:(t+b), (p+c)==N?0:(p+c), (irx+d)==N?0:(irx+d), (iry+e)==N?0:(iry+e), (irz+f)==N?0:(irz+f) ); //truncate radius and wrap angles

              sum.ax += current.ax * w;
              sum.ay += current.ay * w;
              sum.az += current.az * w;
              sum.tx += current.tx * w;
              sum.ty += current.ty * w;
              sum.tz += current.tz * w;

              weight_sum += w;
            }
          }
        }
      }
    }
  }

	if(weight_sum==0) { //take nearest neighbor
		int
      nir = ROUND((r - R_MIN) / R_STEP),
      nt = ROUND((theta - THETA_MIN) / THETA_STEP),
      np = ROUND((phi - PHI_MIN) / PHI_STEP),
      nirx = ROUND((rx - RX_MIN) / RX_STEP),
      niry = ROUND((ry - RY_MIN) / RY_STEP),
      nirz = ROUND((rz - RZ_MIN) / RZ_STEP);

		return get_water_potential(water_potential, nir==N?N-1:nir, nt==N?0:nt, np==N?0:np, nirx==N?0:nirx, niry==N?0:niry, nirz==N?0:nirz ); //truncate radius and wrap angles
	}

	double normalize_weights = 1/weight_sum;
	sum.ax *= normalize_weights;
	sum.ay *= normalize_weights;
	sum.az *= normalize_weights;
	sum.tx *= normalize_weights;
	sum.ty *= normalize_weights;
	sum.tz *= normalize_weights;

	return sum;

}


force_torque_t
calculate_force_torque( water_t I, water_t J )
{
  atom_t M0[] = {
    CREATE_ATOM( CREATE_VECTOR( 0.0,        0.065098, 0.0 ), 0,     15.9994 ),
    CREATE_ATOM( CREATE_VECTOR( -0.756950, -0.520784, 0.0 ), 0.52,  1.0008  ),
    CREATE_ATOM( CREATE_VECTOR( 0.756950,  -0.520784, 0.0 ), 0.52,  1.0008  ),
    CREATE_ATOM( CREATE_VECTOR( 0.0,       -0.084902, 0.0 ), -1.04, 0       )
  };

  vector_t total_force  = CREATE_VECTOR(0, 0, 0);
  vector_t total_torque = CREATE_VECTOR(0, 0, 0);

  for( int a = 0; a < 4; a++ ) {
    vector_t I_rotated = vector_rotate( &I.A, &M0[a].r );
    vector_t RI = vector_add( &I_rotated, &I.r );
    for ( int b = 0; b < 4; b++ ) {
      vector_t J_rotated = vector_rotate( &J.A, &M0[b].r );
      vector_t RJ = vector_add( &J_rotated, &J.r );
      vector_t DR = vector_subtract( &RI, &RJ );
      double DR_squared = vector_length_squared( &DR );
      if ( DR_squared > R_MAX * R_MAX )
        continue;
      double force_magnitude = COULOMB_K * M0[a].q * M0[b].q / DR_squared;

      if ( DR_squared < 100 && M0[a].m > 15 && M0[b].m > 15 )
				force_magnitude += 0;//24 * 6.4852e-5 * (2* pow(3.16,12) * pow(r_squared,-6.5) - pow(3.16,6) * pow(r_squared,-3.5)); //Units via google [0.1550/6.0221415e23 kcal in (amu*angstroms^2) / femtoseconds^2
      vector_t force     = vector_scale( &DR, force_magnitude / fast_sqrt( DR_squared ));
      vector_t IRC_force = vector_cross( &I_rotated, &force );

      total_force = vector_add( &total_force, &force );
      total_torque = vector_add( &total_torque, &IRC_force);
    }
  }

  return CREATE_FORCE_TORQUE( total_force, total_torque );
}


int
integrate( water_t * bodies, int i, vector_t * total_acceleration,
           vector_t * total_torque, matrix_t * initial_inverse_moment_of_inertia,
           double t)
{
  vector_t scratch;

  scratch = vector_add( &bodies[i].a, total_acceleration );
  scratch = vector_scale(&scratch, 0.5 * t);
  bodies[i].v = vector_add( &bodies[i].v, &scratch );

  bodies[i].a = *total_acceleration;
  scratch = vector_scale( total_torque, t );
  bodies[i].L = vector_add( &bodies[i].L, &scratch );

  matrix_t current_inverse_moment_of_inertia =
    matrix_similarity_transform( &bodies[i].A, initial_inverse_moment_of_inertia );

  bodies[i].o = vector_rotate(&current_inverse_moment_of_inertia, &bodies[i].L);

  return 0;
}

matrix_t
get_initial_inverse_moment_of_inertia()
{
  atom_t M0[] = {
    CREATE_ATOM( CREATE_VECTOR( 0.0,        0.065098, 0.0 ), 0,     15.9994 ),
    CREATE_ATOM( CREATE_VECTOR( -0.756950, -0.520784, 0.0 ), 0.52,  1.0008  ),
    CREATE_ATOM( CREATE_VECTOR( 0.756950,  -0.520784, 0.0 ), 0.52,  1.0008  ),
    CREATE_ATOM( CREATE_VECTOR( 0.0,       -0.084902, 0.0 ), -1.04, 0       )
  };

	double moment_of_inertia[3][3] = {
		{ M0[0].m * M0[0].r.y * M0[0].r.y + 2 * M0[1].m * M0[1].r.y * M0[1].r.y, 0, 0 },
		{ 0, 2 * M0[1].m * M0[1].r.x * M0[1].r.x, 0} ,
		{ 0, 0, M0[0].m * (M0[0].r.x * M0[0].r.x + M0[0].r.y * M0[0].r.y) +
     2 * M0[1].m * (M0[1].r.x * M0[1].r.x + M0[1].r.y * M0[1].r.y) }
	};

	double inverse_moment_of_inertia[3][3] =  {
		{ moment_of_inertia[1][1] * moment_of_inertia[2][2], 0, 0 },
		{ 0, moment_of_inertia[0][0] * moment_of_inertia[2][2], 0 },
		{ 0, 0, moment_of_inertia[0][0] * moment_of_inertia[1][1] }
	};

	double moment_of_inertia_determinant =
    moment_of_inertia[0][0] * moment_of_inertia[1][1] * moment_of_inertia[2][2];

	matrix_t initial_inverse_moment_of_inertia;
	for ( int i = 0; i < 3; i++ )
		for ( int j = 0; j < 3; j++ )
			initial_inverse_moment_of_inertia.m[i][j] =
        inverse_moment_of_inertia[i][j] / moment_of_inertia_determinant;

	return initial_inverse_moment_of_inertia;
}
