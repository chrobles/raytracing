#ifndef SPHERE_H
#define SPHERE_H

#include "material.h"
#include "surface.h"
#include "vec3.h"

class Sphere : public Surface {
public:
  Sphere() {}
  Sphere(Point3 center, double r, std::shared_ptr<Material> m)
      : center(center), radius(r), mat_ptr(m){};

  Point3 Center() const { return center; };
  double Radius() const { return radius; };
  std::shared_ptr<Material> MaterialPtr() { return mat_ptr; };

  virtual bool Hit(const Ray &r, double t_min, double t_max,
                   HitRecord &rec) const;

private:
  Point3 center;
  double radius;
  std::shared_ptr<Material> mat_ptr;
};

bool Sphere::Hit(const Ray &r, double t_min, double t_max,
                 HitRecord &rec) const {
  Vec3 oc = r.Origin() - center;
  auto a = r.Endpoint().LengthSquared();
  auto b = Dot(oc, r.Endpoint());
  auto c = oc.LengthSquared() - radius * radius;
  auto discriminant = b * b - a * c;

  if (discriminant > 0) {
    auto root = sqrt(discriminant);
    auto temp = (-b - root) / a;
    Vec3 outward_normal;
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = r.At(rec.t);
      outward_normal = (rec.p - center) / radius;
      rec.SetFaceNormal(r, outward_normal);
      rec.mat_ptr = mat_ptr;
      return true;
    }
    temp = (-b + root) / a;
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = r.At(rec.t);
      outward_normal = (rec.p - center) / radius;
      rec.SetFaceNormal(r, outward_normal);
      rec.mat_ptr = mat_ptr;
      return true;
    }
  }
  return false;
}

#endif // SPHERE_H
