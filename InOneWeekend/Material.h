#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray.h"
#include "Surface.h"
#include "Vec3.h"

class Material {
public:
  virtual bool Scatter(const Ray &r_in, const HitRecord &rec,
                       Color3 &attenuation, Ray &scattered) const = 0;
};

#endif // MATERIAL_H
