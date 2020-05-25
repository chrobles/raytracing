#ifndef SURFACE_H
#define SURFACE_H

#include "Ray.h"

struct HitRecord {
  Point3 p;
  Vec3 normal;
  double t;
  bool frontFace;

  inline void SetFaceNormal(const Ray &r, const Vec3 &outwardNormal) {
    frontFace = Dot(r.Endpoint(), outwardNormal) < 0;
    normal = frontFace ? outwardNormal : -outwardNormal;
  }
};

class Surface {
public:
  virtual bool Hit(const Ray &r, double t_min, double t_max,
                   HitRecord &rec) const = 0;
};

#endif // SURFACE_H
