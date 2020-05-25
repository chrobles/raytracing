#ifndef SURFACE_H
#define SURFACE_H

#include "Material.h"

class Material;

struct HitRecord {
  Point3 p;
  Vec3 normal;
  std::shared_ptr<Material> mat_ptr;
  double t;
  bool front_face;

  inline void SetFaceNormal(const Ray &r, const Vec3 &outward_normal) {
    front_face = Dot(r.Endpoint(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class Surface {
public:
  virtual bool Hit(const Ray &r, double t_min, double t_max,
                   HitRecord &rec) const = 0;
};

#endif // SURFACE_H
