#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double Clamp(double x, double min, double max) {
  if (x < min)
    return min;
  if (x > max)
    return max;
  return x;
}
inline double DegreesToRadians(double d) { return d * pi / 180; }
inline double RandomDouble() { return rand() / (RAND_MAX + 1.0); }
inline double RandomDouble(double min, double max) {
  return min + (max - min) * RandomDouble();
}

// Common Headers

#include "Color.h"
#include "Ray.h"
#include "Vec3.h"

#endif // COMMON_H
