
#ifndef __GROKWATER_SIMULATION__
#define __GROKWATER_SIMULATION__

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif


  // prototypes
  potential_element_t
  get_water_potential( potential_element_t * water_potential,
                       int ir, int t, int p, int irx, int iry, int irz);

  potential_element_t
  interpolate_water_potential( double r, double theta, double phi,
                               double rx, double ry, double rz );

  force_torque_t
  calculate_force_torque( water_t i, water_t j );

  int
  integrate( water_t * bodies, int i, vector_t * total_acceleration,
             vector_t * total_torque, matrix_t * initial_inverse_moment_of_inertia,
             double t);

  matrix_t
  get_initial_inverse_moment_of_inertia( void );


#ifdef __cplusplus
};
#endif

#endif



/*
#ifndef __GROKWATER_SIMULATION__
#define __GROKWATER_SIMULATION__

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CREATE_ATOM(X, Y, Z) (atom){ (X), (Y), (Z) }

#define ROUND(A) ((int)((A) < 0)?((A) - 0.5):((A) + 0.5))

#define round(a)   (((a) < 0) ? (int)((a) - 0.5) : (int)((a) + 0.5))
#define RF (((double)rand())/RAND_MAX)
#define NRF (1 - 2*rf)

//in elementary charges, angstroms, amu, and femtoseconds [8.987551787e9 N m^2
//C^-2 * (1.60217646e-19)^2 in (amu*angstroms/femtoseconds^2) angstroms^2 C^-2]

#define WATER_MASS 18.0153

//angstroms and radians:
#define THETA_MIN 0
#define THETA_MAX  6.2831853071796
#define PHI_MIN 0.0
#define PHI_MAX 6.2831853071796
#define RX_MIN 0.0
#define RX_MAX 6.2831853071796
#define RY_MIN 0.0
#define RY_MAX 6.2831853071796
#define RZ_MIN 0.0
#define RZ_MAX 6.2831853071796
#define R_STEP ((r_max-r_min)/N)

#define THETA_STEP ((theta_max-theta_min)/N)
#define PHI_STEP ((phi_max-phi_min)/N)
#define RX_STEP ((rx_max-rx_min)/N)
#define RY_STEP ((ry_max-ry_min)/N)
#define RZ_STEP ((rz_max-rz_min)/N)

#define N 20

  / *
  //macros
#define ROUND( n ) ((int)(((n) < 0) ? ((n) - 0.5) : ((n) + 0.5)))
#define rf (((double)rand())/RAND_MAX)
#define nrf (1 - 2*rf)

//constants
#define R_MIN 1.5         //r_min 1.5
#define R_MAX 15          //r_max 15
#define THETA_MIN 0       //theta_min 0
#define THETA_MAX 6.2831853071796  //theta_max 2*PI
#define PHI_MIN 0.0       //phi_min 0.0
#define PHI_MAX 2 * PI    //phi_max 2*PI
#define RX_MIN 0.0        //rx_min 0.0
#define RX_MAX 2 * PI     //rx_max 2*PI
#define RY_MIN 0.0        //ry_min 0.0
#define RY_MAX 2 * PI     //ry_max 2*PI
#define RZ_MIN 0.0
#define RZ_MAX 2 * PI
#define r_step ((r_max-r_min)/N)
#define theta_step ((theta_max-theta_min)/N)
#define phi_step ((phi_max-phi_min)/N)
#define rx_step ((rx_max-rx_min)/N)
#define ry_step ((ry_max-ry_min)/N)
#define rz_step ((rz_max-rz_min)/N)
  * /

  // prototypes

  force_torque_t
  calculate_force_torque( water_t i, water_t j);

  int
  integrate( water_t * bodies, int i, vector_t total_acceleration, vector_t total_torque,
             matrix_t initial_inverse_moment_of_inertia, double t);

  matrix_t
  get_initial_inverse_moment_of_inertia();


#ifdef __cplusplus
};
#endif

#endif
*/
