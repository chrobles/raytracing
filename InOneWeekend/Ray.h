#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray {
public:
  Ray() {}
  Ray(const Vec3 &origin, const Vec3 &endpoint)
      : origin(origin), endpoint(endpoint) {}

  Point3 Origin() const { return origin; }
  Point3 Endpoint() const { return endpoint; }

  Vec3 At(double t) const { return origin + t * endpoint; }

private:
  Point3 origin;
  Point3 endpoint;
};

#endif // RAY_H
