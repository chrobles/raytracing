#ifndef METAL_H
#define METAL_H

#include "Material.h"
#include "Vec3.h"

class Metal : public Material {
public:
  Metal(const Color3 &a) : albedo(a) {}

  virtual bool Scatter(const Ray &r_in, const HitRecord &rec,
                       Color3 &attenuation, Ray &scattered) const {
    Vec3 reflected = Reflect(UnitVector(r_in.Endpoint()), rec.normal);
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return (Dot(scattered.Endpoint(), rec.normal) > 0);
  }

public:
  Color3 albedo;
};

#endif // METAL_H
