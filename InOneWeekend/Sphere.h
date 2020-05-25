#ifndef SPHERE_H
#define SPHERE_H

#include "Surface.h"
#include "Vec3.h"

class Sphere : public Surface {
public:
  Sphere() {}
  Sphere(Point3 center, double r) : center(center), radius(r){};

  Point3 Center() const { return center; };
  double Radius() const { return radius; };

  virtual bool Hit(const Ray &r, double t_min, double t_max,
                   HitRecord &rec) const;

private:
  Point3 center;
  double radius;
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
    Vec3 outwardNormal;
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = r.At(rec.t);
      outwardNormal = (rec.p - center) / radius;
      rec.SetFaceNormal(r, outwardNormal);
      return true;
    }
    temp = (-b + root) / a;
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = r.At(rec.t);
      outwardNormal = (rec.p - center) / radius;
      rec.SetFaceNormal(r, outwardNormal);
      return true;
    }
  }
  return false;
}

#endif // SPHERE_H
