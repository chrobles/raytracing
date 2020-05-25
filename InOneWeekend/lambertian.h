#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"
#include "Ray.h"
#include "Vec3.h"

class Lambertian : public Material {
public:
  Lambertian(const Color3 &a) : albedo(a) {}

  virtual bool Scatter(const Ray &r_in, const HitRecord &rec,
                       Color3 &attenuation, Ray &scattered) const {
    Vec3 scatter_direction = rec.normal + RandomUnitVector();
    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }

private:
  Color3 albedo;
};

#endif // LAMBERTIAN_H
