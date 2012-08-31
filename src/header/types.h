#ifndef __GROKWATER_MATH_TYPES__
#define __GROKWATER_MATH_TYPES__


#ifdef __cplusplus
extern "C" {
#endif

  //types and structs


  // forward define the vector type so that source will compile properly
  typedef struct matrix              matrix_t;
  typedef struct vector              vector_t;

  typedef struct atom                atom_t;
  typedef struct force_torque        force_torque_t;
  typedef struct potential_element   potential_element_t;
  typedef struct water               water_t;

  struct matrix {
    double m[3][3];
  };

  struct vector {
    double x;
    double y;
    double z;
  };

  struct atom {
    vector_t r;
    double q;
    double m;
  };

  struct force_torque {
    vector_t force;
    vector_t torque;
  };

  struct potential_element {
    float ax, ay, az;
    float tx, ty, tz;
  };

  struct water {
    vector_t r;
    vector_t v;
    vector_t a;
    vector_t L;
    vector_t o;
    matrix_t A;
  };

#ifdef __cplusplus
};
#endif

#endif
